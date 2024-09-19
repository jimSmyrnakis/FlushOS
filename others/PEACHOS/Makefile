
BIN_OUTPUT=./bin
OBJ_OUTPUT=./obj
PEACHOS_IMAGE=./os/peachos.bin
SRC_FOLDER=./src
INC_PATH=./src
KERNEL_LINKER=./linker/kernel.ld
DEBUG_GCC_FLAGS=-g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc
OBJ_FILES= $(OBJ_OUTPUT)/kernel.asm.o  $(OBJ_OUTPUT)/idt.o $(OBJ_OUTPUT)/idt.asm.o $(OBJ_OUTPUT)/kernel.o $(OBJ_OUTPUT)/stream.o $(OBJ_OUTPUT)/term.o $(OBJ_OUTPUT)/io.asm.o $(OBJ_OUTPUT)/smallRegex.o $(OBJ_OUTPUT)/status.o $(OBJ_OUTPUT)/isr.asm.o $(OBJ_OUTPUT)/isr.o $(OBJ_OUTPUT)/heap.o $(OBJ_OUTPUT)/kheap.o $(OBJ_OUTPUT)/paging.o $(OBJ_OUTPUT)/paging.asm.o $(OBJ_OUTPUT)/string.o $(OBJ_OUTPUT)/pparser.o $(OBJ_OUTPUT)/disk.o $(OBJ_OUTPUT)/file.o $(OBJ_OUTPUT)/fat16.o
OS_LIST= kernel.bin boot.bin

#peach os image file (for disk only)
peachos_x86_32: $(OS_LIST)
	dd if=$(BIN_OUTPUT)/boot.bin     >  $(PEACHOS_IMAGE)
	dd if=$(BIN_OUTPUT)/kernel.bin   >> $(PEACHOS_IMAGE)
	dd if=/dev/zero bs=1048576 count=16 >> $(PEACHOS_IMAGE)
	sudo mount -t vfat $(PEACHOS_IMAGE) /mnt/d
	sudo cp ./hello.txt /mnt/d
	sudo umount /mnt/d

#kernel binary file
kernel.bin: kernelfull.o
	i686-elf-gcc $(DEBUG_GCC_FLAGS) -T $(KERNEL_LINKER) -o $(BIN_OUTPUT)/kernel.bin -ffreestanding -O0 -nostdlib $(OBJ_OUTPUT)/kernelfull.o 

KERNELFULL_LIST= kernel.asm.o idt.asm.o  idt.o kernel.o smallRegex.o term.o io.asm.o stream.o isr.asm.o isr.o heap.o kheap.o paging.o paging.asm.o string.o status.o pparser.o disk.o file.o fat16.o 
#kernel final object
kernelfull.o: $(KERNELFULL_LIST)
	i686-elf-ld -g -relocatable $(OBJ_FILES) -o $(OBJ_OUTPUT)/kernelfull.o

#kernel
kernel.asm.o: $(SRC_FOLDER)/kernel.asm
	nasm -f elf -g $(SRC_FOLDER)/kernel.asm -o $(OBJ_OUTPUT)/kernel.asm.o 
kernel.o: $(SRC_FOLDER)/kernel.c
	i686-elf-gcc -I$(INC_PATH)  $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/kernel.c -o $(OBJ_OUTPUT)/kernel.o 

#idt
idt.asm.o: $(SRC_FOLDER)/idt/idt.asm
	nasm -f elf -g $(SRC_FOLDER)/idt/idt.asm -o $(OBJ_OUTPUT)/idt.asm.o
idt.o: $(SRC_FOLDER)/idt/idt.c
	i686-elf-gcc -I$(INC_PATH)  $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/idt/idt.c -o $(OBJ_OUTPUT)/idt.o

#term
term.o: $(SRC_FOLDER)/term/term.c
	i686-elf-gcc -I$(INC_PATH)  $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/term/term.c -o $(OBJ_OUTPUT)/term.o

#io
io.asm.o: $(SRC_FOLDER)/io/io.asm 
	nasm -f elf -g $(SRC_FOLDER)/io/io.asm -o $(OBJ_OUTPUT)/io.asm.o 

#isr
isr.o: $(SRC_FOLDER)/isr/isr.c
	i686-elf-gcc -I$(INC_PATH)  $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/isr/isr.c -o $(OBJ_OUTPUT)/isr.o
isr.asm.o: $(SRC_FOLDER)/isr/isr.asm
	nasm -f elf -g $(SRC_FOLDER)/isr/isr.asm -o $(OBJ_OUTPUT)/isr.asm.o

#heap
heap.o: $(SRC_FOLDER)/heap/heap.c
	i686-elf-gcc -I$(INC_PATH)  $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/heap/heap.c -o $(OBJ_OUTPUT)/heap.o

#kheap
kheap.o: $(SRC_FOLDER)/kheap.c
	i686-elf-gcc -I$(INC_PATH)  $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/kheap.c -o $(OBJ_OUTPUT)/kheap.o

#paging
paging.o: $(SRC_FOLDER)/paging/paging.c
	i686-elf-gcc -I$(INC_PATH) $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/paging/paging.c -o $(OBJ_OUTPUT)/paging.o 
paging.asm.o: $(SRC_FOLDER)/paging/paging.asm
	nasm -f elf -g $(SRC_FOLDER)/paging/paging.asm -o $(OBJ_OUTPUT)/paging.asm.o 

#disk
disk.o: $(SRC_FOLDER)/disk/disk.c
	i686-elf-gcc -I$(INC_PATH) $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/disk/disk.c -o $(OBJ_OUTPUT)/disk.o 

#string
string.o: $(SRC_FOLDER)/simple/string.c
	i686-elf-gcc -I$(INC_PATH) $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/simple/string.c -o $(OBJ_OUTPUT)/string.o 

#smallRegex
smallRegex.o: $(SRC_FOLDER)/simple/smallRegex.c
	i686-elf-gcc -I$(INC_PATH) $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/simple/smallRegex.c -o $(OBJ_OUTPUT)/smallRegex.o 

#status
status.o: $(SRC_FOLDER)/status.c
	i686-elf-gcc -I$(INC_PATH) $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/status.c -o $(OBJ_OUTPUT)/status.o 

#pparser
pparser.o: $(SRC_FOLDER)/fs/pparser.c 
	i686-elf-gcc -I$(INC_PATH) $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/fs/pparser.c -o $(OBJ_OUTPUT)/pparser.o 

#fs
file.o: $(SRC_FOLDER)/fs/file.c
	i686-elf-gcc -I$(INC_PATH) $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/fs/file.c -o $(OBJ_OUTPUT)/file.o

#stream
stream.o: $(SRC_FOLDER)/disk/stream.c
	i686-elf-gcc -I$(INC_PATH) $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/disk/stream.c -o $(OBJ_OUTPUT)/stream.o 

#fat16
fat16.o: $(SRC_FOLDER)/fs/fat/fat16.c
	i686-elf-gcc -I$(INC_PATH) $(DEBUG_GCC_FLAGS) -std=gnu99 -c $(SRC_FOLDER)/fs/fat/fat16.c -o $(OBJ_OUTPUT)/fat16.o 








#disk bootLoader
boot.bin: $(SRC_FOLDER)/boot/boot.asm
	nasm -f bin $(SRC_FOLDER)/boot/boot.asm -o $(BIN_OUTPUT)/boot.bin