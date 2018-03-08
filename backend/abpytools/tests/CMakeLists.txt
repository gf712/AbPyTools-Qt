cmake_minimum_required(VERSION 3.1)

project(BackendAbPyToolsCPPTests)

add_executable(BackendAbPyToolsCPPTest
        AbPyToolsPyCInterfaceTestSuite.cpp
        )

target_include_directories(BackendAbPyToolsCPPTest PRIVATE
        ${Boost_INCLUDE_DIRS}
        )

target_link_libraries(BackendAbPyToolsCPPTest
        ABPYTOOLSINTERFACE_LIBRARIES
#        ${PYTHON_LIBRARY}
#        ABPYTOOLSCPP_PARSER_LIBRARIES
        Boost::python3
        Boost::unit_test_framework)
