#ifndef TEST_CPU_H
#define TEST_CPU_H

#include <Python.h>
#include <iostream>
#include <cassert>
#include "object.h"

void init_cpu(PyObject *pFunc){

    if(pFunc == NULL) return;

    PyObject *amsAddr = PyUnicode_FromString("5.80.201.232.1.1");
    //PyObject *ipAddr  = PyUnicode_FromString("192.168.1.98");
    PyObject *ipAddr  = PyUnicode_FromString("192.168.1");
    PyObject *argList = PyTuple_Pack(2, amsAddr, ipAddr);
    assert(argList);
    
    if(!PyTuple_Check(argList)){
        std::cout << "Failed to create arglist" << std::endl;
    }


    PyObject *pMyClass = PyObject_CallObject(pFunc, argList);

    if (!pMyClass) {
        std::cerr << "Cannot call example()" << std::endl;
    } else {
        std::cout << "CPU() called" << std::endl;
    }

}

#endif