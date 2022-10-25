#include <Python.h>
#include "object.h"
#include "py_cpu.h"
#include "ads_exception.h"

#include <iostream>
#include <python3.9/unicodeobject.h> // ?
#include <cassert>
#include <stdexcept>


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
#else
    self_cpu->m_ads = (BasicADS*)PyObject_Malloc(sizeof(GenericAdsClient));
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

	try {
        self_cpu->m_cpu.emplace(*(self_cpu->m_ads));
	}
	catch (const DeviceManager::AdsException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
		return -1;
	}

	if (!self_cpu->m_cpu) {
		std::cerr << "Module not available on target" << std::endl;
        PyErr_SetString(PyExc_RuntimeError, "Module not available on target");
		return -1;
	}

    return 0;
}

void CpuType_dealloc(CpuType *self){
    std::cout << "CpuType dealloc() called" << std::endl;

    CpuType* self_cpu = reinterpret_cast<CpuType*>(self);

    self_cpu->m_cpu.reset();
    if(self_cpu->m_ads){
        self_cpu->m_ads->~BasicADS();
        PyObject_Free(self_cpu->m_ads);
    }
}

PyObject* getTemp(PyObject *self, PyObject *args)
{
    

    PyObject *test  = self;
    //int ret = PyArg_ParseTuple(args, "O", &test);
    CpuType* self_cpu = reinterpret_cast<CpuType*>(self);
    if(self_cpu->m_cpu){
        if(self_cpu->m_cpu.has_value()){
            std::cout << "Instanz gefunden" << std::endl;
        } else {
            std::cout << "Instanz nicht gefunden" << std::endl;
        }
    }
    //CpuType* self_cpu = reinterpret_cast<CpuType*>(test);
    return PyLong_FromUnsignedLong(123);
}
