#include <Python.h>
#include "cpu.h"
#include "object.h"
#include "py_cpu.h"
#include "ads_exception.h"
#include "pyerrors.h"

#include <cstdint>
#include <iostream>
#include <python3.9/unicodeobject.h> // ?
#include <cassert>
#include <stdexcept>
#include "ads_py_error.h"

PyObject *CpuType_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
    std::cout << "CpuType_new() called" << std::endl;
    CpuType *self;
        self = (CpuType *) type->tp_alloc(type, 0);
        if (self != NULL) {
            self->m_ads = NULL;
            self->m_dtype = NULL;
        } else {
            return PyErr_NoMemory();
        }
       return (PyObject*) self;
}

int CpuType_init(PyObject *self, PyObject *args, PyObject *kwds){
    std::cout << "CpuType init() called" << std::endl;
    assert(args);

    char *amsAddr = NULL;
#if defined(USE_TWINCAT_ROUTER)
    if (!PyArg_ParseTuple(args, "s", &amsAddr)) {
        return -1;
    }
#else
    char *ipAddr  = NULL;
    // TODO oder ss
    if (!PyArg_ParseTuple(args, "ss", &amsAddr, &ipAddr)) {
        return -1;
    }
#endif

    CpuType* self_cpu = reinterpret_cast<CpuType*>(self);
    static const AmsNetId remoteNetId{ amsAddr };

#if defined(USE_TWINCAT_ROUTER)
	auto adsClient = std::shared_ptr<BasicADS>(new TC1000AdsClient(remoteNetId));

    // TODO
#else

    // Memory allocation for ADS instnace

    self_cpu->m_ads = (BasicADS*)PyObject_Malloc(sizeof(GenericAdsClient));
    if(!self_cpu->m_ads){
        PyErr_SetNone(PyExc_MemoryError);
        return -1;
    }

    try{
        new (self_cpu->m_ads) GenericAdsClient(remoteNetId, ipAddr);
    } catch (const AdsException &ex) {
        std::cout << "ADS Exception" << std::endl;
        PyObject_Free(self_cpu->m_ads);
        self_cpu->m_ads = NULL;
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return -1;
    } catch (const std::runtime_error &ex) {
        std::cout << "Runtime error" << std::endl;
        PyObject_Free(self_cpu->m_ads);
        self_cpu->m_ads = NULL;
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return -1;
    }
#endif

    // Memory allocation for Device Manager type
    self_cpu->m_dtype = (DeviceManager::CPU*)PyObject_Malloc(sizeof(DeviceManager::CPU));
    if(!self_cpu->m_dtype){
        PyErr_SetNone(PyExc_MemoryError);
        return -1;
    }

	try {
        new (self_cpu->m_dtype) DeviceManager::CPU(*self_cpu->m_ads);
        //self_cpu->m_cpu.emplace(*(self_cpu->m_ads));
	}
	catch (const DeviceManager::AdsException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
		return -1;
	}

	if (!self_cpu->m_dtype) {
		//std::cerr << "Module not available on target" << std::endl;
        PyErr_SetString(PyExc_RuntimeError, "Module not available on target");
		return -1;
	}

    return 0;
}

void CpuType_dealloc(CpuType *self){
    std::cout << "CpuType dealloc() called" << std::endl;

    CpuType* self_cpu = reinterpret_cast<CpuType*>(self);

    //self_cpu->m_cpu.reset(); // TODO
    if(self_cpu->m_dtype){
        self_cpu->m_dtype->~CPU();
        PyObject_Free(self_cpu->m_dtype);
    }

    if(self_cpu->m_ads){
        self_cpu->m_ads->~BasicADS();
        PyObject_Free(self_cpu->m_ads);
    }
}

PyObject* getTemp(PyObject *self, PyObject *args)
{
    CpuType* self_cpu = reinterpret_cast<CpuType*>(self);

    int16_t temp = 0;
    int32_t ret = self_cpu->m_dtype->getTemp(temp);

    if(ret){
        PyErr_SetObject(PyExc_RuntimeError, adsErrorStr(ret));
        return NULL;
    }

    return PyLong_FromUnsignedLong(temp);
}
