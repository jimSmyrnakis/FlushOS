cc = i686-elf-gcc
ld = i686-elf-ld
ccflags =-g -ffreestanding -std=gnu99 -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -Iinc -nostdlib -nostartfiles -nodefaultlibs -Wall -O0

object_files= ./Builds/kernel_init.asm.o ./Builds/kernel.o 

all: $(object_files)
	$(ld) -g -relocatable $(object_files) -o ./Builds/flush_kernel.o 
	
./Builds/kernel.o: ./Source/kernel.c
	$(cc) $(flags) -c ./Source/kernel.c -o ./Builds/kernel.o

./Builds/kernel_init.asm.o: ./Source/init/kernel_init.asm
	nasm -g -f elf ./Source/init/kernel_init.asm -o ./Builds/kernel_init.asm.o

clean:
	rm -rf $(object_files) ./Builds/flush_kernel.o 