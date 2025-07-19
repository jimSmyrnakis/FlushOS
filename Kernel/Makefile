cc = i686-elf-gcc
ld = i686-elf-ld
ccflags =-g -Wno-unused-variable -ffreestanding -std=gnu99 -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -Iinc -nostdlib -nostartfiles -nodefaultlibs -Wall -O0

object_files= ./Builds/kernel_init.asm.o ./Builds/kernel.o ./Builds/text_mode.o 

all: $(object_files)
	$(ld) -g -relocatable $(object_files) -o ./Builds/flush_kernel.o 
	
./Builds/kernel.o: ./Source/kernel.c
	$(cc) $(ccflags) -c ./Source/kernel.c -o ./Builds/kernel.o

./Builds/kernel_init.asm.o: ./Source/init/kernel_init.asm
	nasm -g -f elf ./Source/init/kernel_init.asm -o ./Builds/kernel_init.asm.o

./Builds/text_mode.o : ./Source/drivers/mono/desktop/text_mode/text_mode.c 
	$(cc) $(ccflags) -c ./Source/drivers/mono/desktop/text_mode/text_mode.c -o ./Builds/text_mode.o 

clean:
	rm -rf $(object_files) ./Builds/flush_kernel.o 