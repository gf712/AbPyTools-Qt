[![Build Status](https://travis-ci.org/gf712/AbPyTools-Qt.svg?branch=master)](https://travis-ci.org/gf712/AbPyTools-Qt)

AbPyTools-Qt
============

This is a new version of [AbPyTools](https://github.com/gf712/AbPyTools) which has a frontend that can be easily used in addition to the existing Python3 API. Checkout the [wiki](https://github.com/gf712/AbPyTools-Qt/wiki) for more information.

Project Mission & Summary
=========================
- Provide an easy to use GUI to work with heavy and light antibody chains
- Further optimise AbPyTools python code using C/C++ backend
- Integrate machine learning algorithms for data analysis

How does it work?
=================
- AbPyTools-Qt aims to provide an interface that allows any user to easily manipulate antibody sequences. By splitting work into groups it is possible to analyse several sets of antibody chains (and in future whole Fabs) with ease.
- The background integrates the existing python code from [AbPyTools](https://github.com/gf712/AbPyTools) and uses C++ libraries such as [armadillo](http://arma.sourceforge.net/) and [mlpack](https://www.mlpack.org/) to optimise and scale up matrix manipulation tasks (necessary for machine learning).

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

Building from source is something for the patient. If you never used hunter before, particularly with a project that 
requires Qt, downloading and building all the libraries can take a long time (and cause loss of hair..)!

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

- There can be issues with the font used by Qt, but these should be resolved during build time by the cmake script.
The script will automatically add the path to the Qt font directory provided by the Qt hunter installation. If you wish
to change disable this behaviour run cmake like this:

`cmake -DADD_QT_QPA_FONTDIR=OFF ..`

Changelog
=========
### v0.3 (TBA):
- integrate structural analysis
- release binaries (linux)

### v0.2 (TBA):
- further integration with abpytools
- improved UI
- memory management
- clustering

### v0.1 (08/03/2018):
- hydrophobicity matrix PCA and PC plotting
- Simple GUI to call some basic functions found in AbPyTools
- Easy(ish) installation with:
    - cmake
    - make
- Tests:
    - Continuous integration 
    - Code coverage