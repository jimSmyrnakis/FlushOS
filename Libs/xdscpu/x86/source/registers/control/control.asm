BITS 32
section .asm

;extern void X86_32_CALL x86_32_cr0_write(const x86_32_cr0* reg_value);
global _x86_32_cr0_write
_x86_32_cr0_write:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD [ebp + 8]; take address of the 32 bit value on stack
    mov  ebx , DWORD [ebp + 8]; take value from this address
    mov  cr0 , ebx            ; write the value to cr0 register

    pop  ebp
    ret 

;extern void X86_32_CALL x86_32_cr2_write(const x86_32_cr2* reg_value);
global _x86_32_cr2_write
_x86_32_cr2_write:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD [ebp + 8]; take address of the 32 bit value on stack
    mov  ebx , DWORD [ebp + 8]; take value from this address
    mov  cr2 , ebx            ; write the value to cr2 register

    pop  ebp
    ret 

;extern void X86_32_CALL x86_32_cr3_write(const x86_32_cr3* reg_value);
global _x86_32_cr3_write
_x86_32_cr3_write:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD [ebp + 8]; take address of the 32 bit value on stack
    mov  ebx , DWORD [ebp + 8]; take value from this address
    mov  cr3 , ebx            ; write the value to cr3 register

    pop  ebp
    ret 

;extern void X86_32_CALL x86_32_cr4_write(const x86_32_cr4* reg_value);
global _x86_32_cr4_write
_x86_32_cr4_write:
    push ebp
    mov  ebp , esp

    mov  ebx , DWORD [ebp + 8]; take address of the 32 bit value on stack
    mov  ebx , DWORD [ebp + 8]; take value from this address
    mov  cr4 , ebx            ; write the value to cr4 register

    pop  ebp
    ret 

































;extern void X86_32_CALL x86_32_cr0_read (const x86_32_cr0* reg_value);
global _x86_32_cr0_read
_x86_32_cr0_read:
    push ebp 
    mov  ebp , esp 

    mov  ebx , DWORD [ebp + 8]; take address of the destination value where the cr0 reg will copied
    mov  ecx , cr0            ; take the value to other 32 bit register
    mov  DWORD [ebx] , ecx    ; copy value to the destination
  
    pop  ebp 
    ret 

;extern void X86_32_CALL x86_32_cr2_read (const x86_32_cr2* reg_value);
global _x86_32_cr2_read
_x86_32_cr2_read:
    push ebp 
    mov  ebp , esp 

    mov  ebx , DWORD [ebp + 8]; take address of the destination value where the cr2 reg will copied
    mov  ecx , cr2            ; take the value to other 32 bit register
    mov  DWORD [ebx] , ecx    ; copy value to the destination
  
    pop  ebp 
    ret 

;extern void X86_32_CALL x86_32_cr3_read (const x86_32_cr3* reg_value);
global _x86_32_cr3_read
_x86_32_cr3_read:
    push ebp 
    mov  ebp , esp 

    mov  ebx , DWORD [ebp + 8]; take address of the destination value where the cr3 reg will copied
    mov  ecx , cr3            ; take the value to other 32 bit register
    mov  DWORD [ebx] , ecx    ; copy value to the destination
  
    pop  ebp 
    ret 

;extern void X86_32_CALL x86_32_cr4_read (const x86_32_cr4* reg_value);
global _x86_32_cr4_read
_x86_32_cr4_read:
    push ebp 
    mov  ebp , esp 

    mov  ebx , DWORD [ebp + 8]; take address of the destination value where the cr4 reg will copied
    mov  ecx , cr4            ; take the value to other 32 bit register
    mov  DWORD [ebx] , ecx    ; copy value to the destination
  
    pop  ebp 
    ret 