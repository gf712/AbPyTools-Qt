project(qcustomplot)

set(QCUSTOMPLOT_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(TARGET_NAME QCUSTOMPLOT_LIB)

add_library(${TARGET_NAME} STATIC
        src/qcustomplot.cpp)

target_include_directories(${TARGET_NAME} SYSTEM PUBLIC
        include/)

target_include_directories(${TARGET_NAME} PUBLIC
        $<TARGET_PROPERTY:Qt5::PrintSupport,INTERFACE_INCLUDE_DIRECTORIES>
        )

target_link_libraries(${TARGET_NAME}
        Qt5::PrintSupport
        )
