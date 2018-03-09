project(AbPyToolsBackend)

# first generate the utils libs -> has all the basic stuff, i.e. exceptions
add_subdirectory(utils)
# then the parsers, which are needed by the actual AbPyTools libraries
add_subdirectory(parsers)
add_subdirectory(abpytools)
add_subdirectory(abpytools-cpp)
