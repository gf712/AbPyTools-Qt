#!/usr/bin/env bash

cd $HOME/gf712

# download and install miniconda
wget https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh -O miniconda.sh;
bash miniconda.sh -b -p $HOME/miniconda
export PATH="$HOME/miniconda/bin:$PATH"
# if we don't create this symlink there is a weird bug in boost because it looks for this specific directory
hash -r
conda config --set always_yes yes --set changeps1 no
conda update -q conda
# Useful for debugging any issues with conda
conda info -a
conda create -q -n test-environment python=$TRAVIS_PYTHON_VERSION scipy numpy pip matplotlib pandas

cd $HOME/gf712