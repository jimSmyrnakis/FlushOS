BITS 32

section .asm

global outb 
outb:
    push ebp
    mov ebp , esp 

    xor eax , eax
    mov edx , [ebp + 8]
    mov eax , [ebp + 12]
    out dx , al 

    pop  ebp
    ret 

global outw 
outw:
    push ebp
    mov ebp , esp 
    
    xor eax , eax
    mov edx , [ebp + 8]
    mov eax , [ebp + 12]
    out dx , ax 

    pop  ebp
    ret 

global inb 
inb:
    push ebp
    mov ebp , esp 

    xor eax , eax
    mov dx , word[ebp + 8]
    in al , dx 

    pop  ebp
    ret 

global inw 
inw:
    push ebp
    mov ebp , esp 

    xor eax , eax
    mov dx , word[ebp + 8]
    in ax , dx 

    pop  ebp
    ret 