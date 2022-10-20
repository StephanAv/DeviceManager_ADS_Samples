#include "cpu.h"
#include <iostream>


int CpuType_init(PyObject *self, PyObject *args, PyObject *kwds){
    std::cout << "CpuType init() called" << std::endl;
    return 0;
}

void CpuType_dealloc(CpuType *self){
    std::cout << "CpuType dealloc() called" << std::endl;
}

PyObject* getTemp(PyObject *self, PyObject *args)
{
    return PyLong_FromUnsignedLong(123);
}
