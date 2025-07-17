BITS 32
section .asm

global _x86_32_dr0_write;
_x86_32_dr0_write:
    push ebp;
    mov  ebp , esp

    mov  eax , dr0
    mov  ebx , DWORD[ebp + 8]
    mov DWORD[ebx] , eax 

    pop ebp
    ret 

global _x86_32_dr1_write;
_x86_32_dr1_write:
    push ebp;
    mov  ebp , esp

    mov  eax , dr1
    mov  ebx , DWORD[ebp + 8]
    mov DWORD[ebx] , eax 

    pop ebp
    ret 

global _x86_32_dr2_write;
_x86_32_dr2_write:
    push ebp;
    mov  ebp , esp

    mov  eax , dr2
    mov  ebx , DWORD[ebp + 8]
    mov DWORD[ebx] , eax 

    pop ebp
    ret 

global _x86_32_dr3_write;
_x86_32_dr3_write:
    push ebp;
    mov  ebp , esp

    mov  eax , dr3
    mov  ebx , DWORD[ebp + 8]
    mov DWORD[ebx] , eax 

    pop ebp
    ret 

global _x86_32_dr6_write;
_x86_32_dr6_write:
    push ebp;
    mov  ebp , esp

    mov  eax , dr6
    mov  ebx , DWORD[ebp + 8]
    mov DWORD[ebx] , eax 

    pop ebp
    ret 

global _x86_32_dr7_write;
_x86_32_dr7_write:
    push ebp;
    mov  ebp , esp

    mov  eax , dr7
    mov  ebx , DWORD[ebp + 8]
    mov DWORD[ebx] , eax 

    pop ebp
    ret 


global _x86_32_dr0_read;
_x86_32_dr0_read:
    push ebp
    mov  ebp , esp

    mov ecx , DWORD[ebp + 8]
    mov ebx , DWORD[ecx]
    mov eax , ebx
    mov dr0 , eax

    pop  ebp
    ret

global _x86_32_dr1_read;
_x86_32_dr1_read:
    push ebp
    mov  ebp , esp

    mov ecx , DWORD[ebp + 8]
    mov ebx , DWORD[ecx]
    mov eax , ebx
    mov dr1 , eax

    pop  ebp
    ret

global _x86_32_dr2_read;
_x86_32_dr2_read:
    push ebp
    mov  ebp , esp

    mov ecx , DWORD[ebp + 8]
    mov ebx , DWORD[ecx]
    mov eax , ebx
    mov dr2 , eax

    pop  ebp
    ret

global _x86_32_dr3_read;
_x86_32_dr3_read:
    push ebp
    mov  ebp , esp

    mov ecx , DWORD[ebp + 8]
    mov ebx , DWORD[ecx]
    mov eax , ebx
    mov dr3 , eax

    pop  ebp
    ret

global _x86_32_dr6_read;
_x86_32_dr6_read:
    push ebp
    mov  ebp , esp

    mov ecx , DWORD[ebp + 8]
    mov ebx , DWORD[ecx]
    mov eax , ebx
    mov dr6 , eax

    pop  ebp
    ret

global _x86_32_dr7_read;
_x86_32_dr7_read:
    push ebp
    mov  ebp , esp

    mov ecx , DWORD[ebp + 8]
    mov ebx , DWORD[ecx]
    mov eax , ebx
    mov dr7 , eax

    pop  ebp
    ret
