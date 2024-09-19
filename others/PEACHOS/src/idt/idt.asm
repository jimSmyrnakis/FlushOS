BITS 32
section .asm

global enableInterrupts
enableInterrupts:
    sti
    ret

global disableInterrupts
disableInterrupts:
    cli
    ret

global loadIdtTable
loadIdtTable:
    push ebp
    mov ebp , esp

    mov eax , [ebp + 8]
    lidt [eax]

    pop  ebp
    ret

global storeIdtTable
storeIdtTable:
    push ebp
    mov ebp , esp

    mov eax , [ebp + 8]
    sidt [eax]

    pop  ebp
    ret 
    