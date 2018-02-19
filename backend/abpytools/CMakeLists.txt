cmake_minimum_required(VERSION 3.1)

#find_package(PythonLibs REQUIRED)

# TODO: automate path finding with anaconda
set(PYTHON_INCLUDE_DIRS /home/gil/anaconda3/include/python3.6m)
set(PYTHON_LIBRARIES /home/gil/anaconda3/lib/libpython3.6m.so)

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