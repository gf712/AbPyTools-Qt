project(AbPyToolsCppParsers)

set(SOURCE_FILES
        src/hydrophobicityParser.cpp
        src/FastaParser.cpp
        src/parser.cpp)

set(ABPYTOOLS_CPP_PARSER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "abpytools cpp parser include directory")

add_library(AbPyToolsCppParserLib STATIC
            ${SOURCE_FILES})

target_include_directories(AbPyToolsCppParserLib
        INTERFACE include/)

target_include_directories(AbPyToolsCppParserLib SYSTEM
        PUBLIC ${BACKEND_UTILS_DIRS})

target_link_libraries(AbPyToolsCppParserLib
        EXCEPTIONS_LIB
        Boost::filesystem
        Boost::system
        Boost::python3)

file(COPY data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)
file(COPY data/abraham.hpb DESTINATION ${CMAKE_BINARY_DIR}/backend/abpytools/data)
file(COPY data/abraham.hpb DESTINATION ${CMAKE_BINARY_DIR}/backend/abpytools-cpp/data)

add_subdirectory(tests)

add_test(NAME AbPyToolsParseCppTests COMMAND AbPyToolsCppParserTest
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})