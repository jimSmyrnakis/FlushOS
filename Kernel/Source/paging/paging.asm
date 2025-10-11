[BITS 32]
section .asm

;extern void paging_enable(void);

global paging_enable
paging_enable:
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax
    ret

;extern void paging_disable(void);
global paging_disable
paging_disable:
    mov eax , cr0 
    and eax , 0x7FFFFFFE
    mov cr0 , eax 
    ret 

;extern void paging_load(void* dt_physical_address);
global paging_load
paging_load:
    push ebp 
    mov ebp , esp 
    push ebx 

    mov eax , [ebp  + 8]
    mov cr3 , eax 

    pop ebx 
    pop ebp 
    ret 