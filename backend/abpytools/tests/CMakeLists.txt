cmake_minimum_required(VERSION 3.1)

project(BackendAbPyToolsCPPTests)

add_executable(SimpleTest
        simpleTest.cpp)

target_include_directories(SimpleTest PRIVATE
        ${BOOST_INCLUDE_DIRS}
        ${ABPYTOOLS_CPP_DIRS}
        )

target_link_libraries(SimpleTest AbPyToolsInterfaceLib)

#target_link_libraries(SimpleTest
#        PRIVATE AbPyToolsInterfaceLib Boost::Test)