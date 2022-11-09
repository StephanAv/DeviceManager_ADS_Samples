#include <Python.h>
#include "file_system_object.h"
#include "py_fso.h"
#include "ads_py_error.h"

PyObject* dir(PyObject* self, PyObject* args)
{
    FsoType* self_tc = reinterpret_cast<FsoType*>(self);

    char* path = NULL;
    if (!PyArg_ParseTuple(args, "s", &path)) {
        return NULL;
    }

    std::vector<std::string> folders;
    std::vector<std::string> files;

    int32_t ret = self_tc->m_dtype->dir(path, folders, files);
    if (ret) {
        PyErr_SetObject(PyExc_RuntimeError, adsErrorStr(ret));
        return NULL;
    }

    // Process folders 
    PyObject* pyListFolders = PyList_New(folders.size());

    for (Py_ssize_t i = 0; i < folders.size(); i++) {
            PyObject* pyFolder = PyUnicode_FromString(folders[i].c_str());
            if (!pyFolder) {
                continue;
            }
            PyList_SetItem(pyListFolders, i, pyFolder);
    }

    // Process files
    PyObject* pyListFiles = PyList_New(files.size());

    for (Py_ssize_t j = 0; j < files.size(); j++) {
        PyObject* pyFile = PyUnicode_FromString(files[j].c_str());
        if (!pyFile) {
            continue;
        }
        PyList_SetItem(pyListFiles, j, pyFile);
    }

    return  Py_BuildValue("OO", pyListFolders, pyListFiles);
}