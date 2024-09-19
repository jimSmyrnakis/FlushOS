#ifndef X86_32_IDT_H
#define X86_32_IDT_H

    #include "../dtables.h"

    struct _x86_32_idt_descriptor{
        uint16_t zero;  // for alligment (good cache fill)
        uint16_t limit; // limit of the idt (0 = 1 byte)
        uint32_t base;  // the base linear address 
    }X86_32_SYSTEM_STRUCT;
    /*like the gdt_descriptor but for interrupt descriptor table */

    extern void X86_32_CALL _x86_32_set_idtr(const struct _x86_32_idt_descriptor* idtd);
    extern void X86_32_CALL _x86_32_get_idtr(      struct _x86_32_idt_descriptor* idtd);

    #define x86_32_idt_descriptor_set(Idt_descriptor , Limit , Base ) {(Idt_descriptor).zero = 0; (Idt_descriptor).limit = (Limit); (Idt_descriptor).base = (Base);}


    struct x86_32_idt{
        struct x86_32_dtable tbl; // the dtable struct for the descriptor table
    };

    x86_32_err_type X86_32_CALL x86_32_idt_init(
        struct x86_32_idt*          idt           ,
        void*                       begin_addr    ,
        void*                       end_addr      ,
        struct _x86_32_descriptor   init_val  
    );
    /*
     *
     *
     * Is the same with x86_32_dtable_init but the max_capacity is 256*sizeof(descriptor)
    */

    x86_32_err_type X86_32_CALL x86_32_idt_set_descriptor(
        struct x86_32_idt*          idt         ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );
    /* The same as x86_32_dtable_set_descriptor */
    
    x86_32_err_type X86_32_CALL x86_32_idt_get_descriptor(
        struct x86_32_idt*          idt         ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );
    /* The same as x86_32_dtable_get_descriptor */



    #define x86_32_idt_set_idt_descriptor(idt, idt_desc) x86_32_idt_descriptor_set( idt_desc , (uint32_t)(idt).tbl.base , (idt).tbl.limit ) 
    
    void X86_32_CALL x86_32_idt_descriptor_set_idt(struct x86_32_idt* dest , const struct _x86_32_idt_descriptor* src);
    /*initiallize the idt table with the idt table that the idt descriptor points to */

#endif 