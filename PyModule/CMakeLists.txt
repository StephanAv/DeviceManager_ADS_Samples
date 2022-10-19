cmake_minimum_required(VERSION 3.14)
#project(DeviceManager)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#find_package(PythonInterp 3.6 REQUIRED)
#find_package(PythonLibs 3.6 REQUIRED)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
set(SRCS "devicemanager.cpp" )
add_library(PyDeviceManager SHARED ${SRCS})
#add_executable(PyDebug "pydbg.cpp")

#find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
#target_link_libraries(PyDebug ${PYTHON_LIBRARIES})

# das wird benötigt
set_target_properties(
    PyDeviceManager
    PROPERTIES
        PREFIX ""
        OUTPUT_NAME "DeviceManager"
        LINKER_LANGUAGE C # Egal ob hier C oder CXX steht
    )
#set_target_properties(
#    PyDebug
#    PROPERTIES
#        PREFIX ""
#        OUTPUT_NAME "PyDebug"
#        LINKER_LANGUAGE C # Egal ob hier C oder CXX steht
#    )
