#!/bin/bash

export PREFIX="$HOME/Tools/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

#compile and produce libraries
cd ../Libs/xdscpu/i686/build
./build.sh
cd ../../../../Scripts

#create first level bootloader
cd ../Bootloaders
./build.sh
cd ../Scripts

#compile the kernel
cd ../Kernel/
./build.sh
cd ../Scripts/

#generate the os image
make all


