[BITS 32]

CODE_SEGMENT equ 0x08
DATA_SEGMENT equ 0x10

extern kernel_main
global kernel_init
global problem
kernel_init:
    cli 
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
    
    call kernel_main
    jmp $


problem:
    int 0
    ret 

times 512 - ($ - $$) db 0
