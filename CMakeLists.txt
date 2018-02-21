cmake_minimum_required(VERSION 3.1)

enable_testing()

# C++ code is all written in c++ 11 standard
set (CMAKE_CXX_STANDARD 11)

# get hunter for package management in cmake
include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.18.12.tar.gz"
        SHA1 "7e8c74787e08c476484d3e5106524fe7a5a0cc56"
)

# project name
project(AbPyTools-Qt)

# find python3.5 or greater
find_package(PythonLibs 3.5 REQUIRED)

# get boost and build unit_test_framework and python3 -> requires python3 interpreter
hunter_add_package(Boost COMPONENTS test python)
find_package(Boost COMPONENTS REQUIRED unit_test_framework python3)

add_subdirectory(backend/utils)
add_subdirectory(backend/abpytools)
