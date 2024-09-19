ORG 0x7c00
BITS 16 

gdtCodeIndex equ KernelCodeSegment - GDT_Begin
gdtDataIndex equ KernelDataSegment - GDT_Begin
KarnelAddr   equ 0x00100000

;=====================FAT 16 Header=====================
jmp short _initBootLoaderCodeSegment_
nop
;filename we now is atleast 8 utf8 characters wide (space is the end of the flname)
OEM_Identrifier     db 'Peachos ' 
;how many bytes each sector of the disk is , don't take it seriously (that depends on the storage device)
SectorCount         dw 512
;how many sectors per cluster (this is what the size of)
SectorPerCluster    db 0x80
;how many sectors up we will not use (this is where the kernel absolute bin code is)
ReservedSectors     dw 200 
;we gone have two copies of the fat16 header , so we can have a backup system
FatCopies           db 2
;how many entries or (files and folder compination) can have in the root directory?
RootDirEntriesNum   dw 64
;we dont care and use this field as a begginers
NumSectors          dw 0
;what type of storage device (physical or logical) we use
MediaDescriptorType db 0xF8
;what the size of the fat16 header structure is (always round it to sector size)
FAT16_HEADER_COUNT  dw 512 ;mean's one sector
;that has to do with the storage device ?
SectorsPerTrack     dw 0x20
;that sure has to do with the storage device
NumberOfHeads       dw 0x40
;the partition start sector , we dont do something like it so 0
PartitionBegin      dd 0
; i dont have idea what that is
SectorBig           dd 0x773594
;=====================FAT 16 Header=====================
;=====================Extended Boot Record=====================
DriverNumber        db 0x80
WinNTBit            db 0
Signature           db 0x29
VolumeID            dd 0x0000D105
VolumeIDString      db 'PEACHOS BOO'
SystemIDString      db 'FAT16   '
;=====================Extended Boot Record=====================

_initBootLoaderCodeSegment_:
    jmp 0x0000:_initBootLoaderDataSegments_



_initBootLoaderDataSegments_:
    cli ; clear IF Flag so no external interrupts stop the execution
    mov ax , 0x0000
    mov ds , ax
    mov es , ax
    mov ss , ax
    mov sp , 0x7c00
    
_BootLoader16_: 

    

    ; set Protected Enable bit and load kernel segments (data and code)
    cli
    lgdt [GlobalDescriptorTablePointer]
    
    mov eax , cr0 
    or  eax , 1  
    mov cr0 , eax 

    jmp gdtCodeIndex:Load32;





DeviceID: dw 0  

GlobalDescriptorTable:
GDT_Begin:
    nullDescriptor: ; selector index 0x00
        dw 0x0000
        dw 0x0000
        dw 0x0000
        dw 0x0000
    KernelCodeSegment:;code segment for all 4GB RAM , selector index 0x08
        dw 0xFFFF       ; segment limit 00...15 = ffff
        dw 0x0000       ; segment base  00...15 = 0
        db 0x00         ; segment base  16...23 = 0 
        db 0b10011010   ; P=1,DPL=0,11,C=0,R=1,A=0
        db 0b11001111   ; G=1,D=1,0,AVL=0,segment limit 16...19 = f
        db 0x00         ; segment base  24...32 = 0
    KernelDataSegment:;data segment for all 4GB RAM  , selector index 0x10
        dw 0xFFFF
        dw 0x0000
        db 0x00
        db 0b10010010
        db 0b11001111
        db 0x00
GDT_End:

GlobalDescriptorTablePointer:
    dw GDT_End - GDT_Begin - 1
    dd GlobalDescriptorTable


[BITS 32]
Load32:
    mov eax , 1     ;base sector
    mov ecx , 100   ;number of sectors to load
    mov edi , KarnelAddr ;buffer on memory to load them
    call SIMPLE_LBA_ATA_DISK_LOADER; eax zero if something rong happen
    
    
    jmp gdtCodeIndex:KarnelAddr

SIMPLE_LBA_ATA_DISK_LOADER:
    mov ebx , eax

    ;send 8high bits of sectors base to chip register 0x01F6 address component
    shr eax , 24
    or  eax , 0xE0 ; for selecting the master drive
    mov dx , 0x01F6
    out dx , al

    ;send sectors to read
    mov eax , ecx
    mov dx  , 0x01F2
    out dx  , al

    ;send 8low bits of sectors base to chip register 0x01F3
    mov eax , ebx 
    mov dx  , 0x01F3
    out dx  , al
    
    ;send 8bit on byte1 of sectors base to chip register 0x01F4
    mov eax , ebx 
    shr eax , 8
    mov dx  , 0x01F4
    out dx  , al 

    ;send 8bit on byte2 of sectors base to chip register 0x01F5
    mov eax , ebx 
    shr eax , 16
    mov dx  , 0x01F5
    out dx  , al

    ;lateer on will explained 
    mov dx , 0x01F7
    mov al , 0x20
    out dx , al

    ;Read All sectors to memory address contained on register esi 
    .nextSector:
        push ecx
    
    .WaitDisk:
        mov  dx , 0x01F7
        in   al , dx 
        test al , 8 ;if bit 7 is not set flag zero will be set
        jz .WaitDisk
    .ReadSector:
        mov ecx , 256
        mov dx  , 0x01F0
        rep insw 
        ;insw : reads a word from dx io address ,
        ;stores is back to edi address
        ;and add 2 on the edi
        ;rep : is prefix that do the command insw/or whatever ,
        ;checks if ecx is zero , if not
        ;then is execute the op command and dicrements ecx by one
        ;else stops executing (this command can be interrupted at any point )
        pop  ecx
        loop .nextSector ;decriments the ecx by one and if ecx != 0 jumps to label
    
    ret



times 510-($-$$) db 0
Signature_0x55AA: dw 0xAA55 
; intel 80386 is little endian that why 0xAA55 will 
; saved on the binnary file as 0x55AA  

Buffer:
Karnel:
