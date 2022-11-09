#ifndef PY_FSO_H
#define PY_FSO_H

#include <Python.h>
#include "py_slot_templates.h"
#include "file_system_object.h"

typedef DObject<DeviceManager::FileSystemObject> FsoType;

PyObject* dir(PyObject* self, PyObject* args);

static PyMethodDef FsoType_methods[] = {
    {"dir", (PyCFunction)dir, METH_VARARGS, "List files and directories"},
    //{"getUsage", (PyCFunction)getUsage, METH_NOARGS, "Returns the current CPU usage [%]"},
    //{"getTemp", (PyCFunction)getTemp, METH_NOARGS, "Returns the CPU temperature [?C]"},
    {NULL, NULL} /* Sentinel */
};

static PyType_Slot FsoType_slots[] = {
    {Py_tp_new, (void*)dtype_new<DeviceManager::FileSystemObject>},
    {Py_tp_init, (void*)dtype_init<DeviceManager::FileSystemObject>},
    {Py_tp_dealloc, (void*)dtype_dealloc<DeviceManager::FileSystemObject>},
    {Py_tp_methods, FsoType_methods},
    {0, 0} /* Sentinel */
};

static PyType_Spec FsoType_spec = {
    "FileSystem", // tp_name
    #if defined(USE_TWINCAT_ROUTER)
    sizeof(FsoType) + sizeof(TC1000AdsClient), // tp_basicsize
#else
    sizeof(FsoType) + sizeof(GenericAdsClient),
#endif
    0, // tp_itemsize : All instances have the same size
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    FsoType_slots
};


#endif // !PY_FSO_H