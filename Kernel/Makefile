cc = i686-elf-gcc
ld = i686-elf-ld
ccflags =-g -Wno-unused-variable -ffreestanding -std=gnu99 -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -Iinc -nostdlib -nostartfiles -nodefaultlibs -Wall -O0

object_files=./Builds/kernel_init.asm.o ./Builds/io.o ./Builds/interrupts.o ./Builds/memory.c.o ./Builds/idt.asm.o ./Builds/idt.c.o  ./Builds/kernel.o ./Builds/text_mode.o  

all: $(object_files)
	$(ld) -g -relocatable $(object_files) -o ./Builds/flush_kernel.o 
	
./Builds/kernel.o: ./Source/kernel.c
	$(cc) $(ccflags) -c ./Source/kernel.c -o ./Builds/kernel.o

./Builds/kernel_init.asm.o: ./Source/init/kernel_init.asm
	nasm -g -f elf ./Source/init/kernel_init.asm -o ./Builds/kernel_init.asm.o

./Builds/text_mode.o : ./Source/drivers/mono/desktop/text_mode/text_mode.c 
	$(cc) $(ccflags) -c ./Source/drivers/mono/desktop/text_mode/text_mode.c -o ./Builds/text_mode.o 

./Builds/idt.c.o: ./Source/Interrupts/idt.c
	$(cc) $(ccflags) -c ./Source/Interrupts/idt.c -o ./Builds/idt.c.o

./Builds/idt.asm.o: ./Source/Interrupts/idt.asm 
	nasm -g -f elf ./Source/Interrupts/idt.asm  -o ./Builds/idt.asm.o

./Builds/memory.c.o: ./Source/std/memory.c
	$(cc) $(ccflags) -c ./Source/std/memory.c -o ./Builds/memory.c.o

./Builds/interrupts.o: ./Source/Interrupts/interrupts.c
	$(cc) $(ccflags) -c ./Source/Interrupts/interrupts.c -o ./Builds/interrupts.o

./Builds/io.o: ./Source/io/io.asm 
	nasm -g -f elf ./Source/io/io.asm   -o ./Builds/io.o

clean:
	rm -rf $(object_files) ./Builds/flush_kernel.o 