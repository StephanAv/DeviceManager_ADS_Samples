#include <Python.h>
#include "py_cpu.h"
#include "py_twincat.h"
#include "modsupport.h"
#include "object.h"

PyModuleDef devman_module = {
    PyModuleDef_HEAD_INIT,
    "DeviceManager", // Module name
    "Allows to access various properties of Beckhoff IPCs",
    -1,   // Optional size of the module state memory
    NULL, // Optional method definitions
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

    // Create and add TwinCAT type
    PyObject* tc_type = PyType_FromSpec(&TcType_spec);
    if (tc_type == NULL) {
        Py_DecRef(module);
        Py_DecRef(cpu_type);
        Py_DecRef(tc_type);
        return NULL;
    }

    if (PyModule_AddObject(module, "TwinCAT", tc_type) < 0) {
        Py_DECREF(tc_type);
        Py_DECREF(cpu_type);
        Py_DECREF(module);
        return NULL;
    }
    return module;
}