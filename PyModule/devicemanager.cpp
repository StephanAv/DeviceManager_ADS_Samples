#include <Python.h>


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

    return module;
}