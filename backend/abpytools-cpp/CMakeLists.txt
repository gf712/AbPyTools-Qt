project(BackendAbPyToolsPureCPP)

set(SOURCE_FILES
        src/chainCollectionCPP.cpp
        src/queryAbnum.cpp)

set(TARGET_NAME AbPyToolsCPPLib)

message("ABPYTOOLS_CPP_DIRS: ${ABPYTOOLS_CPP_DIRS}")

include_directories(include/)

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME}
        ${AbPyToolsInterfaceLib}
        ${PYTHON_LIBRARY}
        )

target_include_directories(${TARGET_NAME} PRIVATE
        ${ABPYTOOLS_CPP_DIRS}
        ${PYTHON_INCLUDE_DIRS})