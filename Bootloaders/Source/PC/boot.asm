ORG 0x7c00
BITS 16

CODE_SEGMENT equ  Code_Descriptor - global_descriptor_table
DATA_SEGMENT equ  Data_Descriptor - global_descriptor_table
;BIOS Possible parameter block
BIOS_PARAMETER_BLOCK: ; BPB
    ; based on osdev org BPB first command
    jmp short entry_point
    nop 
    OEMIdentifier           db 'FLUSHOS ' ; an identifier that is used by us to recognise (may not even needed)
    BytesPerSector          dw 0x200; bytes per sector , this has to do with the permenant disk type and so kernels generly ignore that , better ask the disk him self
    SectorsPerCluster       db 0x80 ; each cluster has a number of sectors
    ReservedSectors         dw 200  ; 200 RESEVED SECTORS used for the os (100MB)
    FATCopies               db 0x02 ; 2 FAT (FAT1 , FAT2)
    RootDirEntries          dw 0x40 ; 64 root directories entries
    NumSectors              dw 0x00 ; don't care
    MediaType               db 0xF8 ; don't care
    SectorsPerFat           dw 0x100 ; how many sectors per FAT (BPB,EBPB,RESEVED,FAT1,FAT2,DATA_CLUSTERS)
    SectorsPerTrack         dw 0x20 ; don't care we use lba already and we are can't trust strangers
    NumberOfHeads           dw 0x40 ; don't care (don't trust strangers make the driver for the device and ask via the chip your self)
    HiddenSectors           dd 0x00 ; no any (but could be usefull for system data of processes)
    SectorsBig              dd 0x773594 
EXTENDED_BIOS_PARAMETER_BLOCK: ; EBPB
    DriveNumber             db 0x80 ; 
    WinNTBit                db 0x00
    Signature               db 0x29
    VolumeID                dd 0xD105
    VolumeIDString          db 'FLUSHOS BOO'
    SystemIDString          db 'FAT16   '



entry_point:
    jmp 0:init ; Αναγκάζει τον cs register να πάρει την τιμή 0 και να κάνει αλμα στην εντολή offset init 

init:
    cli 
    mov ax , 0x0000
    mov bx , 0x0000
    ;mov cs , ax 
    mov ds , ax
    mov ss , bx 
    mov sp , 0x7c00
    mov es , ax 
    sti 
start:
    cli
    
    init_descriptors:
        cli 
        lgdt [gdt_descriptor]
        
    enable_protected_mode:
        mov eax , cr0 
        or eax , 0x00000001 ; PE flag to set protected mode
        
        mov cr0 , eax 
        
        jmp CODE_SEGMENT:load32
        

    
global_descriptor_table:
    null_descriptor:    
        dd 0
        dd 0
        
; 0000 0000 1000 0000 
; 0x 0 0    8 0

    ;==============Code Segment descriptor ==================
Code_Descriptor:
    ; limit first 16 bits
    dw 0xFFFF
    ; base 16 first bits
    dw 0x0000
    ; next 8 bits of base 
    db 0x00
    ; special flags
    db 0x9A ; code segment with read access 
    db 0xCF ; granuarity + compatibility mode + 32-bit addresses + 19-16 bits limit to ones 
    db 0x00 ; base last 8 bits to 0
    ;==============Data Segment descriptor ==================
Data_Descriptor:
    ; limit first 16 bits
    dw 0xFFFF
    ; base 16 first bits
    dw 0x0000
    ; next 8 bits of base 
    db 0x00
    ; special flags
    db 0x92 ; data segment with write access 
    db 0xCF ; granuarity + compatibility mode + 32-bit addresses + 19-16 bits limit to ones 
    db 0x00 ; base last 8 bits to 0
global_descriptor_table_end:

gdt_descriptor:
    dw global_descriptor_table_end - (global_descriptor_table) - 1
    dd global_descriptor_table


[BITS 32]
load32: ; Χρήση ενός απλού οδηγού σκληρού δίσκου για την φώρτωση όλου του πυρίνα 
    mov eax , 1 ; πρώτο μπλόκ του δίσκου
    mov ecx , 100 ; 10 συνολικά μπλόκς 
    mov edi , 0x0100000 ; προόρισμός στην διεύθυνση 1ΜΒ όπου περιμένουμε να αρχίση ο πυρίνας
    call ata_lba_read
    jmp CODE_SEGMENT:0x0100000


ata_lba_read:
    mov ebx , eax ; temp store sector index
    ; Send high 8 bits to the lba hd controller
    shr eax , 24
    or eax , 0xE0 ; Select master drive
    mov dx , 0x1F6
    out dx , al 

    ; Send total sectors
    mov eax , ecx 
    mov dx , 0x1F2
    out dx , al 


    ; Send more bits of the lba (first byte)
    mov eax , ebx ; take the temp lba 
    mov dx , 0x1F3
    out dx , al 

    ; Send second lba byte 
    mov eax , ebx 
    mov dx , 0x1F4
    shr eax , 8
    out dx , al

    ; Send 3thrd byte of lba
    mov dx , 0x1F5
    mov eax , ebx 
    shr eax , 16
    out dx , al 

    ; 
    mov dx , 0x1F7
    mov al , 0x20
    out dx , al 

    ; Read all sectors to the memory with polling method (this is just something to work for beggining )
    .next_sector
        push ecx ; back up ecx
    ; check if a sector is available with polling
    .try_again
        mov dx , 0x1F7
        in al , dx 
        test al , 8
        jz .try_again
    ; read the sector
        mov ecx , 256
        mov dx , 0x1F0 
        rep insw ; rep repeats this instruction as many as ecx counter is set , here is 256
        ; where insw or in string word (16-bit) reads a byte from the port dx (0x1F0) and stores it 
        ; to the edi register 
        pop ecx ; restore ecx value
        loop .next_sector 

    ret 

TEST_TEXT_DISK2: db 'THIS TEXT HERE IS FOR TESTING WITH BLESS '

times 510 - ($ - $$) db 0



bootSignature:
    dw 0xAA55 ; 55AA the way a bios recognise the boot sector on the specific disk



