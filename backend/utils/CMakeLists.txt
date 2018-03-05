project(BackendUtils)

set(BACKEND_UTILS_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
set(TARGET_NAME EXCEPTIONS_LIB)

add_library(${TARGET_NAME} STATIC
        src/exception.cpp)

target_include_directories(${TARGET_NAME}
        PUBLIC include/
        PUBLIC ${PYTHON_INCLUDE_DIRS}
        PUBLIC ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${TARGET_NAME}
        PUBLIC ${PYTHON_LIBRARY})
