project(BackendAbPyToolsCPP)

set(ABPYTOOLS_CPP_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "abpytools cpp include lib")

set(SOURCE_FILES
        src/chain.cpp)

set(TARGET_NAME AbPyToolsInterfaceLib)

include_directories(${ABPYTOOLS_CPP_PARSER_DIR})

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES})

message(${PYTHON_NUMPY_INCLUDE_DIR})

target_include_directories(${TARGET_NAME}
        INTERFACE include/)

target_include_directories(${TARGET_NAME} SYSTEM
        PUBLIC ${PYTHON_INCLUDE_DIRS}
        ${BACKEND_UTILS_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${PYTHON_NUMPY_INCLUDE_DIR})

target_link_libraries(${TARGET_NAME}
        ${EXCEPTIONS_LIB}
        AbPyToolsCppParserLib
        ${PYTHON_LIBRARY})

add_subdirectory(tests)

add_test(NAME BackendAbPyToolsCPPTest COMMAND BackendAbPyToolsCPPTest
        WORKING_DIRECTORY ${BackendAbPyToolsCPPTests_BIN_DIR})