ORG 0x7c00
BITS 16

CODE_SEGMENT equ  Code_Descriptor - global_descriptor_table
DATA_SEGMENT equ  Data_Descriptor - global_descriptor_table
;BIOS Possible parameter block
BIOS_BLOCK:
    ; based on osdev org BPB first command
    jmp short entry_point
    nop 
times (33) db 0



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
        
        jmp CODE_SEGMENT:load32 ; load code selector and move to load32 place
        

    
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


;===========================================================================================================================
;============================================== 32 bit protected mode ======================================================
;===========================================================================================================================
[BITS 32]

load32:
    ;αρχικοποιήση τμήματος δεδομένων σε όλους τους data segment registers
    mov ax , DATA_SEGMENT
    mov ds , ax
    mov ss , ax 
    mov es , ax 
    mov fs , ax
    mov gs , ax
    mov ebp , 0x00200000
    mov esp , ebp 

    ; αρχικοποιή το Αddress bit 20 του επεξεργαστή . όμως μόνο στα σημερηνά συστήματα λειτουργή .
    enable_A20_line:
        in al , 0x92 
        or al , 2
        out 0x92 , al 

    jmp $



times 510 - ($ - $$) db 0



bootSignature:
    dw 0xAA55 ; 55AA the way a bios recognise the boot sector on the specific disk
message:


