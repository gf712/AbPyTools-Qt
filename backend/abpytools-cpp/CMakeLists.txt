project(BackendAbPyToolsPureCPP)

set(INCLUDE_FILES include/chainCollectionCPP.h
        )

set(SOURCE_FILES
        src/chainCollectionCPP.cpp
        src/queryAbnum.cpp
        include/chainCollectionCPP.h)

set(TARGET_NAME AbPyToolsCPPLib)

message("ABPYTOOLS_CPP_DIRS: ${ABPYTOOLS_CPP_DIRS}")

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME}
        ${AbPyToolsInterfaceLib}
        ${PYTHON_LIBRARY}
        )

target_include_directories(${TARGET_NAME}
        INTERFACE include/
        )

target_include_directories(${TARGET_NAME} SYSTEM
        PUBLIC ${PYTHON_INCLUDE_DIRS}
        ${ABPYTOOLS_CPP_DIRS}
        ${PYTHON_NUMPY_INCLUDE_DIR}
        )