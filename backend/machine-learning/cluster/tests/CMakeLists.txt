project(ClusterTests)

add_executable(ClusterTest
        ClusterTestSuite.cpp
        )

target_link_libraries(ClusterTest
        CLUSTER_ALGORITHMS_LIBRARIES
        Boost::unit_test_framework
        )
