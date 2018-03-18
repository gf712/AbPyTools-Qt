project(AbPyToolsCPPTests)

add_executable(AbPyToolsCPPTest
        AbPyToolsCPPTestSuite.cpp
        )

target_link_libraries(AbPyToolsCPPTest
        ABPYTOOLSCPP_LIBRARIES
        Boost::unit_test_framework
        )
