#ifndef PY_SLOT_TEMPLATES_H
#define PY_SLOT_TEMPLATES_H

#include <Python.h>
#include <iostream>
#include <cstdint>

#if defined(USE_TWINCAT_ROUTER)
	#include "TC1000_AdsClient.h"
#else
	#include "GenericAdsClient.h"
#endif

#include "ads_exception.h"

template <typename T>
struct DObject{
    PyObject_HEAD
#if defined(USE_TWINCAT_ROUTER)
    TC1000AdsClient* m_ads;
#else
    BasicADS* m_ads;
#endif
    T *m_dtype;
};

template <typename T>
PyObject *dtype_new(PyTypeObject *type){
    std::cout << typeid(T).name() <<"_new() called" << std::endl;
    DObject<T> *self;

        self = (DObject<T>*) type->tp_alloc(type, 0);
        if (self != NULL) {
            self->m_ads = NULL;
            self->m_dtype = NULL;
        } else {
            return PyErr_NoMemory();
        }
       return (PyObject*) self;
}

template <typename T>
int dtype_init(PyObject *self, PyObject *args, PyObject *kwds){
    std::cout << typeid(T).name() <<"_init() called" << std::endl;
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

    DObject<T> *self_dtype = reinterpret_cast<DObject<T>*>(self);
    uint8_t b_netId[6] = { 0 };
    std::string s_amsAddr(amsAddr);
    std::string delimiter = ".";

    size_t pos = 0;
    std::string token;
    while ((pos = s_amsAddr.find(delimiter)) != std::string::npos) {
        token = s_amsAddr.substr(0, pos);
        std::cout << token << std::endl;
        s_amsAddr.erase(0, pos + delimiter.length());
    }
    std::cout << s_amsAddr << std::endl;

    int ams_b_cnt = 0;
    for (uint8_t* it = (uint8_t*)amsAddr; *it; ++it) {
        if (isdigit(*it)) {
            b_netId[ams_b_cnt++] = *it;
        }
    }

    

    static const AmsNetId remoteNetId{ (unsigned char)b_netId };

#if defined(USE_TWINCAT_ROUTER)
    
    self_dtype->m_ads = (TC1000AdsClient*)PyObject_Malloc(sizeof(TC1000AdsClient));
    if (!self_dtype->m_ads) {
        PyErr_SetNone(PyExc_MemoryError);
        return -1;
    }
    //try {
    //    new (self_dtype->m_ads) TC1000AdsClient(remoteNetId);
    //}
    //catch (const AdsException& ex) {
    //    std::cout << "ADS Exception" << std::endl;
    //    PyObject_Free(self_dtype->m_ads);
    //    self_dtype->m_ads = NULL;
    //    PyErr_SetString(PyExc_RuntimeError, ex.what());
    //    return -1;
    //}
    //catch (const std::runtime_error& ex) {
    //    std::cout << "Runtime error" << std::endl;
    //    PyObject_Free(self_dtype->m_ads);
    //    self_dtype->m_ads = NULL;
    //    PyErr_SetString(PyExc_RuntimeError, ex.what());
    //    return -1;
    //}
#else

    // Memory allocation for ADS instnace

    self_dtype->m_ads = (BasicADS*)PyObject_Malloc(sizeof(GenericAdsClient));
    if(!self_dtype->m_ads){
        PyErr_SetNone(PyExc_MemoryError);
        return -1;
    }

    try{
        new (self_dtype->m_ads) GenericAdsClient(remoteNetId, ipAddr);
    } catch (const AdsException &ex) {
        std::cout << "ADS Exception" << std::endl;
        PyObject_Free(self_dtype->m_ads);
        self_dtype->m_ads = NULL;
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return -1;
    } catch (const std::runtime_error &ex) {
        std::cout << "Runtime error" << std::endl;
        PyObject_Free(self_dtype->m_ads);
        self_dtype->m_ads = NULL;
        PyErr_SetString(PyExc_RuntimeError, ex.what());
        return -1;
    }
#endif

    // Memory allocation for Device Manager type
    self_dtype->m_dtype = (T*)PyObject_Malloc(sizeof(T));
    if(!self_dtype->m_dtype){
        PyErr_SetNone(PyExc_MemoryError);
        return -1;
    }

	try {
        new (self_dtype->m_dtype) T(*self_dtype->m_ads);
	}
	catch (const DeviceManager::AdsException& ex) {
        PyErr_SetString(PyExc_RuntimeError, ex.what());
		return -1;
	}

	if (!self_dtype->m_dtype) {
        PyErr_SetString(PyExc_RuntimeError, "Module not available on target");
		return -1;
	}

    return 0;
}

template<typename T>
void dtype_dealloc(PyObject *self){
    std::cout << typeid(T).name() <<"_dealloc() called" << std::endl;

    DObject<T> *self_dtype = reinterpret_cast<DObject<T>*>(self);

    if(self_dtype->m_dtype){
        self_dtype->m_dtype->~T();
        PyObject_Free(self_dtype->m_dtype);
    }

    if(self_dtype->m_ads){
#if defined(USE_TWINCAT_ROUTER)
        self_dtype->m_ads->~TC1000AdsClient();
#else
        self_dtype->m_ads->~BasicADS();
#endif
        PyObject_Free(self_dtype->m_ads);
    }
}
#endif