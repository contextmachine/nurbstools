cmake_minimum_required(VERSION 3.4...3.18)


project(nurbstools)
add_subdirectory(party)

set(NURBSTOOLS_BUILD_ON_DLL OFF CACHE BOOL "Dynamically link OpenNURBS library")

# Add compiler definitions
if(NURBSTOOLS_BUILD_ON_DLL)
    set(BUILD_COMP_DEFS
            ${BUILD_COMP_DEFS}
            -DOPENNURBS_IMPORTS  # OpenNURBS dynamic linking
            )
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(BUILD_COMP_DEFS
            ${BUILD_COMP_DEFS}
            -DON_CLANG_CONSTRUCTOR_BUG  # OpenNURBS fix for Linux compilation
            )
endif()

find_package(pybind11 REQUIRED)

pybind11_add_module(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE opennurbs)
# NURBSTOOLS_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.

target_compile_definitions(${PROJECT_NAME}
        PRIVATE VERSION_INFO=${NURBSTOOLS_VERSION_INFO})