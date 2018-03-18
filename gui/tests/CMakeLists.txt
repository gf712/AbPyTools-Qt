project(AbPyToolsCPPGUITests)

add_executable(AbPyToolsGUITestSuite
        AbPyToolsGUITestSuite.cpp
        )

target_link_libraries(AbPyToolsGUITestSuite
        ABPYTOOLS_GUI_LIBRARIES
        Boost::unit_test_framework)
