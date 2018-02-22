cmake_minimum_required(VERSION 3.1)

project(BackendAbPyToolsCPP)

set(ABPYTOOLS_CPP_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include/ PARENT_SCOPE)

set(SOURCE_FILES
        src/chain.cpp)

set(TARGET_NAME AbPyToolsInterfaceLib)

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES})

target_include_directories(${TARGET_NAME} PUBLIC
        ${PYTHON_INCLUDE_DIRS}
        include/
        ${BACKEND_UTILS_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${PYTHON_NUMPY_INCLUDE_DIR}
        ${ABPYTOOLS_CPP_PARSER_DIR}
        )

target_link_libraries(${TARGET_NAME}
        ${EXCEPTIONS_LIB}
        ${AbPyToolsCppParserLib}
        ${PYTHON_LIBRARY})

add_subdirectory(tests)

add_test(NAME BackendAbPyToolsCPPTest COMMAND BackendAbPyToolsCPPTest
         WORKING_DIRECTORY ${BackendAbPyToolsCPPTests_SOURCE_DIR})