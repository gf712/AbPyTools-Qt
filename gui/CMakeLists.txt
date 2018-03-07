project(AbPyToolsGUI)

# solves slots issue
# https://cmake.org/pipermail/cmake/2009-January/026705.html
ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# add ui/ directory to search path
set(CMAKE_AUTOUIC_SEARCH_PATHS ui/)

set(SOURCE_FILES
        src/mainwindow.cpp
        src/newsequencedialog.cpp
        src/chainGroups.cpp
        src/newgroupdialog.cpp
        src/fileloaderdialog.cpp
        src/hydrophobicityGroup.cpp
        src/editdialog.cpp
        src/qcustomplot.cpp
        )

set(HEADER_FILES
        include/mainwindow.h
        include/newsequencedialog.h
        include/chainGroups.h
        include/newgroupdialog.h
        include/fileloaderdialog.h
        include/hydrophobicityGroup.h
        include/editdialog.h
        include/qcustomplot.h
        )

set(UI_FILES
        ui/mainwindow.ui
        ui/newsequencedialog.ui
        ui/newgroupdialog.ui
        ui/fileloaderdialog.ui
        ui/editdialog.ui
        )

add_library(AbPyToolsGUIlib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        ${UI_FILES})

target_include_directories(AbPyToolsGUIlib PUBLIC
        include/
#        $<TARGET_PROPERTY:Qt5::Core,INTERFACE_INCLUDE_DIRECTORIES>
#        $<TARGET_PROPERTY:Qt5::Widgets,INTERFACE_INCLUDE_DIRECTORIES>
#        ${QCUSTOMPLOT_INCLUDE}
        )


target_link_libraries(AbPyToolsGUIlib
        AbPyToolsInterfaceLib
        AbPyToolsCPPLib
#        QCUSTOMPLOT_LIB
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        Qt5::PrintSupport
        Qt5::Concurrent
        )


add_executable(AbPyToolsQt
        src/main.cpp)

target_link_libraries(AbPyToolsQt
        AbPyToolsGUIlib
)
