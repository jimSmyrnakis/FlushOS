BITS 32
section .asm

global _x86_32_ecode_read;
_x86_32_ecode_read:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp +  8]  ; take the address of the _x86_32_ecode variable
    mov  ecx , DWORD[ebp + 12]  ; take the value of the ecode (32bits total)
    mov DWORD[ebx] , ecx        ; mov the ecode value to the address memory that is the _x86_32_ecode variable    

    pop  ebp
    ret

global _x86_32_ecode_write;
_x86_32_ecode_write:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp +  8]  ; take the address of the _x86_32_ecode variable
    mov  ecx , DWORD[ebx]       ; take the value of this variable
    mov DWORD[ebp + 12] , ecx   ; save it to the ecode on the stack

    pop  ebp
    ret
