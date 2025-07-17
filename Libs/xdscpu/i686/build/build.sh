#!/bin/bash

export PREFIX="$HOME/Tools/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
echo $PATH


make

