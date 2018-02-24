project(AbPyToolsCppParsers)

set(SOURCE_FILES
        src/hydrophobicityParser.cpp tests/AbPyToolsCppParserTests.cpp)

set(ABPYTOOLS_CPP_PARSER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

add_library(AbPyToolsCppParserLib STATIC
            ${SOURCE_FILES})

target_include_directories(AbPyToolsCppParserLib
        PUBLIC include/)
#        ${BOOST_INCLUDE_DIR})

target_link_libraries(AbPyToolsCppParserLib
        Boost::filesystem
        Boost::system)

file(COPY data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)
file(COPY data/abraham.hpb DESTINATION ${CMAKE_BINARY_DIR}/backend/abpytools/data)

add_subdirectory(tests)

message(${AbPyToolsCppParserTests_BINARY_DIR})

add_test(NAME AbPyToolsParseCppTests COMMAND AbPyToolsCppParserTest
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})