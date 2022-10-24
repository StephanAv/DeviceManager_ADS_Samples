#include <Python.h>
#include "py_cpu.h"
#include "modsupport.h"
#include "object.h"

typedef struct {
    PyObject_HEAD
    int value;
} DevManObject;

static PyObject* division(PyObject *self, PyObject *args) {
    long dividend, divisor;
    if (!PyArg_ParseTuple(args, "ll", &dividend, &divisor)) {
        return NULL;
    }
    if (0 == divisor) {
        PyErr_Format(PyExc_ZeroDivisionError, "Dividing %d by zero!", dividend);
        return NULL;
    }
    return PyLong_FromLong(dividend / divisor);
}

PyMethodDef method_table[] = {
    {"division", (PyCFunction) division, METH_VARARGS, "Method docstring"},
    {NULL, NULL, 0, NULL} // Sentinel value ending the table
};

PyModuleDef devman_module = {
    PyModuleDef_HEAD_INIT,
    "DeviceManager", // Module name
    "Allows to access various properties of Beckhoff IPCs",
    -1,   // Optional size of the module state memory
    method_table,
    NULL, // Optional slot definitions
    NULL, // Optional traversal function
    NULL, // Optional clear function
    NULL  // Optional module deallocation function
};

PyMODINIT_FUNC 
PyInit_DeviceManager(void) {

    PyObject* module = PyModule_Create(&devman_module);

    // Create and add CPU type
    PyObject *cpu_type = PyType_FromSpec(&CpuType_spec);
    if (cpu_type == NULL){
        Py_DecRef(module);
        return NULL;
    }

    if(PyModule_AddObject(module, "CPU", cpu_type) < 0){
        Py_DECREF(cpu_type);
        Py_DECREF(module);
        return NULL;
    }
    return module;
}