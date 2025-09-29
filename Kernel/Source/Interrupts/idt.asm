[BITS 32]
section .asm

;Procedure      : idtr_load
;c Definition   : extern void idtr_load(idtr* ptr)
;Parameter      : ptr that is pointer to idtr structure that x86 understands
;Description    : purpose is to load the new interrupt descriptor table that we want 
;                 in to the microprocessor , so it can refer to it after a interrupt
;                 (software , external or exception) has generated 
;Return's       : Nothing 
;Warning        : This is a ring level 0 privilige procedure , if the cpl is not zero 
;                 a GP(General Perpuse ) exception is generated . 
;Author         : Dimitris Smyrnakis

global idtr_load
idtr_load:
    push ebp
    mov  ebp , esp

    mov ebx , [ebp + 8] ; take parameter
    lidt [ebx]

    
    pop ebp
    ret


global idtr_store
idtr_store:
    push ebp
    mov ebp , esp 

    mov eax , [ebp + 8]
    sidt [eax]

    pop ebp 
    ret 

global enable_intt
enable_intt:
    sti 
    ret

global disable_intt
disable_intt:
    cli
    ret 

extern default_handler
global isr_default
isr_default:
    pusha
    call default_handler
    popa
    iretd