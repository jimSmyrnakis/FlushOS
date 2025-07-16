
all: boot.bin
	ndisasm ./boot.bin 
	bless ./boot.bin
	LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libpthread.so.0 /usr/bin/qemu-system-x86_64 -hda ./boot.bin

	LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libpthread.so.0 gdb
	 
	


boot.bin: ./boot.asm
	nasm -f bin ./boot.asm -o ./boot.bin # set the nasm to assemble in raw binnary format the outnd

clean: ./boot.bin 
	rm -rf ./boot.bin 


	
