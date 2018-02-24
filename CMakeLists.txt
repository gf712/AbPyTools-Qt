cmake_minimum_required(VERSION 3.1)

enable_testing()

# C++ code is all written in c++ 11 standard
set (CMAKE_CXX_STANDARD 11)

############################################################################################
#                                       HUNTER
############################################################################################

# get hunter for package management in cmake
include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.19.125.tar.gz"
        SHA1 "371aef6239eff8639fe2cd94afef0f4d9f733302"
        LOCAL
)


# project name
project(AbPyTools-Qt)

# find python3.5 or greater
find_package(PythonLibs 3.5 REQUIRED)

# get boost and build unit_test_framework and python3 -> requires python3 interpreter
hunter_add_package(Boost COMPONENTS test python filesystem)
hunter_add_package(Qt)

find_package(Boost CONFIG COMPONENTS REQUIRED unit_test_framework python3 filesystem system)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

############################################################################################
#                                       DECLARATIONS
############################################################################################


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -fPIC -O0")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Numpy REQUIRED)

add_subdirectory(backend)
add_subdirectory(gui)
