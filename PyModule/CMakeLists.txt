cmake_minimum_required(VERSION 3.14)
#project(DeviceManager)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#find_package(PythonInterp 3.6 REQUIRED)
#find_package(PythonLibs 3.6 REQUIRED)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

#add_executable(PyDebug "pydbg.cpp")

set(SRCS devicemanager.cpp types/py_cpu.cpp)
add_library(PyDeviceManager SHARED ${SRCS})
add_executable(PyDebug "debug.cpp")
#add_library(PyDeviceManager SHARED )
#find_package(PythonLibs REQUIRED)
#include_directories(${PYTHON_INCLUDE_DIRS})
#target_link_libraries(PyDeviceManager ${PYTHON_LIBRARIES})


if (WIN32)
    add_compile_definitions(USE_TWINCAT_ROUTER)
endif()

# das wird benötigt
set_target_properties(
    PyDeviceManager
    PROPERTIES
        PREFIX ""
        OUTPUT_NAME "DeviceManager"
        LINKER_LANGUAGE C # Egal ob hier C oder CXX steht
        LINK_LIBRARIES DeviceManager
        INCLUDE_DIRECTORIES "${PYTHON_INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}/types" # vscode/codium does not recognize this
)
set_target_properties(
    PyDebug
    PROPERTIES
        OUTPUT_NAME "PyDebug"
        LINKER_LANGUAGE C # Egal ob hier C oder CXX steht
        INCLUDE_DIRECTORIES "/usr/include/python3.9;${PYTHON_INCLUDE_DIR};${CMAKE_CURRENT_SOURCE_DIR}/tests"
        LINK_LIBRARIES "${PYTHON_LIBRARIES}"
)
#;${CMAKE_SOURCE_DIR}/ADS
#set(SRCS "devicemanager.cpp" "cpu.cpp")

if (WIN32)
    set_target_properties(
        PyDeviceManager
        PROPERTIES
            SUFFIX ".pyd" # Win32 https://stackoverflow.com/questions/31038963/how-do-you-rename-a-library-filename-in-cmake
    )
endif()

#set_target_properties(
#    PyDebug
#    PROPERTIES
#        PREFIX ""
#        OUTPUT_NAME "PyDebug"
#        LINKER_LANGUAGE C # Egal ob hier C oder CXX steht
#    )
