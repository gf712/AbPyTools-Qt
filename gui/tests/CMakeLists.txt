project(GUIAbPyToolsCPPTests)

add_executable(GUIAbPyToolsCPPTest
        AbPyToolsGUITestSuite.cpp
        )

target_link_libraries(BackendAbPyToolsCPPTest
        ABPYTOOLSINTERFACE_LIBRARIES
        Boost::unit_test_framework)
