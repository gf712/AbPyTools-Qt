project(DecompositionAlgorithms)

set(DECOMPOSITION_ALGO_DIR include CACHE INTERNAL "decomposition algorithms include lib")

set(SOURCE_FILES
        src/pca.cpp)

set(TARGET_NAME DECOMPOSITION_ALGORITHMS_LIBRARIES)

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "decomposition-algorithms")

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

add_test(NAME PCATestSuite COMMAND PCATest
         WORKING_DIRECTORY ${PCATests_BIN_DIR})