#include <Python.h>
#include "cpu.h"
#include "object.h"
#include "py_cpu.h"
#include "ads_exception.h"
#include "pyerrors.h"

#include <cstdint>
#include <iostream>
#include <python3.9/unicodeobject.h> // ?
#include <cassert>
#include <stdexcept>
#include "ads_py_error.h"

PyObject* getTemp(PyObject *self, PyObject *args)
{
    CpuType* self_cpu = reinterpret_cast<CpuType*>(self);

    int16_t temp = 0;
    int32_t ret = self_cpu->m_dtype->getTemp(temp);

    if(ret){
        PyErr_SetObject(PyExc_RuntimeError, adsErrorStr(ret));
        return NULL;
    }

    return PyLong_FromUnsignedLong(temp);
}
