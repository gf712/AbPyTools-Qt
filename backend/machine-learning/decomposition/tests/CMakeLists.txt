project(PCATests)

add_executable(PCATest
        PCATestSuite.cpp
        )

target_link_libraries(PCATest
        DECOMPOSITION_ALGORITHMS_LIBRARIES
        Boost::unit_test_framework
        )
