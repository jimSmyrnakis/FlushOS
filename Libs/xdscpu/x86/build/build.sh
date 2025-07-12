#!/bin/bash

#export PREFIX="$HOME/opt/cross"
#export TARGET=i686-elf
#export PATH="$PREFIX/bin:$PATH"

#cd ../../../../Tools/
#./preparation.sh
#cd ../Libs/xdscpu/x86/build/
export PREFIX="$PWD/../../../../Tools/src"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
echo $PATH


make

