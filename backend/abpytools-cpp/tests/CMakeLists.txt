project(AbPyToolsCPPTests)

add_executable(AbPyToolsCPPTest
        AbPyToolsCPPTestSuite.cpp
        )

target_include_directories(AbPyToolsCPPTest PRIVATE
        ${Boost_INCLUDE_DIRS}
        )

target_link_libraries(AbPyToolsCPPTest
        ABPYTOOLSCPP_LIBRARIES
        ${Boost_LIBRARIES}
        )
