#!/usr/bin/env bash

cd $HOME

sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo add-apt-repository ppa:titas-chanda/armadillo -y
sudo apt-get update -y
sudo apt-get install gcc-5 g++-5 libmlpack-dev -y
# increase priority of gcc5 and g++5
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 150 --slave /usr/bin/g++ g++ /usr/bin/g++-5

if [[ $HUNTER_ENABLED == 0 ]]
then
    # install Qt and boost manually
    wget -O boost_1_66_0.tar.gz https://sourceforge.net/projects/boost/files/boost/1.66.0/boost_1_66_0.tar.gz/download
    tar -xzf boost_1_66_0.tar.gz
    cd boost_1_66_0/
    sudo apt-get install autotools-dev libicu-dev build-essential libbz2-dev libboost-all-dev -y
    ./bootstrap.sh --with-python-version=3.6 --with-libraries=test,python,filesystem,system
    ./b2 -j4
    sudo ./b2 install
    # qt
    sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa -y
    sudo apt-get update -y
    sudo apt-get install qtbase5-dev qtdeclarative5-dev libqt5webkit5-dev libsqlite3-dev -y
    sudo apt-get install qt5-default qttools5-dev-tools -y
fi

cd $HOME