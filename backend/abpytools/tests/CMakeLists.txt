cmake_minimum_required(VERSION 3.1)

project(BackendAbPyToolsCPPTests)

add_executable(BackendAbPyToolsCPPTest
        AbPyToolsPyCInterfaceTestSuite.cpp
        )

target_link_libraries(BackendAbPyToolsCPPTest
        ABPYTOOLSINTERFACE_LIBRARIES
        Boost::python3
        Boost::unit_test_framework
        )
