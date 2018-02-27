project(AbPyToolsGUI)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# add ui/ directory to search path
set(CMAKE_AUTOUIC_SEARCH_PATHS ui/)

set(SOURCE_FILES
        src/mainwindow.cpp
        src/newsequencedialog.cpp)

set(HEADER_FILES
        include/mainwindow.h
        include/newsequencedialog.h)

set(UI_FILES
        ui/mainwindow.ui
        ui/newsequencedialog.ui)

add_library(AbPyToolsGUIlib STATIC
        ${SOURCE_FILES}
        ${HEADER_FILES}
        ${UI_FILES})

target_include_directories(AbPyToolsGUIlib PUBLIC
        include/
        $<TARGET_PROPERTY:Qt5::Core,INTERFACE_INCLUDE_DIRECTORIES>
        $<TARGET_PROPERTY:Qt5::Widgets,INTERFACE_INCLUDE_DIRECTORIES>
        )

target_link_libraries(AbPyToolsGUIlib
        AbPyToolsInterfaceLib
        AbPyToolsCPPLib
        Qt5::Widgets
        Qt5::Core)

add_executable(AbPyToolsQt
        src/main.cpp)

target_link_libraries(AbPyToolsQt
        AbPyToolsGUIlib
)
