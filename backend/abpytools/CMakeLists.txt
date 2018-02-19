cmake_minimum_required(VERSION 3.1)

#message("${PYTHON_INCLUDE_DIRS}")

include_directories(${PYTHON_INCLUDE_DIRS}
        include/)

set(SOURCE_FILES
        src/chain.cpp)

set(TARGET_NAME AbPyToolsInterfaceLib)

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME}
        ${PYTHON_LIBRARIES})

add_executable(testExec src/main.cpp)

target_link_libraries(testExec ${TARGET_NAME})