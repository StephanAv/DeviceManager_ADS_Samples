#include <Python.h>
#include <iostream>
#include <cstddef>

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

    //test_division(get_func(pmodule, "division"));
    //test_setString(get_func(pmodule, "setString"));
    //test_myclass(get_func(pmodule, "init"));

    return 0;
}