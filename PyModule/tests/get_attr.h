#ifndef GET_FUNC_H
#define GET_FUNC_H

#include "object.h"
#include <Python.h>
#include <iostream>

PyObject* get_attr(PyObject *pmodule, const char* fName){

    // Hasattr first
    PyObject* pAttr = PyObject_GetAttrString(pmodule, fName);
    if (!pAttr) {
        std::cerr << "Cannot find function " << fName << std::endl;
        return NULL;
    }

    // if (!PyCallable_Check(pFunc)) {
    //     std::cerr << "Function " << fName << " is not calable" << std::endl;
    //     return NULL;
    // }
    return pAttr;
}



#endif