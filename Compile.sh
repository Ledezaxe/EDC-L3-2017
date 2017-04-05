#!/bin/bash

if [ ! -d "./build" ]; then
mkdir build
fi
if [ ! -d "./dist" ]; then
mkdir dist
fi
cd ./build/
cmake ../source -DCMAKE_INSTALL_PREFIX="../dist" -DCMAKE_BUILD_TYPE=Debug
make
make install