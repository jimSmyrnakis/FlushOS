
all: program.bin ./Message.txt 
	dd if=./Message.txt >> ./program.bin
	dd if=/dev/zero bs=512 count=1 >> ./program.bin
	ndisasm ./program.bin 
	bless ./program.bin
	LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libpthread.so.0 /usr/bin/qemu-system-x86_64 -hda ./program.bin

	LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libpthread.so.0 gdb
	 
	


program.bin: ./kernel_bootloader.asm
	nasm -f bin ./kernel_bootloader.asm -o ./program.bin # set the nasm to assemble in raw binnary format the outnd


	
