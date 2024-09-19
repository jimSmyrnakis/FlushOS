#ifndef X86_32_DEBUG_REGISTERS_H
#define X86_32_DEBUG_REGISTERS_H

    #include "../../core.h"
    #include "../../error.h"

    typedef uint32_t _x86_32_dr0; //breakpoint0
    typedef uint32_t _x86_32_dr1; //breakpoint1
    typedef uint32_t _x86_32_dr2; //breakpoint2
    typedef uint32_t _x86_32_dr3; //breakpoint3
    typedef uint32_t _x86_32_dr6; //debug status register
    typedef uint32_t _x86_32_dr7; //debug control register


    
    struct x86_32_dr0{
        void* breakpoint0_laddr;
    };

    struct x86_32_dr1{
        void* breakpoint1_laddr;
    };

    struct x86_32_dr2{
        void* breakpoint2_laddr;
    };

    struct x86_32_dr3{
        void* breakpoint3_laddr;
    };

    struct x86_32_dr6{ // Note : This register must be clear from the exception procedure / task
        bool    b0  ;       // breakpoint0 condition detected           --bit 00
        bool    b1  ;       // breakpoint0 condition detected           --bit 01
        bool    b2  ;       // breakpoint0 condition detected           --bit 02
        bool    b3  ;       // breakpoint0 condition detected           --bit 03
        bool    bd  ;       // debug register access condition          --bit 13
        bool    bs  ;       // single step execution condition          --bit 14
        bool    bt  ;       // task switch condition                    --bit 15
        // reserved bit 12 clear
        // reserved bit's 4-11 , 16-31 must be set
    };

    enum x86_32_rwi{
        x86_32_rwi_instructions=0,   // 00
        x86_32_rwi_data_writes =1,   // 01
        x86_32_rwi_io_access   =2,   // 10 or undefined
        x86_32_rwi_data_access =3    // 11
    };
    enum x86_32_leni{
        x86_32_leni_byte  = 0 ,     // 00
        x86_32_leni_word  = 1 ,     // 01
        x86_32_leni_dword = 3 ,     // 11
        x86_32_leni_qword = 2       // 10 or undefined

    };
    struct x86_32_dr7{
        //reversed bits 8-9 , 11 - 12 and 14-15 must be zero
        //reserved bit 10 must be 1
        bool                l0 ;        // local breakpoint0 enable in set for the current task only (task switch clears it)            --bit 00
        bool                l1 ;        // local breakpoint1 enable in set for the current task only (task switch clears it)            --bit 02
        bool                l2 ;        // local breakpoint2 enable in set for the current task only (task switch clears it)            --bit 04
        bool                l3 ;        // local breakpoint3 enable in set for the current task only (task switch clears it)            --bit 06
        bool                g0 ;        // global breakpoint0 enable in set for all the tasks (task switch no effect on it)             --bit 01
        bool                g1 ;        // global breakpoint1 enable in set for all the tasks (task switch no effect on it)             --bit 03
        bool                g2 ;        // global breakpoint2 enable in set for all the tasks (task switch no effect on it)             --bit 05
        bool                g3 ;        // global breakpoint3 enable in set for all the tasks (task switch no effect on it)             --bit 07
        bool                gd ;        // generate debug at debug registers access                                                     --bit 13
        enum   x86_32_rwi   rw0;        // instr , data write , data access and io access conditions for breakpoint0                    --bit 16-17
        enum   x86_32_rwi   rw1;        // instr , data write , data access and io access conditions for breakpoint1                    --bit 20-21
        enum   x86_32_rwi   rw2;        // instr , data write , data access and io access conditions for breakpoint2                    --bit 24-25
        enum   x86_32_rwi   rw3;        // instr , data write , data access and io access conditions for breakpoint3                    --bit 28-29        
        enum   x86_32_leni  ln0;        // byte , word , dword , qword bounds conditions for breakpoint0                                --bit 18-19
        enum   x86_32_leni  ln1;        // byte , word , dword , qword bounds conditions for breakpoint1                                --bit 22-23
        enum   x86_32_leni  ln2;        // byte , word , dword , qword bounds conditions for breakpoint2                                --bit 26-27
        enum   x86_32_leni  ln3;        // byte , word , dword , qword bounds conditions for breakpoint3                                --bit 30-31
    };




    void X86_32_CALL x86_32_dr0_set(struct x86_32_dr0* dest , const _x86_32_dr0* src);
    void X86_32_CALL x86_32_dr1_set(struct x86_32_dr1* dest , const _x86_32_dr1* src);
    void X86_32_CALL x86_32_dr2_set(struct x86_32_dr2* dest , const _x86_32_dr2* src);
    void X86_32_CALL x86_32_dr3_set(struct x86_32_dr3* dest , const _x86_32_dr3* src);

    void X86_32_CALL x86_32_dr0_get(_x86_32_dr0* dest , const struct x86_32_dr0* src);
    void X86_32_CALL x86_32_dr1_get(_x86_32_dr1* dest , const struct x86_32_dr1* src);
    void X86_32_CALL x86_32_dr2_get(_x86_32_dr2* dest , const struct x86_32_dr2* src);
    void X86_32_CALL x86_32_dr3_get(_x86_32_dr3* dest , const struct x86_32_dr3* src);

    void X86_32_CALL x86_32_dr6_get(struct x86_32_dr6* dest , const _x86_32_dr6* src);
    void X86_32_CALL x86_32_dr7_get(struct x86_32_dr7* dest , const _x86_32_dr7* src);

    void X86_32_CALL x86_32_dr6_set(_x86_32_dr6* dest , const struct x86_32_dr6* src);
    void X86_32_CALL x86_32_dr7_set(_x86_32_dr7* dest , const struct x86_32_dr7* src);

    extern void X86_32_CALL _x86_32_dr0_write(_x86_32_dr0* val);
    extern void X86_32_CALL _x86_32_dr1_write(_x86_32_dr1* val);
    extern void X86_32_CALL _x86_32_dr2_write(_x86_32_dr2* val);
    extern void X86_32_CALL _x86_32_dr3_write(_x86_32_dr3* val);
    extern void X86_32_CALL _x86_32_dr6_write(_x86_32_dr6* val);
    extern void X86_32_CALL _x86_32_dr7_write(_x86_32_dr7* val);

    extern void X86_32_CALL _x86_32_dr0_read(_x86_32_dr0* val);
    extern void X86_32_CALL _x86_32_dr1_read(_x86_32_dr1* val);
    extern void X86_32_CALL _x86_32_dr2_read(_x86_32_dr2* val);
    extern void X86_32_CALL _x86_32_dr3_read(_x86_32_dr3* val);
    extern void X86_32_CALL _x86_32_dr6_read(_x86_32_dr6* val);
    extern void X86_32_CALL _x86_32_dr7_read(_x86_32_dr7* val);

#endif 