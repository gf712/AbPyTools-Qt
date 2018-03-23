project(AbPyToolsBackend)

# first generate the utils libs -> has all the basic stuff, i.e. exceptions
add_subdirectory(utils)
# then the parsers, which are needed by the actual AbPyTools libraries
add_subdirectory(parsers)
# machine learning algorithms
add_subdirectory(machine-learning)
# python wrapper
add_subdirectory(abpytools)
# cpp implementations to hold chain information
add_subdirectory(abpytools-cpp)
