cc = i686-elf-gcc
ld = i686-elf-ld
ccflags =-g -Wno-unused-variable -ffreestanding -std=gnu99 -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -Iinc -nostdlib -nostartfiles -nodefaultlibs -Wall -O0

object_files=./Builds/kernel_init.asm.o ./Builds/fat16.o ./Builds/file.o ./Builds/disk_stream.o ./Builds/path_parser.o ./Builds/string.o ./Builds/disk.o ./Builds/pata.o ./Builds/virtmem.o ./Builds/paging.asm.o ./Builds/paging.o ./Builds/pte.o ./Builds/pde.o ./Builds/kheap.o ./Builds/heap.o ./Builds/pic.o ./Builds/io.o ./Builds/interrupts.o ./Builds/memory.c.o ./Builds/idt.asm.o ./Builds/idt.c.o  ./Builds/kernel.o ./Builds/text_mode.o  

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

./Builds/pic.o: ./Source/drivers/mono/desktop/pic/pic.c 
	$(cc) $(ccflags) -c ./Source/drivers/mono/desktop/pic/pic.c  -o ./Builds/pic.o

./Builds/heap.o: ./Source/heap/heap.c 
	$(cc) $(ccflags) -c ./Source/heap/heap.c   -o ./Builds/heap.o

./Builds/kheap.o: ./Source/heap/kheap.c 
	$(cc) $(ccflags) -c ./Source/heap/kheap.c   -o ./Builds/kheap.o

./Builds/pde.o: ./Source/paging/pde.c 
	$(cc) $(ccflags) -c ./Source/paging/pde.c    -o ./Builds/pde.o

./Builds/pte.o: ./Source/paging/pte.c 
	$(cc) $(ccflags) -c ./Source/paging/pte.c    -o ./Builds/pte.o

./Builds/paging.o: ./Source/paging/paging.c 
	$(cc) $(ccflags) -c ./Source/paging/paging.c    -o ./Builds/paging.o

./Builds/paging.asm.o: ./Source/paging/paging.asm
	nasm -g -f elf ./Source/paging/paging.asm   -o ./Builds/paging.asm.o

./Builds/virtmem.o: ./Source/virtmem/virtmem.c 
	$(cc) $(ccflags) -c ./Source/virtmem/virtmem.c    -o ./Builds/virtmem.o

./Builds/pata.o: ./Source/drivers/mono/desktop/pata/pata.c 
	$(cc) $(ccflags) -c ./Source/drivers/mono/desktop/pata/pata.c  -o ./Builds/pata.o

./Builds/disk.o: ./Source/disk/disk.c 
	$(cc) $(ccflags) -c ./Source/disk/disk.c   -o ./Builds/disk.o

./Builds/disk_stream.o: ./Source/disk/disk_stream.c 
	$(cc) $(ccflags) -c ./Source/disk/disk_stream.c   -o ./Builds/disk_stream.o

./Builds/string.o: ./Source/std/string.c 
	$(cc) $(ccflags) -c ./Source/std/string.c   -o ./Builds/string.o

./Builds/path_parser.o: ./Source/file_system/path_parser.c 
	$(cc) $(ccflags) -c ./Source/file_system/path_parser.c   -o ./Builds/path_parser.o

./Builds/file.o: ./Source/file_system/file.c 
	$(cc) $(ccflags) -c ./Source/file_system/file.c   -o ./Builds/file.o

./Builds/fat16.o: ./Source/drivers/mono/file_systems/FAT16/fat16.c 
	$(cc) $(ccflags) -c ./Source/drivers/mono/file_systems/FAT16/fat16.c  -o ./Builds/fat16.o

clean:
	rm -rf $(object_files) ./Builds/flush_kernel.o 