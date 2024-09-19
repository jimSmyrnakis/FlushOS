#include "debug.h"

void X86_32_CALL x86_32_dr0_set(struct x86_32_dr0* dest , const _x86_32_dr0* src) { dest->breakpoint0_laddr = (void*)(*src); }
void X86_32_CALL x86_32_dr1_set(struct x86_32_dr1* dest , const _x86_32_dr1* src) { dest->breakpoint1_laddr = (void*)(*src); }
void X86_32_CALL x86_32_dr2_set(struct x86_32_dr2* dest , const _x86_32_dr2* src) { dest->breakpoint2_laddr = (void*)(*src); }
void X86_32_CALL x86_32_dr3_set(struct x86_32_dr3* dest , const _x86_32_dr3* src) { dest->breakpoint3_laddr = (void*)(*src); }

void X86_32_CALL x86_32_dr0_get(_x86_32_dr0* dest , const struct x86_32_dr0* src) { (*dest) = (uint32_t)src->breakpoint0_laddr; }
void X86_32_CALL x86_32_dr1_get(_x86_32_dr1* dest , const struct x86_32_dr1* src) { (*dest) = (uint32_t)src->breakpoint1_laddr; }
void X86_32_CALL x86_32_dr2_get(_x86_32_dr2* dest , const struct x86_32_dr2* src) { (*dest) = (uint32_t)src->breakpoint2_laddr; }
void X86_32_CALL x86_32_dr3_get(_x86_32_dr3* dest , const struct x86_32_dr3* src) { (*dest) = (uint32_t)src->breakpoint3_laddr; }

#define DR6_INIT ((_x86_32_dr6) 0xFFFF0FF0 ) // reserved bit's that must be set are set and clear as specified
#define DR6_B0   X86_32_SET_BIT(_x86_32_dr6 ,  0)
#define DR6_B1   X86_32_SET_BIT(_x86_32_dr6 ,  1)
#define DR6_B2   X86_32_SET_BIT(_x86_32_dr6 ,  2)
#define DR6_B3   X86_32_SET_BIT(_x86_32_dr6 ,  3)
#define DR6_BD   X86_32_SET_BIT(_x86_32_dr6 , 13)
#define DR6_BS   X86_32_SET_BIT(_x86_32_dr6 , 14)
#define DR6_BT   X86_32_SET_BIT(_x86_32_dr6 , 15)

#define DR7_INIT        X86_32_SET_BIT(_x86_32_dr7, 10)
#define DR7_L0          X86_32_SET_BIT(_x86_32_dr7,  0)
#define DR7_G0          X86_32_SET_BIT(_x86_32_dr7,  1)
#define DR7_L1          X86_32_SET_BIT(_x86_32_dr7,  2)
#define DR7_G1          X86_32_SET_BIT(_x86_32_dr7,  3)
#define DR7_L2          X86_32_SET_BIT(_x86_32_dr7,  4)
#define DR7_G2          X86_32_SET_BIT(_x86_32_dr7,  5)
#define DR7_L3          X86_32_SET_BIT(_x86_32_dr7,  6)
#define DR7_G3          X86_32_SET_BIT(_x86_32_dr7,  7)
#define DR7_GD          X86_32_SET_BIT(_x86_32_dr7, 13)
#define DR7_RW0_MASK    ( X86_32_SET_BIT(_x86_32_dr7, 17)  |  X86_32_SET_BIT(_x86_32_dr7, 16))
#define DR7_RW0_INSTR   (~X86_32_SET_BIT(_x86_32_dr7, 17)  | ~X86_32_SET_BIT(_x86_32_dr7, 16))
#define DR7_RW0_DTWRT   (~X86_32_SET_BIT(_x86_32_dr7, 17)  |  X86_32_SET_BIT(_x86_32_dr7, 16))
#define DR7_RW0_IOACS   ( X86_32_SET_BIT(_x86_32_dr7, 17)  | ~X86_32_SET_BIT(_x86_32_dr7, 16))
#define DR7_RW0_DTACS   ( X86_32_SET_BIT(_x86_32_dr7, 17)  |  X86_32_SET_BIT(_x86_32_dr7, 16))
#define DR7_LN0_MASK    ( X86_32_SET_BIT(_x86_32_dr7, 19)  |  X86_32_SET_BIT(_x86_32_dr7, 18))
#define DR7_LN0_BYTE    (~X86_32_SET_BIT(_x86_32_dr7, 19)  | ~X86_32_SET_BIT(_x86_32_dr7, 18))
#define DR7_LN0_WORD    (~X86_32_SET_BIT(_x86_32_dr7, 19)  |  X86_32_SET_BIT(_x86_32_dr7, 18))
#define DR7_LN0_QWORD   ( X86_32_SET_BIT(_x86_32_dr7, 19)  | ~X86_32_SET_BIT(_x86_32_dr7, 18))
#define DR7_LN0_DWORD   ( X86_32_SET_BIT(_x86_32_dr7, 19)  |  X86_32_SET_BIT(_x86_32_dr7, 18))
#define DR7_RW1_MASK    ( X86_32_SET_BIT(_x86_32_dr7, 21)  |  X86_32_SET_BIT(_x86_32_dr7, 20))
#define DR7_RW1_INSTR   (~X86_32_SET_BIT(_x86_32_dr7, 21)  | ~X86_32_SET_BIT(_x86_32_dr7, 20))
#define DR7_RW1_DTWRT   (~X86_32_SET_BIT(_x86_32_dr7, 21)  |  X86_32_SET_BIT(_x86_32_dr7, 20))
#define DR7_RW1_IOACS   ( X86_32_SET_BIT(_x86_32_dr7, 21)  | ~X86_32_SET_BIT(_x86_32_dr7, 20))
#define DR7_RW1_DTACS   ( X86_32_SET_BIT(_x86_32_dr7, 21)  |  X86_32_SET_BIT(_x86_32_dr7, 20))
#define DR7_LN1_MASK    ( X86_32_SET_BIT(_x86_32_dr7, 23)  |  X86_32_SET_BIT(_x86_32_dr7, 22))
#define DR7_LN1_BYTE    (~X86_32_SET_BIT(_x86_32_dr7, 23)  | ~X86_32_SET_BIT(_x86_32_dr7, 22))
#define DR7_LN1_WORD    (~X86_32_SET_BIT(_x86_32_dr7, 23)  |  X86_32_SET_BIT(_x86_32_dr7, 22))
#define DR7_LN1_QWORD   ( X86_32_SET_BIT(_x86_32_dr7, 23)  | ~X86_32_SET_BIT(_x86_32_dr7, 22))
#define DR7_LN1_DWORD   ( X86_32_SET_BIT(_x86_32_dr7, 23)  |  X86_32_SET_BIT(_x86_32_dr7, 22))
#define DR7_RW2_MASK    ( X86_32_SET_BIT(_x86_32_dr7, 25)  |  X86_32_SET_BIT(_x86_32_dr7, 24))
#define DR7_RW2_INSTR   (~X86_32_SET_BIT(_x86_32_dr7, 25)  | ~X86_32_SET_BIT(_x86_32_dr7, 24))
#define DR7_RW2_DTWRT   (~X86_32_SET_BIT(_x86_32_dr7, 25)  |  X86_32_SET_BIT(_x86_32_dr7, 24))
#define DR7_RW2_IOACS   ( X86_32_SET_BIT(_x86_32_dr7, 25)  | ~X86_32_SET_BIT(_x86_32_dr7, 24))
#define DR7_RW2_DTACS   ( X86_32_SET_BIT(_x86_32_dr7, 25)  |  X86_32_SET_BIT(_x86_32_dr7, 24))
#define DR7_LN2_MASK    ( X86_32_SET_BIT(_x86_32_dr7, 27)  |  X86_32_SET_BIT(_x86_32_dr7, 26))
#define DR7_LN2_BYTE    (~X86_32_SET_BIT(_x86_32_dr7, 27)  | ~X86_32_SET_BIT(_x86_32_dr7, 26))
#define DR7_LN2_WORD    (~X86_32_SET_BIT(_x86_32_dr7, 27)  |  X86_32_SET_BIT(_x86_32_dr7, 26))
#define DR7_LN2_QWORD   ( X86_32_SET_BIT(_x86_32_dr7, 27)  | ~X86_32_SET_BIT(_x86_32_dr7, 26))
#define DR7_LN2_DWORD   ( X86_32_SET_BIT(_x86_32_dr7, 27)  |  X86_32_SET_BIT(_x86_32_dr7, 26))
#define DR7_RW3_MASK    ( X86_32_SET_BIT(_x86_32_dr7, 29)  |  X86_32_SET_BIT(_x86_32_dr7, 28))
#define DR7_RW3_INSTR   (~X86_32_SET_BIT(_x86_32_dr7, 29)  | ~X86_32_SET_BIT(_x86_32_dr7, 28))
#define DR7_RW3_DTWRT   (~X86_32_SET_BIT(_x86_32_dr7, 29)  |  X86_32_SET_BIT(_x86_32_dr7, 28))
#define DR7_RW3_IOACS   ( X86_32_SET_BIT(_x86_32_dr7, 29)  | ~X86_32_SET_BIT(_x86_32_dr7, 28))
#define DR7_RW3_DTACS   ( X86_32_SET_BIT(_x86_32_dr7, 29)  |  X86_32_SET_BIT(_x86_32_dr7, 28))
#define DR7_LN3_MASK    ( X86_32_SET_BIT(_x86_32_dr7, 31)  |  X86_32_SET_BIT(_x86_32_dr7, 30))
#define DR7_LN3_BYTE    (~X86_32_SET_BIT(_x86_32_dr7, 31)  | ~X86_32_SET_BIT(_x86_32_dr7, 30))
#define DR7_LN3_WORD    (~X86_32_SET_BIT(_x86_32_dr7, 31)  |  X86_32_SET_BIT(_x86_32_dr7, 30))
#define DR7_LN3_QWORD   ( X86_32_SET_BIT(_x86_32_dr7, 31)  | ~X86_32_SET_BIT(_x86_32_dr7, 30))
#define DR7_LN3_DWORD   ( X86_32_SET_BIT(_x86_32_dr7, 31)  |  X86_32_SET_BIT(_x86_32_dr7, 30))

#define instructions    x86_32_rwi_instructions
#define io_access       x86_32_rwi_io_access
#define data_access     x86_32_rwi_data_access
#define data_writes      x86_32_rwi_data_writes

#define byte        x86_32_leni_byte
#define word        x86_32_leni_word
#define dword       x86_32_leni_dword
#define qword       x86_32_leni_qword

void X86_32_CALL x86_32_dr6_set(_x86_32_dr6* dest , const struct x86_32_dr6* src){
    (*dest) = DR6_INIT;
    x86_32_fast_set( src->b0 , dest , DR6_B0 );
    x86_32_fast_set( src->b1 , dest , DR6_B1 );
    x86_32_fast_set( src->b2 , dest , DR6_B2 );
    x86_32_fast_set( src->b3 , dest , DR6_B3 );
    x86_32_fast_set( src->bd , dest , DR6_BD );
    x86_32_fast_set( src->bs , dest , DR6_BS );
    x86_32_fast_set( src->bt , dest , DR6_BT );
}

void X86_32_CALL x86_32_dr7_set(_x86_32_dr7* dest , const struct x86_32_dr7* src){
    (*dest) = DR7_INIT;
    x86_32_fast_set( src->g0 , dest , DR7_G0 );
    x86_32_fast_set( src->g1 , dest , DR7_G1 );
    x86_32_fast_set( src->g2 , dest , DR7_G2 );
    x86_32_fast_set( src->g3 , dest , DR7_G3 );
    x86_32_fast_set( src->l0 , dest , DR7_L0 );
    x86_32_fast_set( src->l1 , dest , DR7_L1 );
    x86_32_fast_set( src->l2 , dest , DR7_L2 );
    x86_32_fast_set( src->l3 , dest , DR7_L3 );
    x86_32_fast_set( src->gd , dest , DR7_GD );
    
    
    
    //set rw0
    switch(src->rw0){ 
        case instructions: (*dest) |= DR7_RW0_INSTR; break; 
        case io_access   : (*dest) |= DR7_RW0_IOACS; break; 
        case data_writes : (*dest) |= DR7_RW0_DTWRT; break; 
        case data_access : (*dest) |= DR7_RW0_DTACS; break; 
    };
    //set rw1
    switch(src->rw1){ 
        case instructions: (*dest) |= DR7_RW1_INSTR; break; 
        case io_access   : (*dest) |= DR7_RW1_IOACS; break; 
        case data_writes : (*dest) |= DR7_RW1_DTWRT; break; 
        case data_access : (*dest) |= DR7_RW1_DTACS; break; 
    };
    //set rw2
    switch(src->rw2){ 
        case instructions: (*dest) |= DR7_RW2_INSTR; break; 
        case io_access   : (*dest) |= DR7_RW2_IOACS; break; 
        case data_writes : (*dest) |= DR7_RW2_DTWRT; break; 
        case data_access : (*dest) |= DR7_RW2_DTACS; break; 
    };
    //set rw3
    switch(src->rw3){ 
        case instructions: (*dest) |= DR7_RW3_INSTR; break; 
        case io_access   : (*dest) |= DR7_RW3_IOACS; break; 
        case data_writes : (*dest) |= DR7_RW3_DTWRT; break; 
        case data_access : (*dest) |= DR7_RW3_DTACS; break; 
    };


    //set ln0
    switch(src->ln0){
        case byte   : (*dest) |= DR7_LN0_BYTE ; break;
        case word   : (*dest) |= DR7_LN0_WORD ; break;
        case dword  : (*dest) |= DR7_LN0_DWORD; break;
        case qword  : (*dest) |= DR7_LN0_QWORD; break;
    };
    //set ln1
    switch(src->ln1){
        case byte   : (*dest) |= DR7_LN1_BYTE ; break;
        case word   : (*dest) |= DR7_LN1_WORD ; break;
        case dword  : (*dest) |= DR7_LN1_DWORD; break;
        case qword  : (*dest) |= DR7_LN1_QWORD; break;
    };
    //set ln2
    switch(src->ln2){
        case byte   : (*dest) |= DR7_LN2_BYTE ; break;
        case word   : (*dest) |= DR7_LN2_WORD ; break;
        case dword  : (*dest) |= DR7_LN2_DWORD; break;
        case qword  : (*dest) |= DR7_LN2_QWORD; break;
    };
    //set ln3
    switch(src->ln3){
        case byte   : (*dest) |= DR7_LN3_BYTE ; break;
        case word   : (*dest) |= DR7_LN3_WORD ; break;
        case dword  : (*dest) |= DR7_LN3_DWORD; break;
        case qword  : (*dest) |= DR7_LN3_QWORD; break;
    };

}

void X86_32_CALL x86_32_dr6_get(struct x86_32_dr6* dest , const _x86_32_dr6* src ){

    x86_32_fast_get(src , DR6_B0 , dest->b0 );
    x86_32_fast_get(src , DR6_B1 , dest->b1 );
    x86_32_fast_get(src , DR6_B2 , dest->b2 );
    x86_32_fast_get(src , DR6_B3 , dest->b3 );
    x86_32_fast_get(src , DR6_BD , dest->bd );
    x86_32_fast_get(src , DR6_BS , dest->bs );
    x86_32_fast_get(src , DR6_BT , dest->bt );

}

void X86_32_CALL x86_32_dr7_get(struct x86_32_dr7* dest , const _x86_32_dr7* src ){

    x86_32_fast_get(src , DR7_G0 , dest->g0 );
    x86_32_fast_get(src , DR7_G1 , dest->g1 );
    x86_32_fast_get(src , DR7_G2 , dest->g2 );
    x86_32_fast_get(src , DR7_G3 , dest->g3 );
    x86_32_fast_get(src , DR7_L0 , dest->l0 );
    x86_32_fast_get(src , DR7_L1 , dest->l1 );
    x86_32_fast_get(src , DR7_L2 , dest->l2 );
    x86_32_fast_get(src , DR7_L3 , dest->l3 );
    x86_32_fast_get(src , DR7_GD , dest->gd );

    //get ln0
    switch( (*src) & DR7_LN0_MASK){
        case DR7_LN0_BYTE : dest->ln0 = byte ; break;
        case DR7_LN0_WORD : dest->ln0 = word ; break;
        case DR7_LN0_DWORD: dest->ln0 = dword; break;
        case DR7_LN0_QWORD: dest->ln0 = qword; break;
    };
    //get ln1
    switch( (*src) & DR7_LN0_MASK){
        case DR7_LN1_BYTE : dest->ln1 = byte ; break;
        case DR7_LN1_WORD : dest->ln1 = word ; break;
        case DR7_LN1_DWORD: dest->ln1 = dword; break;
        case DR7_LN1_QWORD: dest->ln1 = qword; break;
    };
    //get ln2
    switch( (*src) & DR7_LN2_MASK){
        case DR7_LN2_BYTE : dest->ln2 = byte ; break;
        case DR7_LN2_WORD : dest->ln2 = word ; break;
        case DR7_LN2_DWORD: dest->ln2 = dword; break;
        case DR7_LN2_QWORD: dest->ln2 = qword; break;
    };
    //get ln3
    switch( (*src) & DR7_LN3_MASK){
        case DR7_LN3_BYTE : dest->ln3 = byte ; break;
        case DR7_LN3_WORD : dest->ln3 = word ; break;
        case DR7_LN3_DWORD: dest->ln3 = dword; break;
        case DR7_LN3_QWORD: dest->ln3 = qword; break;
    };

    //get rw0
    switch( (*src) & DR7_RW0_MASK){
        case DR7_RW0_INSTR: dest->rw0 = instructions; break;
        case DR7_RW0_DTWRT: dest->rw0 = data_writes ; break;
        case DR7_RW0_DTACS: dest->rw0 = data_access ; break;
        case DR7_RW0_IOACS: dest->rw0 = io_access   ; break;
    };
    //get rw1
    switch( (*src) & DR7_RW1_MASK){
        case DR7_RW1_INSTR: dest->rw1 = instructions; break;
        case DR7_RW1_DTWRT: dest->rw1 = data_writes ; break;
        case DR7_RW1_DTACS: dest->rw1 = data_access ; break;
        case DR7_RW1_IOACS: dest->rw1 = io_access   ; break;
    };
    //get rw2
    switch( (*src) & DR7_RW2_MASK){
        case DR7_RW2_INSTR: dest->rw2 = instructions; break;
        case DR7_RW2_DTWRT: dest->rw2 = data_writes ; break;
        case DR7_RW2_DTACS: dest->rw2 = data_access ; break;
        case DR7_RW2_IOACS: dest->rw2 = io_access   ; break;
    };
    //get rw3
    switch( (*src) & DR7_RW3_MASK){
        case DR7_RW3_INSTR: dest->rw3 = instructions; break;
        case DR7_RW3_DTWRT: dest->rw3 = data_writes ; break;
        case DR7_RW3_DTACS: dest->rw3 = data_access ; break;
        case DR7_RW3_IOACS: dest->rw3 = io_access   ; break;
    };

}