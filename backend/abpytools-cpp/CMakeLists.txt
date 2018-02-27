project(BackendAbPyToolsPureCPP)

set(INCLUDE_FILES include/chainCollectionCPP.h
        )

set(ABPYTOOLS_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "abpytools-cpp include lib")

set(SOURCE_FILES
        src/chainCollectionCPP.cpp
        src/queryAbnum.cpp)

set(TARGET_NAME AbPyToolsCPPLib)

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME}
        AbPyToolsInterfaceLib
        )

target_include_directories(${TARGET_NAME}
        INTERFACE include/
        )

target_include_directories(${TARGET_NAME} SYSTEM
        PUBLIC ${PYTHON_INCLUDE_DIRS}
        ${ABPYTOOLS_CPP_DIR}
        ${PYTHON_NUMPY_INCLUDE_DIR}
        )

add_subdirectory(tests)

add_test(NAME AbPyToolsCPPTestSuite COMMAND AbPyToolsCPPTest
         WORKING_DIRECTORY ${AbPyToolsCPPTests_BIN_DIR})