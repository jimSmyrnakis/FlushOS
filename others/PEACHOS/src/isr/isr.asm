BITS 32
section .asm


extern handler0
global idtHandler0
idtHandler0:
    cli
    ;pushad 
    call handler0

    ;popad 
    mov eax , 100
    iret 


extern handler21
global idtHandler21
idtHandler21:
    cli
    pushad ;push all G.P.R.'s

    call handler21;
    
    popad ;pop all gpr
    sti
    iret 


extern defaultHandler
global idtDefaultHandler
idtDefaultHandler:
    cli
    pushad ;push all G.P.R.'s

    call defaultHandler

    popad ;pop all gpr
    sti
    iret 


