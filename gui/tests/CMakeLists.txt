project(GUIAbPyToolsCPPTests)

add_executable(GUIAbPyToolsCPPTest
        AbPyToolsGUITestSuite.cpp
        )

target_link_libraries(BackendAbPyToolsCPPTest
        AbPyToolsInterfaceLib
        Boost::unit_test_framework)
