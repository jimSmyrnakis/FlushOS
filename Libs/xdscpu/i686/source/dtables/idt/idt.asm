BITS 32
section .asm

;extern void X86_32_CALL _x86_32_set_idtr(struct x86_32_idt_descriptor* desc);
global _x86_32_set_idtr
_x86_32_set_idtr:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD [ebp + 8] ;take the address of the gdt descriptor from the stack
    add  ebx ,  2 ;first 2 bytes are field zero for allignment
    lidt [ebx] ;take the address and load it to idt segment register

    pop  ebp
    ret 

;extern void X86_32_CALL _x86_32_get_idtr(struct x86_32_idt_descriptor* desc);
global _x86_32_get_idtr
_x86_32_get_idtr:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD [ebp + 8] ; take the address of the gdt descriptor from the stack
    add  ebx , 2 ; move two bytes addresses more so start pointing to limit field
    sidt [ebx] ; take the value of the idt register and load it to idt descriptor

    pop  ebp 
    ret 
