[![Build Status](https://travis-ci.org/gf712/AbPyTools-Qt.svg?branch=master)](https://travis-ci.org/gf712/AbPyTools-Qt)

AbPyTools-Qt
============

This is a new version of [AbPyTools](https://github.com/gf712/AbPyTools) which has a frontend that can be easily used in addition to the existing
Python3 API.

Project Mission & Summary
=========================
- Provide an easy to use interface to work with heavy and light antibody chains
- Further optimise AbPyTools python code using C/C++ backend
- Integrate machine learning algorithms for data analysis

Build from source
=================
AbPyTools-Qt can (in relative terms..) be easily built with cmake, which creates all required files for make.
First create a build directory:
```
cd /path/to/AbPyTools-Qt
mkdir build
cd build
```

AbPyTools-Qt requires Python >= 3.5. If you have several python versions in your system, it should automatically find the required version.
If this fails, or for some reason you want to use a specific version (>=3.5) you can set the path with cmake:
```
cmake -DPYTHON_INCLUDE_DIR=/path/to/python/include -DPYTHON_LIBRARY=/path/to/python/libs ..
```
For those building with anaconda this could look like:
```
cmake -DPYTHON_INCLUDE_DIR=$HOME/anaconda3/include/python3.6m -DPYTHON_LIBRARY=$HOME/anaconda3/lib/libpython3.6m.so ..
```

Note that you need to use the same environment you used to install [AbPyTools](https://github.com/gf712/AbPyTools)!

And now build (and test) the source code:

```
make
make test
```

Known issues
============
- Compiling boost with a python distribution from anaconda can lead to pathing issues. This issue will come up when 
hunter is preparing the build files, and boost will fail to find the pyconfig.h. To solve this create a symlink
in the include directory, like this:
```
cd /your/anaconda/path/
cd include/
ln -s python3.6m python3.6
```

Changelog
=========

v0.1 (TBC):
- Simple GUI to call some basic functions found in AbPyTools
- Sort out installation of all depencies, AbPyTools, Boost and Qt
    - cmake
    - make
    - qmake
- Tests:
    - Continuous integration 
    - Code coverage