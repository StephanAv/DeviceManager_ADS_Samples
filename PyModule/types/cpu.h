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

typedef struct {
    PyObject_HEAD
    int value;
} CpuType;


int CpuType_init(PyObject *self, PyObject *args, PyObject *kwds);
void CpuType_dealloc(CpuType *self);

PyObject* getTemp(PyObject *self, PyObject *args);


static struct PyMemberDef CpuType_member[] = {
    {"value", T_INT, offsetof(CpuType, value)},
    {NULL} /* Sentinel */
};

static PyMethodDef CpuType_methods[] = {
    {"getTemp", (PyCFunction)getTemp, METH_VARARGS | METH_CLASS, "Returns the CPU temperature"},
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
    "CPU", // tp_name
    sizeof(CpuType), // tp_basicsize
    0, // tp_itemsize
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    CpuType_slots
};

#endif