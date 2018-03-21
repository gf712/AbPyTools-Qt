project(BackendAbPyToolsCPP)

set(ABPYTOOLS_CPP_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "abpytools cpp include lib")

set(SOURCE_FILES
        src/chain.cpp)

set(TARGET_NAME ABPYTOOLSINTERFACE_LIBRARIES)

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "abpytools-interface")

target_include_directories(${TARGET_NAME}
        INTERFACE include/)

target_include_directories(${TARGET_NAME} SYSTEM
        PUBLIC ${PYTHON_INCLUDE_DIRS}
        ${BACKEND_UTILS_DIRS}
#        ${BOOST_INCLUDE_DIRS}
        ${PYTHON_NUMPY_INCLUDE_DIR})

target_link_libraries(${TARGET_NAME}
        ${ABPYTOOLSCPP_EXCEPTIONS_LIBRARIES}
        ABPYTOOLSCPP_PARSER_LIBRARIES
        ${PYTHON_LIBRARY}
        Boost::python3)

add_subdirectory(tests)

add_test(NAME BackendAbPyToolsCPPTest COMMAND BackendAbPyToolsCPPTest
         WORKING_DIRECTORY ${BackendAbPyToolsCPPTests_BIN_DIR})