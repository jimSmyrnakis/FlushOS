BITS 32
section .asm

global _x86_32_set_cs
_x86_32_set_cs:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx , WORD [ebx]
    mov   cs , cx   

    pop  ebp
    ret

global _x86_32_set_ds
_x86_32_set_ds:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx ,  WORD[ebx]
    mov   ds , cx

    pop  ebp
    ret

global _x86_32_set_ss
_x86_32_set_ss:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx ,  WORD[ebx]
    mov   ss , cx

    pop  ebp
    ret


global _x86_32_set_gs
_x86_32_set_gs:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx ,  WORD[ebx]
    mov   gs , cx

    pop  ebp
    ret


global _x86_32_set_fs
_x86_32_set_fs:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx ,  WORD[ebx]
    mov   fs , cx

    pop  ebp
    ret



global _x86_32_get_cs
_x86_32_get_cs:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx , cs
    mov   WORD [ebx] , cx 

    pop  ebp
    ret

global _x86_32_get_ds
_x86_32_get_ds:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx , ds
    mov   WORD [ebx] , cx 

    pop  ebp
    ret

global _x86_32_get_ss
_x86_32_get_ss:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx , ss
    mov   WORD [ebx] , cx 

    pop  ebp
    ret

global _x86_32_get_fs
_x86_32_get_fs:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx , fs
    mov   WORD [ebx] , cx 

    pop  ebp
    ret

global _x86_32_get_gs
_x86_32_get_gs:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD[ebp + 8]
    mov   cx , gs
    mov   WORD [ebx] , cx 

    pop  ebp
    ret



