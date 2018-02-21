cmake_minimum_required(VERSION 3.1)

project(BackendAbPyToolsCPP)

set(ABPYTOOLS_CPP_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/)

include_directories(
        ${PYTHON_INCLUDE_DIRS}
        ${ABPYTOOLS_CPP_DIRS}
        ${BACKEND_UTILS_DIRS}
        ${BOOST_INCLUDE_DIRS})

set(SOURCE_FILES
        src/chain.cpp
        include/chain.h)

set(TARGET_NAME AbPyToolsInterfaceLib)

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME}
        ${EXCEPTIONS_LIB}
        ${PYTHON_LIBRARY})

add_subdirectory(tests)

add_test(NAME SimpleTest COMMAND SimpleTest
         WORKING_DIRECTORY ${BackendAbPyToolsCPPTests_SOURCE_DIR})