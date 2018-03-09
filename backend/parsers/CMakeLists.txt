project(AbPyToolsCppParsers)

set(SOURCE_FILES
        src/hydrophobicityParser.cpp
        src/FastaParser.cpp
        src/parser.cpp)

set(ABPYTOOLS_CPP_PARSER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "abpytools cpp parser include directory")

set(TARGET_NAME ABPYTOOLSCPP_PARSER_LIBRARIES)

add_library(${TARGET_NAME} STATIC
        ${SOURCE_FILES}
        )

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "abpytoolscpp-parsers")

target_include_directories(${TARGET_NAME}
        INTERFACE include/)

target_include_directories(${TARGET_NAME} SYSTEM
        PUBLIC ${BACKEND_UTILS_DIRS})

target_link_libraries(${TARGET_NAME}
        ABPYTOOLSCPP_EXCEPTIONS_LIBRARIES
        ${Boost_LIBRARIES}
        )

file(COPY data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)
file(COPY data/abraham.hpb DESTINATION ${CMAKE_BINARY_DIR}/backend/abpytools/data)
file(COPY data/abraham.hpb DESTINATION ${CMAKE_BINARY_DIR}/backend/abpytools-cpp/data)

add_subdirectory(tests)

add_test(NAME AbPyToolsParseCppTests COMMAND AbPyToolsCppParserTest
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})