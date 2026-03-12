cc = i686-elf-gcc
ld = i686-elf-ld
ccflags =-g -ffreestanding -std=gnu99 -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -Wno-unused-parameter -Iinc -nostdlib -nostartfiles -nodefaultlibs -Wall -O0

libraries= ../Libs/xdscpu/i686/library/x86_32_proc.o
object_files=  ../Kernel/Builds/flush_kernel.o  $(libraries)

all: ../Image/flushos.bin
	
	LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libpthread.so.0 /usr/bin/qemu-system-x86_64 -hda ../Image/flushos.bin
	LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libpthread.so.0 gdb

notYet:
	bless ../Image/flushos.bin
	ndisasm ../Image/flushos.bin
	
../Image/flushos.bin: ../Builds/os.bin ../Bootloaders/Image/bootloader.bin
	rm -rf ../Image/flushos.bin
	dd if=../Bootloaders/Image/bootloader.bin  >> ../Image/flushos.bin
	dd if=../Builds/os.bin >> ../Image/flushos.bin
	dd if=/dev/zero bs=1048576 count=1024 >> ../Image/flushos.bin
	sudo mount -t vfat ../Image/flushos.bin /mnt/d
	sudo cp  ./Hello.txt /mnt/d
	sudo ls /mnt/d
	sudo umount /mnt/d
	


../Builds/os.bin: ../Builds/os.o
	$(cc) $(ccflags) -T ../Scripts/common_linker_script.ld -o ../Builds/os.bin ../Builds/os.o 
	$(ld) -T ../Scripts/common_linker_script.ld -o ../Builds/os.bin ../Builds/os.o


../Builds/os.o: $(object_files)
	$(ld) -g -relocatable $(object_files) -o ../Builds/os.o

clean: 
	rm -rf ../Image/flushos.bin ../Builds/os.o ../Builds/os.bin