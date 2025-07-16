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

#build unitilites for i686 processor
EXPORT PREFIX="$HOME/Tools/opt/cross"
EXPORT TARGET=i686-elf
EXPORT PATH="$PREFIX/bin:$PATH"
cd ../Tools/src
mkdir build-binutils
cd build-binutils
../binutils-2.35/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make 
make install
../gdb-2.35/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make all-gdb
make install-gdb
cd ../../../scripts

#gcc cross platform for i686 processor
cd ../Tools/src
which -- $TARGET-as || echo $TARGET-as is not in the PATH
mkdir build-gcc
cd build-gcc
../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make all-gcc
make all-target-libgcc
make all-target-libstdc++-v3
make install-gcc
make install-target-libgcc
make install-target-libstdc++-v3


#testing ...
echo "Testing ..."
$HOME/opt/cross/bin/$TARGET-gcc --version




