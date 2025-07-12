ORG 0x0000
BITS 16

;BIOS Possible parameter block
BIOS_BLOCK:
    ; based on osdev org BPB first command
    jmp short entry_point
    nop 
times (29) db 0

driver_number: db 0

interrupt_habdle_zero:
    mov ah , 0x000e
    mov al , 'A'
    mov bx , 0
    int 0x10
    iret 



entry_point:
    jmp 0x7c0:init ; Αναγκάζει τον cs register να πάρει την τιμή 0x7c0 και να κάνει αλμα στην εντολή offset init 

init:
    cli 
    mov ax , 0x07c0
    mov bx , 0x0000
    ;mov cs , ax 
    mov ds , ax
    mov ss , bx 
    mov sp , 0x7c00
    mov es , ax 
    ; save driver number
    mov byte[driver_number] , dl 
    sti 
init_interrupts:
    mov word[ss:0x00] , interrupt_habdle_zero
    mov word[ss:0x02] , 0x07c0

test_interrupt:
    int 0x00 ; by call (software interrupt call)
    mov ax , 0x0000
    div ax ; ganaerate the interrupt by processor as exception

start:
    loadNextSector:
        mov ah , 02h;
        mov al , 1 ; number of sectors
        mov ch , 0 ; cylinder number 
        mov cl , 2 ; second sector (start from 1 as first )
        mov dh , 0 ; first head
        ;dl is given by the bios 
        mov dl , byte[driver_number]
        mov bx , message 
        int 0x13
        jc print_error
    print_text:
        mov si , message 
        call print 
        jmp $ ; to your self
        

    print_error:
    mov si , error_message 
    call print 
    jmp $ ; to your self

print:
    mov bx , 0;
.loop0:
    lodsb 
    cmp al , 0
    je .done 
    call print_character
    jmp .loop0
.done: 
    ret 


print_character:
    mov ah , 0eh ; special command for this interrupt routine of the bios
    int 0x10 ; a bios interrupt routine that is provided 
    ret 

error_message: db 'Failed to load next Sector' , 0

times 510 - ($ - $$) db 0



bootSignature:
    dw 0xAA55 ; 55AA the way a bios recognise the boot sector on the specific disk
message:


