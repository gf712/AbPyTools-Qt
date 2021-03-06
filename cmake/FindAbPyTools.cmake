#.rst:
# FindAbpytools
# -------------
#
# Find AbPyTools
#
# Find the AbPyTools python library
#
# This module sets the following variables::
#
#   ABPYTOOOLS_FOUND - set to true if the library is found
#   ABPYTOOOLS_INCLUDE_DIRS - python include directory where abpytools was found
#   ABPYTOOOLS_LIBRARIES - python libraries where abpytools was found
#   ABPYTOOOLS_VERSION_MAJOR - major version number
#   ABPYTOOOLS_VERSION_MINOR - minor version number
#   ABPYTOOOLS_VERSION_PATCH - patch version number
#   ABPYTOOOLS_VERSION_STRING - version number as a string (ex: "0.2.3")

if (PYTHON_EXECUTABLE)
    file(WRITE ${CMAKE_BINARY_DIR}/python_script.py
            "
try:
  import abpytools
  print(abpytools.__version__, end='')
except:
  pass
")
    execute_process(
            COMMAND ${PYTHON_EXECUTABLE} python_script.py
            OUTPUT_VARIABLE ABPYTOOLS_VERSION_STRING)
    file(REMOVE ${CMAKE_BINARY_DIR}/python_script.py)
else()
    message(FATAL_ERROR "Python executable not found.")
endif(PYTHON_EXECUTABLE)


# check if abpytools version could be obtained
string(COMPARE EQUAL "${ABPYTOOLS_VERSION_STRING}" "" _cmp)

if (NOT _cmp)
    set(ABPYTOOLS_LIBRARIES ${PYTHON_LIBRARIES})
    set(ABPYTOOLS_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS})
    string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\1" ABPYTOOLS_VERSION_MAJOR ${ABPYTOOLS_VERSION_STRING})
    string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\2" ABPYTOOLS_VERSION_MINOR ${ABPYTOOLS_VERSION_STRING})
    string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\3" ABPYTOOLS_VERSION_PATCH ${ABPYTOOLS_VERSION_STRING})
else()
    message(FATAL_ERROR "Could not find AbPyTools in the given python environment!")
endif ()

if (${AbPyTools_FIND_VERSION} VERSION_GREATER ${ABPYTOOLS_VERSION_STRING})
    message(STATUS "Could not find required version! Consider installing the newest abpytools version:")
    message(STATUS "  pip install abpytools")
#message("VERSION TO FIND: ${AbPyTools_FIND_VERSION}")
endif()

find_package_handle_standard_args(AbPyTools
        REQUIRED_VARS ABPYTOOLS_INCLUDE_DIRS ABPYTOOLS_LIBRARIES
        VERSION_VAR ABPYTOOLS_VERSION_STRING
        )

mark_as_advanced(
        ABPYTOOLS_INCLUDE_DIRS
        ABPYTOOLS_LIBRARIES
        ABPYTOOLS_VERSION_STRING
        ABPYTOOLS_VERSION_MAJOR
        ABPYTOOLS_VERSION_MINOR
        ABPYTOOLS_VERSION_PATCH
)