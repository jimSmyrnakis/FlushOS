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

#this will be used for our os emulation 
sudo mkdir /mnt/d

./buildCompiler.sh
