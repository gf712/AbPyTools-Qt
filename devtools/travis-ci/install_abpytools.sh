#!/usr/bin/env bash

cd $HOME/gf712
# configure a headless display to test plot generation
export DISPLAY=:99.0
sh -e /etc/init.d/xvfb start
sleep 3 # give xvfb some time to start
git clone https://github.com/gf712/AbPyTools
cd AbPyTools
python setup.py install
python setup.py test
cd $HOME/gf712
