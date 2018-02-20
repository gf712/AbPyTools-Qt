cmake_minimum_required(VERSION 3.1)

project(BackendUtils)

set(BACKEND_UTILS_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(TARGET_NAME EXCEPTIONS_LIB PARENT_SCOPE)

include_directories(BACKEND_UTILS_DIRS)

add_library(EXCEPTIONS_LIB STATIC
        include/exception.h
        src/exception.cpp)
