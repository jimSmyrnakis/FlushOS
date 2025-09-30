[BITS 32]
section .asm

; Author : Dimitris Smyrnakis




; C signature : extern void outb(uint8_t data , uint16_t port)
; Parameters  : 
;           1. data : The 8 bit value 
;           2. port : 16 bit port address where data will send to
; Return's    : Nothing
; Description : Send's data to the specified destination port 
global outb;
outb:
    push ebp 
    mov ebp , esp

    mov al ,  [ebp + 8 ]; data
    mov edx , [ebp + 12]; port
    

    out dx , al 

    pop ebp 
    ret 

global outw
outw:
    push ebp 
    mov ebp , esp 

    mov ax , [ebp + 8 ]; data
    mov edx , [ebp + 12]; port
    
    out dx , ax 

    pop ebp 
    ret 

global outd
outd:
    push ebp 
    mov ebp , esp 

    mov eax , [ebp + 8 ]; data
    mov edx , [ebp + 12]; port
    
    out dx , eax 

    pop ebp 
    ret 

global inb;
inb:
    push ebp 
    mov ebp  ,esp 

    mov ebx , [ebp + 8 ] ; data pointer (8 bit val)
    mov edx , [ebp + 12] ; port address (16bit val)
    in al , dx 
    mov [ebx] , al  ;

    pop ebp 
    ret 

global inw;
inw:
    push ebp 
    mov ebp  ,esp 

    mov ebx , [ebp + 8 ] ; data pointer (16bit val)
    mov edx , [ebp + 12] ; port address (16bit val)
    in  ax, dx 
    mov [ebx] , ax  ;

    pop ebp 
    ret 

global ind;
ind:
    push ebp 
    mov ebp  ,esp 

    mov ebx , [ebp + 8 ] ; data pointer (32bit val)
    mov edx , [ebp + 12] ; port address (16bit val)
    in  eax, dx 
    mov [ebx] , eax  ;

    pop ebp 
    ret 

