BITS 32
section .asm

global _x86_32_eflags_write
global _x86_32_eflags_read

_x86_32_eflags_write:
    push ebp
    mov  ebp , esp

    mov ebx , DWORD [ebp + 8]
    mov ebx , DWORD [ebx]
    push ebx
    popfd

    pop  ebp
    ret

_x86_32_eflags_read:
    push ebp
    mov  ebp , esp

    mov ebx , DWORD [ebp + 8]
    pushfd
    pop eax 
    mov DWORD [ebx] , eax

    pop  ebp
    ret

    