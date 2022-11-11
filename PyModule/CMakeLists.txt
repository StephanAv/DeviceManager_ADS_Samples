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

set(SRCS    devicemanager.cpp
            types/py_cpu.cpp
            types/py_twincat.cpp
            types/py_fso.cpp
            types/py_miscellaneous.cpp
)

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
#set(HEADER_FILES ${PYTHON_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/types )

# TODO 
# https://cmake.org/cmake/help/v3.14/prop_tgt/EXCLUDE_FROM_ALL.html

target_link_libraries(PyDeviceManager PRIVATE DeviceManager ${PYTHON_LIBRARIES})
target_link_libraries(PyDebug PRIVATE DeviceManager ${PYTHON_LIBRARIES})

set_target_properties(
    PyDeviceManager
    PROPERTIES
        PREFIX ""
        EXCLUDE_FROM_ALL YES
        OUTPUT_NAME "DeviceManager"
        LINK_DIRECTORIES ${PROJECT_BINARY_DIR}
        INCLUDE_DIRECTORIES "${PYTHON_INCLUDE_DIRS};${CMAKE_CURRENT_SOURCE_DIR}/types;${PROJECT_SOURCE_DIR}/ADS;${PROJECT_SOURCE_DIR}/Areas" # vscode/codium does not recognize this
)
set_target_properties(
    PyDebug
    PROPERTIES
        EXCLUDE_FROM_ALL YES
        OUTPUT_NAME "PyDebug"
        INCLUDE_DIRECTORIES "/usr/include/python3.9;${PYTHON_INCLUDE_DIR};${CMAKE_CURRENT_SOURCE_DIR}/tests"
)


if (WIN32)
    target_include_directories(PyDeviceManager PRIVATE "C:\\TwinCAT\\AdsApi\\TcAdsDll\\Include")
    target_link_libraries(PyDeviceManager PUBLIC TcAdsDll.lib)
    target_link_directories(PyDeviceManager PRIVATE "C:\\TwinCAT\\AdsApi\\TcAdsDll\\x64\\lib")

    target_include_directories(PyDebug PRIVATE "C:\\TwinCAT\\AdsApi\\TcAdsDll\\Include")
    target_link_libraries(PyDebug PUBLIC TcAdsDll.lib)
    target_link_directories(PyDebug PRIVATE "C:\\TwinCAT\\AdsApi\\TcAdsDll\\x64\\lib")
    
    set_target_properties(
        PyDeviceManager
        PROPERTIES
            SUFFIX ".pyd"
    )
endif()