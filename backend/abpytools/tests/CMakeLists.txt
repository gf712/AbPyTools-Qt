cmake_minimum_required(VERSION 3.1)

project(BackendAbPyToolsCPPTests)

add_executable(BackendAbPyToolsCPPTest
        AbPyToolsPyCInterfaceTestSuite.cpp
        )

target_include_directories(BackendAbPyToolsCPPTest PRIVATE
        ${Boost_INCLUDE_DIRS}
        ../include
        )

target_link_libraries(BackendAbPyToolsCPPTest
        AbPyToolsInterfaceLib
        ${PYTHON_LIBRARY}
        Boost::python3
        Boost::unit_test_framework)
