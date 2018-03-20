project(ClusterAlgorithms)

set(CLUSTER_ALGO_DIR include CACHE INTERNAL "cluster algorithms include lib")

set(SOURCE_FILES
        src/kmeans.cpp)

set(TARGET_NAME CLUSTER_ALGORITHMS_LIBRARIES)

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "cluster-algorithms")

target_include_directories(${TARGET_NAME}
        INTERFACE include/
        )

target_include_directories(${TARGET_NAME} SYSTEM
        PUBLIC
        ${MLPACK_INCLUDE_DIRS}
        )

target_link_libraries(${TARGET_NAME}
        ${MLPACK_LIBRARIES}
        ${ARMADILLO_LIBRARIES}
        )

add_subdirectory(tests)

add_test(NAME ClusterTestSuite COMMAND ClusterTest
         WORKING_DIRECTORY ${ClusterTests_BIN_DIR})