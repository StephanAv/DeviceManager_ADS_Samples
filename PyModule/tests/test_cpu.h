#ifndef TEST_CPU_H
#define TEST_CPU_H

#include <Python.h>
#include <iostream>
#include <cassert>
#include "abstract.h"
#include "object.h"

PyObject* cpu_init(PyObject *pFunc){

    assert(pFunc);

    PyObject *amsAddr = PyUnicode_FromString("5.80.201.232.1.1");
    PyObject *ipAddr  = PyUnicode_FromString("192.168.1.98");
    //PyObject *ipAddr  = PyUnicode_FromString("192.168.1");
    PyObject *argList = PyTuple_Pack(2, amsAddr, ipAddr);
    assert(argList);
    
    if(!PyTuple_Check(argList)){
        std::cout << "Failed to create arglist" << std::endl;
    }


    PyObject *pCpuInstance = PyObject_CallObject(pFunc, argList);

    if (!pCpuInstance) {
        std::cerr << "Cannot call example()" << std::endl;
        return NULL;
    } else {
        std::cout << "CPU() called" << std::endl;
        return pCpuInstance;
    }

}

void test_cpu_getTemp(PyObject *CPU){
    assert(CPU);

    PyObject *cpuTemperature = PyObject_CallMethodNoArgs(CPU, PyUnicode_FromString("getTemp"));
    if(!cpuTemperature){
        PyErr_Print();
    }
    //PyObject* attrCpuTemp =
    //PyObject *cpuTemperature = PyObject_CallMethod(CPU, "getTemp", NULL);
    if(PyLong_Check(cpuTemperature)){
        std::cout << "CPU temperature: " << PyLong_AsLong(cpuTemperature) << std::endl;
    }
}
#endif