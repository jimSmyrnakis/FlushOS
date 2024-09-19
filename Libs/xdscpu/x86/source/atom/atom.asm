BITS 32
section .asm

global _x86_atom_exchange_8
_x86_atom_exchange_8:
    push ebp
    mov  ebp , esp

    mov ebx , DWORD [ebp +  8]
    mov eax , DWORD [ebp + 12]
    xchg BYTE[ebx] , al 

    pop  ebp
    ret 

global _x86_atom_exchange_16
_x86_atom_exchange_16:
    push ebp
    mov  ebp , esp

    mov ebx , DWORD [ebp +  8]
    mov eax , DWORD [ebp + 12]
    xchg WORD[ebx] , ax 

    pop  ebp
    ret 

global _x86_atom_exchange_32
_x86_atom_exchange_32:
    push ebp
    mov  ebp , esp

    mov ebx , DWORD [ebp +  8]
    mov eax , DWORD [ebp + 12]
    xchg DWORD[ebx] , eax 

    pop  ebp
    ret 
