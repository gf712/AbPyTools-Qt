project(AbPyToolsGUI)

# solves slots issue
# https://cmake.org/pipermail/cmake/2009-January/026705.html
ADD_DEFINITIONS(-DQT_NO_KEYWORDS)


# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

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

set(RESOURCE_FILES
        sprites.qrc)

set(TARGET_NAME ABPYTOOLS_GUI_LIBRARIES)

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
        ${RESOURCE_FILES}
        )

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "abpytools-gui")

target_include_directories(${TARGET_NAME} SYSTEM PUBLIC
        include/
        )

target_link_libraries(${TARGET_NAME}
        ABPYTOOLSINTERFACE_LIBRARIES
        ABPYTOOLSCPP_LIBRARIES
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        Qt5::PrintSupport
        Qt5::Concurrent
        )

add_subdirectory(tests)

add_test(NAME AbPyToolsGUITestSuite COMMAND AbPyToolsGUITestSuite
         WORKING_DIRECTORY ${AbPyToolsCPPGUITests_BIN_DIR})

###################################################################
#                           BUILD APP
###################################################################

add_executable(AbPyToolsQt
        src/main.cpp)

target_link_libraries(AbPyToolsQt
        ${TARGET_NAME}
)
