BITS 32
section .asm

global _x86_32_cli
_x86_32_cli:
    cli 
    ret 

global _x86_32_sti
_x86_32_sti:
    sti
    ret

global _X86_32_iret;
_x86_32_iret:
    iret
    ret

    
      

