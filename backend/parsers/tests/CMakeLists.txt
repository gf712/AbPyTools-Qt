cmake_minimum_required(VERSION 3.1)

project(AbPyToolsCppParserTests)

add_executable(AbPyToolsCppParserTest
        AbPyToolsCppParserTests.cpp)

target_compile_definitions(AbPyToolsCppParserTest PRIVATE
        TEST_PATH=${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(AbPyToolsCppParserTest PRIVATE
        ${Boost_INCLUDE_DIRS})

target_link_libraries(AbPyToolsCppParserTest
        ABPYTOOLSCPP_PARSER_LIBRARIES
        ${Boost_LIBRARIES}
        )
