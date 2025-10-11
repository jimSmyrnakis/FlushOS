#!/bin/bash

#assember
sudo apt install nasm
#virtual system
sudo apt install qemu-system-x86
#bless 
sudo apt install bless
#gdb for debbuging 
sudo apt install gdb
#gcc + linker(gnu compilers collection) for mainly building the cross platform gcc c compiler for the os
sudo apt install gcc
sudo apt install ld

./buildCompiler.sh
