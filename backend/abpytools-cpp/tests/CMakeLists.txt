project(AbPyToolsCPPTests)

add_executable(AbPyToolsCPPTest
        AbPyToolsCPPTestSuite.cpp
        )

target_include_directories(AbPyToolsCPPTest PRIVATE
        ${Boost_INCLUDE_DIRS}
        )

target_link_libraries(AbPyToolsCPPTest
        AbPyToolsCPPLib
        Boost::python3
        Boost::unit_test_framework)
