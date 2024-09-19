BITS 32
section .asm


global loadPageDirectory
loadPageDirectory:
    push ebp
    mov ebp , esp

    mov eax , [ebp + 8]
    mov cr3 , eax

    pop  ebp
    ret 

global storePageDirectory
storePageDirectory:
    push ebp 
    mov ebp , esp

    mov eax , dword[ebp + 8]
    mov ebx , cr3
    mov dword[eax] , ebx

    pop  ebp
    ret 

global enablePaging
enablePaging: 
    push ebp
    mov ebp , esp

    mov eax , cr0
    or  eax , 0x80000000
    mov cr0 , eax 

    pop  ebp 
    ret 

global disablePaging
disablePaging:
    push ebp 
    mov ebp ,esp 

    mov eax , cr0 
    mov ebx , 0x7FFFFFFF
    and eax , ebx
    mov cr0 , eax 

    pop  ebp 
    ret 
    