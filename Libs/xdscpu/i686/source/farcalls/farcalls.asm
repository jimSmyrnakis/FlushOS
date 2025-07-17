BITS 32
section .asm

extern _far_struct_base;

_x86_32_far_call:
    mov eax , DWORD[ebp + 6]
    call far [eax] 
    ret