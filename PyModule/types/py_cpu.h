#ifndef PY_CPU_H
#define PY_CPU_H

#include <Python.h>
#include "py_slot_templates.h"
//#include <object.h>
//#include <longobject.h>
//#include <unicodeobject.h>
//#include <modsupport.h>
//#include <methodobject.h>
#include <tupleobject.h>
#include <structmember.h>
#include "cpu.h"
#include "methodobject.h"

#if defined(USE_TWINCAT_ROUTER)
	#include "TC1000_AdsClient.h"
#else
	#include "GenericAdsClient.h"
#endif

// https://cython.readthedocs.io/en/latest/src/userguide/extension_types.html
// typedef struct {
//     PyObject_HEAD
//     BasicADS* m_ads;
//     DeviceManager::CPU* m_dtype;
// } CpuType;


typedef DObject<DeviceManager::CPU> CpuType;

PyObject* getFreq(PyObject* self, PyObject* args);
PyObject* getUsage(PyObject* self, PyObject* args);
PyObject* getTemp(PyObject *self, PyObject *args);


static PyMethodDef CpuType_methods[] = {
    {"getFreq", (PyCFunction)getFreq, METH_NOARGS, "Returns the CPU frequency [MHz]"},
    {"getUsage", (PyCFunction)getUsage, METH_NOARGS, "Returns the current CPU usage [%]"},
    {"getTemp", (PyCFunction)getTemp, METH_NOARGS, "Returns the CPU temperature [�C]"},
    {NULL, NULL} /* Sentinel */
};

static PyType_Slot CpuType_slots[] = {
    {Py_tp_new, (void*)dtype_new<DeviceManager::CPU>},
    {Py_tp_init, (void*)dtype_init<DeviceManager::CPU>},
    {Py_tp_dealloc, (void*)dtype_dealloc<DeviceManager::CPU>},
    {Py_tp_methods, CpuType_methods},
    {0, 0} /* Sentinel */
};

static PyType_Spec CpuType_spec = {
    "CPU", // tp_name
    #if defined(USE_TWINCAT_ROUTER)
    sizeof(CpuType) + sizeof(TC1000AdsClient), // tp_basicsize
#else
    sizeof(CpuType) + sizeof(GenericAdsClient),
#endif
    0, // tp_itemsize : All instances have the same size
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    CpuType_slots
};

#endif