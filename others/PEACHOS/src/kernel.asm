BITS 32

extern kmain
global makeProblem

gdtCodeIndex equ 0x08
gdtDataIndex equ 0x10

global _kernelInit_
_kernelInit_:
    mov ax , gdtDataIndex
    mov ds , ax
    mov ss , ax
    mov es , ax
    mov gs , ax
    mov fs , ax
    mov ebp, 0x00200000
    mov esp , ebp
    
    ;enable a20 line using the fast way with a special keyboard chip 
    ;that is used to enable A20 line
    in al , 0x92 ;read register chip
    or al , 2 ; set bit 1 
    out 0x92 , al ;write register chip the new value
    
    mov al , 0x11 ; give value to the status register of the 
    out 0x20 , al ; tell master pic
    mov al , 0x20 ; where all external interrupt vectors start
    out 0x21 , al ; give the value to the pic 
    mov al , 0x01 ; i dont now
    out 0x21 , al ; i just now master pic remap all external interrupts
    ;from interrupt vector index 32 and after (or 0x20 and after) so the
    ;ints from 0 - 31 stays for processor exceptions and faults that is the
    ;default



    call kmain

    jmp $

makeProblem:
    xor eax , eax 
    div eax
    int 0x21
    ret


times 512-($-$$) db 0
; we put this to the text section with result that we need to be sure it 
; will allign perfect to 16 (512 % 16 = 0)