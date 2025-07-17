BITS 32
section .asm


global _x86_32_inb;
_x86_32_inb:
    push ebp
    mov  ebp , esp 

    mov dx , WORD [ebp + 8]
    in  al , dx 

    pop  ebp
    ret 

global _x86_32_inw;
_x86_32_inw:
    push ebp
    mov  ebp , esp

    mov dx , WORD [ebp + 8]
    in  ax , dx

    pop  ebp
    ret

global _x86_32_ind
_x86_32_ind:
    push ebp
    mov  ebp , esp

    mov  dx , WORD [ebp + 8]
    in  eax , dx

    pop ebp
    ret





global _x86_32_outb;
_x86_32_outb:
    push ebp
    mov  ebp ,esp
    
    mov  dx , WORD [ebp + 8]
    mov  al , BYTE [ebp + 12]
    out dx , al

    pop ebp
    ret 

global _x86_32_outw;
_x86_32_outw:
    push ebp
    mov  ebp , esp 

    mov dx , WORD [ebp +  8]
    mov ax , WORD [ebp + 12]
    out dx , ax

    pop ebp
    ret

global _x86_32_outd;
_x86_32_outd:
    push ebp
    mov  ebp , esp

    mov  dx , WORD  [ebp +  8]
    mov eax , DWORD [ebp + 12]
    out  dx , eax

    pop ebp
    ret










global _x86_32_insb;
_x86_32_insb:
    push ebp ;
    mov  ebp , esp

    mov dx , WORD [ebp + 8]
    xor ecx , ecx
    mov  cx , WORD [ebp + 12]
    mov edi , DWORD [ebp + 16]
    cld
    rep insb 

    pop  ebp
    ret 

global _x86_32_insw;
_x86_32_insw:
    push ebp;
    mov  ebp , esp 

    mov  dx , WORD [ebp +  8]
    xor ecx , ecx
    mov  cx , WORD [ebp + 12]
    imul cx , 2
    mov edi , DWORD[ebp + 16]
    cld
    rep insw

    pop ebp
    ret

global _x86_32_insd;
_x86_32_insd:
    push ebp;
    mov  ebp , esp 

    mov  dx , WORD [ebp +  8]
    xor ecx , ecx
    mov  cx , WORD [ebp + 12]
    imul cx , 4
    mov edi , DWORD[ebp + 16]
    cld
    rep insd  

    pop ebp
    ret










global _x86_32_outsb;
_x86_32_outsb:
    push ebp
    mov  ebp , esp

    mov  dx , WORD [ebp +  8]
    xor ecx , ecx
    mov  cx , WORD [ebp + 12]
    mov esi , DWORD[ebp + 16]
    cld
    rep outsd

    pop ebp
    ret

global _x86_32_outsw;
_x86_32_outsw:
    push ebp
    mov  ebp , esp

    mov  dx , WORD [ebp +  8]
    xor ecx , ecx
    mov  cx , WORD [ebp + 12]
    imul cx , 2
    mov esi , DWORD[ebp + 16]
    cld
    rep outsw

    pop  ebp
    ret

global _x86_32_outsd;
_x86_32_outsd:
    push ebp
    mov  ebp , esp

    mov  dx , WORD [ebp +  8]
    xor ecx , ecx
    mov  cx , WORD [ebp + 12]
    imul cx , 4
    mov esi , DWORD[ebp + 16]
    cld
    rep outsd

    pop  ebp
    ret
















