#!/bin/bash

#gcc + linker(gnu compilers collection) for mainly building the cross platform gcc c compiler for the os
sudo apt install gcc
sudo apt install ld

#for creating the cross compiler essential libraries
sudo apt install foo
sudo apt install build-essential
sudo apt install bison
sudo apt install flex 
sudo apt install libgmp3-dev
sudo apt install libmpc-dev
sudo apt install libmpfr-dev
sudo apt install texinfo
sudo apt install libisl-dev

#build unitilites
EXPORT PREFIX="$HOME/Tools/opt/cross"
EXPORT TARGET=i686-elf
EXPORT PATH="$PREFIX/bin:$PATH"
cd ../Tools/src
mkdir build-binutils
cd build-binutils
../binutils-2.35/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make 
make install
cd ../../../scripts

#

