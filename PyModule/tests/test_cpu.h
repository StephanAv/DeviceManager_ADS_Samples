#ifndef TEST_CPU_H
#define TEST_CPU_H

#include <Python.h>
#include <iostream>
#include "object.h"

void init_cpu(PyObject *pFunc){

    if(pFunc == NULL) return;

    PyObject *pMyClass = PyObject_CallObject(pFunc, NULL);
    if (!pMyClass) {
        std::cerr << "Cannot call example()" << std::endl;
    } else {
        std::cout << "CPU() called" << std::endl;
    }

}

#endif