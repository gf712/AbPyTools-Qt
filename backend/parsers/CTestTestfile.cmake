# CMake generated Testfile for 
# Source directory: /home/gil/AbPyTools-Qt/backend/parsers
# Build directory: /home/gil/AbPyTools-Qt/backend/parsers
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(AbPyToolsParseCppTests "/home/gil/AbPyTools-Qt/backend/parsers/tests/AbPyToolsCppParserTest")
set_tests_properties(AbPyToolsParseCppTests PROPERTIES  WORKING_DIRECTORY "/home/gil/AbPyTools-Qt/backend/parsers")
subdirs("tests")
