
source_path  =./../source
object_path  =./../object
library_path =./../library
include_path =./../include

source_files  = $(source_path)/memory/memory.c  $(source_path)/string/string.c
include_files = $(include_path)/memory/memory.h $(include_path)/string/string.h

//=================== for i686-elf-gcc cross platform compiler =================== 
cc = i686-elf-gcc
ld = i686-elf-ld
cc_rflags =-ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0
cc_dflags =-g $(cc_rflags)

debug_i686_elf_gcc: $(source_files) $(include_files)
	$(cc) $(cc_dflags) 
