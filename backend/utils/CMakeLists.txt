project(BackendUtils)

set(BACKEND_UTILS_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(TARGET_NAME ABPYTOOLSCPP_EXCEPTIONS_LIBRARIES)

add_library(${TARGET_NAME} STATIC
        src/abpytools_exceptions.cpp)

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "abpytoolscpp-exceptions")

target_include_directories(${TARGET_NAME} PUBLIC
        include/
        ${PYTHON_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${TARGET_NAME}
        PUBLIC ${PYTHON_LIBRARIES})
