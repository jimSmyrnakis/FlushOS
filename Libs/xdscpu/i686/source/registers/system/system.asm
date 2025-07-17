BITS 32
section .asm


global _x86_32_set_tr
_x86_32_set_tr:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx ,  WORD[ebx]
    ltr   cx

    pop  ebp
    ret

global _x86_32_set_ldtr
_x86_32_set_ldtr:
    push ebp
    mov  ebp , esp

    mov ebx , DWORD[ebp + 8]
    mov  cx ,  WORD[ebx]
    lldt cx

    pop ebp
    ret




global _x86_32_get_tr
_x86_32_get_tr:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    str   cx
    mov   WORD [ebx] , cx 

    pop  ebp
    ret

global _x86_32_get_ldtr
_x86_32_get_ldtr:
    push ebp
    mov  ebp , esp

    mov ebx , DWORD[ebp + 8]
    sldt cx
    mov WORD [ebx] , cx 

    pop ebp
    ret 