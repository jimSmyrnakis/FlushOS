#!/bin/bash

EXPORT PREFIX="$HOME/Tools/opt/cross"
EXPORT TARGET=i686-elf
EXPORT PATH="$PREFIX/bin:$PATH"

cd ../Kernel/
make all
cd ../scripts/
