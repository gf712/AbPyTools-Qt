cmake_minimum_required(VERSION 3.1)

enable_testing()

set (CMAKE_CXX_STANDARD 11)

include("cmake/HunterGate.cmake")

# 1. Try to detect hunter by:
#   * cmake variable
#   * environment variable
#   * in HOME (`.hunter` directory)
#   * in SYSTEMDRIVE (`.hunter` directory, windows only)
#   * in USERPROFILE (`.hunter` directory, windows only)
# 2. if failed, download it
# 3. set HUNTER_GATE_* variables
# 4. include master file: 'include(${HUNTER_SELF}/cmake/Hunter)
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.18.12.tar.gz"
        SHA1 "7e8c74787e08c476484d3e5106524fe7a5a0cc56"
)

set(PYTHON_PATH $ENV{HOME}/anaconda3 CACHE FILEPATH "Python path")

message("python path ${PYTHON_PATH}")

project(AbPyTools-Qt)

hunter_add_package(Boost COMPONENTS test)
find_package(Boost CONFIG REQUIRED COMPONENTS unit_test_framework)

set(BOOST_INCLUDE_DIRS ${BOOST_ROOT}/include)

#find_package(PythonLibs)

# TODO: automate path finding with anaconda
set(PYTHON_INCLUDE_DIRS ${PYTHON_PATH}/include/python3.6m)
set(PYTHON_LIBRARIES ${PYTHON_PATH}/lib/libpython3.6m.so)

add_subdirectory(backend/utils)
add_subdirectory(backend/abpytools)
