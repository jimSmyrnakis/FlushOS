

all: ./Image/bootloader.bin 
	
	 
	
./Image/bootloader.bin: ./Builds/boot.bin
	rm -rf ./Image/bootloader.bin
	dd if=./Builds/boot.bin  >> ./Image/bootloader.bin

./Builds/boot.bin: ./Source/PC/boot.asm
	nasm -f bin ./Source/PC/boot.asm -o ./Builds/boot.bin # set the nasm to assemble in raw binnary format the outnd

clean: 
	rm -rf ./Builds/boot.bin ./Image/bootloader.bin  


	
