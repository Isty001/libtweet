#!/usr/bin/env bash

sudo rm -f /etc/apt/sources.list.d/google-chrome.list
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update || true
sudo apt-get install gcc-5
sudo apt-get install curl
sudo apt-get install liboauth-dev
sudo apt-get install libcmocka0
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 20
sudo make test-unit
