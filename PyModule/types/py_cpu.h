#ifndef PY_CPU_H
#define PY_CPU_H

#include <Python.h>

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
typedef struct {
    PyObject_HEAD
    BasicADS* m_ads;
    std::optional<DeviceManager::CPU> m_cpu;
} CpuType;
// https://docs.python.org/release/2.6/_sources/extending/newtypes.txt
// TODO" tp_new method hinzufuegen um einen initialwert zu setzen (z.b. NULL)
// die tp_init funktion kann mehrfach aufgerufen werden

int CpuType_init(PyObject *self, PyObject *args, PyObject *kwds);
void CpuType_dealloc(CpuType *self);

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
    {Py_tp_init, (void*)CpuType_init},
    {Py_tp_dealloc, (void*)CpuType_dealloc},
    {Py_tp_members, CpuType_member},
    {Py_tp_methods, CpuType_methods},
    {0, 0} /* Sentinel */
};

static PyType_Spec CpuType_spec = {
    "DeviceManager.CPU", // tp_name
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