cmake_minimum_required(VERSION 3.1)

enable_testing()

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

project(AbPyTools-Qt)

hunter_add_package(Boost COMPONENTS test)
find_package(Boost CONFIG REQUIRED COMPONENTS unit_test_framework)

set(BOOST_INCLUDE_DIRS ${BOOST_ROOT}/include)

#find_package(PythonLibs)

# TODO: automate path finding with anaconda
set(PYTHON_INCLUDE_DIRS /home/gil/anaconda3/include/python3.6m)
set(PYTHON_LIBRARIES /home/gil/anaconda3/lib/libpython3.6m.so)

add_subdirectory(backend/utils)
add_subdirectory(backend/abpytools)
