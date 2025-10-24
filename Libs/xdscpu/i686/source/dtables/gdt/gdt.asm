BITS 32
section .asm

;Author : Dimitris Smyrnakis
;Details: This is ring 0 privilige procedure that loads the gdtr register
;extern void X86_32_CALL _x86_32_set_gdtr(struct x86_32_gdt_descriptor* desc);
global _x86_32_set_gdtr
_x86_32_set_gdtr:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD [ebp + 8] ;take the address of the gdt descriptor from the stack
    add  ebx ,  2 ;first 2 bytes are field zero for allignment
    lgdt [ebx] ;take the address and load it to gdt segment register

    pop  ebp
    ret 

;Author: Dimitris Smyrnakis 
;Details: Return's the gdtr limit and base by filling these field's in the struct 
;extern void X86_32_CALL _x86_32_get_gdtr(struct x86_32_gdt_descriptor* desc);
global _x86_32_get_gdtr
_x86_32_get_gdtr:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD [ebp + 8] ; take the address of the gdt descriptor from the stack
    add  ebx , 2 ; move two bytes addresses more so start pointing to limit field
    sgdt [ebx] ; take the value of the gdt register and load it to gdt descriptor

    pop  ebp 
    ret 

    