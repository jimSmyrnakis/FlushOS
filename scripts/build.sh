#!/bin/bash

export PREFIX="$HOME/Tools/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

#compile and produce libraries
cd ../Libs/xdscpu/i686/build
./build.sh
cd ../../../../scripts


#compile the kernel
cd ../Kernel/
make all
cd ../scripts/
