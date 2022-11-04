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

PyObject* getTemp(PyObject *self, PyObject *args);

static struct PyMemberDef CpuType_member[] = {
    //{"value", T_INT, offsetof(CpuType, value)},
    {NULL} /* Sentinel */
};

static PyMethodDef CpuType_methods[] = {
    {"getTemp", (PyCFunction)getTemp, METH_NOARGS, "Returns the CPU temperature"},
    //{"getTemp", (PyCFunction)getTemp, METH_CLASS | METH_NOARGS, "Returns the CPU temperature"},
    {NULL, NULL} /* Sentinel */
};

static PyType_Slot CpuType_slots[] = {
    {Py_tp_new, (void*)dtype_new<DeviceManager::CPU>},
    {Py_tp_init, (void*)dtype_init<DeviceManager::CPU>},
    {Py_tp_dealloc, (void*)dtype_dealloc<DeviceManager::CPU>},
    {Py_tp_members, CpuType_member},
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