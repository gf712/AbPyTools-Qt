cmake_minimum_required(VERSION 3.6)

enable_testing()

# C++ code is all written in c++ 11 standard
set (CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

############################################################################################
#                                       HUNTER
############################################################################################

#set(HUNTER_ENABLED ON CACHE BOOL "whether to use hunter to build dependencies with hunter")

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

#if (NOT ${HUNTER_ENABLED})
#    list(APPEND ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Hunter/disabled-mode")
#endif()

find_package(Boost CONFIG COMPONENTS REQUIRED unit_test_framework python3 filesystem system)
find_package(Qt5 CONFIG COMPONENTS REQUIRED Widgets Core)

find_package(Numpy REQUIRED)
find_package(MLPACK REQUIRED)

############################################################################################
#                                     DECLARATIONS
############################################################################################


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -fPIC -O0")
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(ADD_QT_QPA_FONTDIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

############################################################################################
#                                  ADD PROJECT DIRS
############################################################################################

add_subdirectory(backend)
add_subdirectory(gui)

############################################################################################
#                                   FINAL MESSAGES
############################################################################################

#message("$ENV{QT_QPA_FONTDIR}")

if (${ADD_QT_QPA_FONTDIR})
    message("\n           ----------------- CUSTOM VARIABLES --------------------

-- Variables to be added at build time to .bashrc file:

   - QT_QPA_FONTDIR=${QT_ROOT}/lib/fonts
     Disable this behaviour with -DADD_QT_QPA_FONTDIR=OFF

           -------------------------------------------------------
")
    # add QT_QPA_FONTDIR to .bashrc file
#    file(APPEND $ENV{HOME}/.bashrc "\n# added by AbPyTools-Qt installer
#export QT_QPA_FONTDIR=\"${QT_ROOT}/lib/fonts\"")
endif()

############################################################################################
#                                        END
############################################################################################