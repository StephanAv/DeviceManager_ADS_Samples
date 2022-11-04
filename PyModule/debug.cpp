#include <Python.h>
#include <iostream>
#include <cstddef>

#include "get_attr.h"
#include "test_cpu.h"

static void reprint(PyObject* obj) {
    PyObject* repr = PyObject_Repr(obj);
    PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
    const char* bytes = PyBytes_AS_STRING(str);

    printf("REPR: %s\n", bytes);

    Py_XDECREF(repr);
    Py_XDECREF(str);
}

int main(int argc, char *argv[], char *envp[])
{

    for (char **env = envp; *env != 0; env++)
    {
        char *thisEnv = *env;
        printf("%s\n", thisEnv);    
    }

    Py_SetProgramName(L"DebugPyDeviceManager");

    /* Initialize the Python interpreter.  Required.
       If this step fails, it will be a fatal error. */

    Py_Initialize();
    PyObject* sys_path = PySys_GetObject("path");
    PyList_Append(sys_path, PyUnicode_FromString("C:/Users/StephanA/source/repos/DeviceManager_ADS_Samples/out/build/x64-Debug/PyModule"));
    PyObject* sys_path_str = PyObject_Repr(sys_path);
    PyObject* pyStr = PyUnicode_AsEncodedString(sys_path_str, NULL, NULL);
    const char* strPath = PyBytes_AsString(pyStr);
    if (strPath) {
        std::cout << "PATH: " << strPath << std::endl;
    }

//    const char* script_path = R"(/home/stephan/Documents/PythonCppExtension/main.py)";
//    // https://docs.python.org/3/c-api/veryhigh.html#c.PyRun_SimpleFile
//    FILE* script = fopen(script_path, "r");
//    if(script){
//        PyRun_SimpleFile(script, "main.py");
//    }
//    fclose(script);

    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */

    PyObject *pmodule = PyImport_ImportModule("DeviceManager");
    if (!pmodule) {
        PyErr_Print();
        return -1;
    }
    PyObject* Cpu = get_attr(pmodule, "CPU");
    PyObject* cpuInstance = cpu_init(Cpu);
    test_cpu_getTemp(cpuInstance);
    return 0;
}