#ifndef X86_32_GDT_H
#define X86_32_GDT_H

    #include "../dtables.h"


    struct _x86_32_gdt_descriptor{

        uint16_t zero ; // zero is for allingment 
        uint16_t limit; // the beggining of limit is where the gdt descriptor actualy start
        uint32_t base ; // base address of the gdt table 

    }X86_32_SYSTEM_STRUCT;
    /*
     *
     *
     * This struct is a system struct , means that it must be not optimized or the compiler alligned the data types
     * because thats the way the processor must find the data . The zero field is there only for perfomance alligment
     * as specified in the intel's system programming volume . The alligment must be multyple of 16 witch is multyple of 8 
     * that the system struct is. Base is the base address that the gdt table starts and base + limit is the address of the
     * last byte in the gdt . zero field can be any value but i call it zero just as a way to note that is unused field 
    */

    #define x86_32_gdt_descriptor_set(Gdt_descriptor , Limit , Base ) {(Gdt_descriptor).zero = 0; (Gdt_descriptor).limit = (Limit); (Gdt_descriptor).base = (Base);}

    extern void     X86_32_CALL _x86_32_set_gdtr(struct _x86_32_gdt_descriptor* desc);
    extern void     X86_32_CALL _x86_32_get_gdtr(struct _x86_32_gdt_descriptor* desc);
    /* set gdt register with the gdt descriptor or get the gdt descriptor , code here is in assembly level only*/
    

    struct x86_32_gdt{
        struct x86_32_dtable tbl; // the dtable struct for the descriptor table
    };

    x86_32_err_type X86_32_CALL x86_32_gdt_init(
        struct x86_32_gdt*          gdt           ,
        void*                       begin_addr    ,
        void*                       end_addr      ,
        struct _x86_32_descriptor   init_val  
    );
    /*
     *
     *
     * Is the same with x86_32_dtable_init but the max_capacity is 0xFFFF + 1 
    */

    x86_32_err_type X86_32_CALL x86_32_gdt_set_descriptor(
        struct x86_32_gdt*          gdt         ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );
    /* The same as x86_32_dtable_set_descriptor but index= 0 is a new error (X86_32_E_GDTANLDESCR) */
    
    x86_32_err_type X86_32_CALL x86_32_gdt_get_descriptor(
        struct x86_32_gdt*          gdt         ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );
    /* The same as x86_32_dtable_get_descriptor and is for index = 0 too ok to use */



    #define x86_32_gdt_set_gdt_descriptor(gdt, gdt_desc) x86_32_gdt_descriptor_set( gdt_desc , (uint32_t)(gdt).tbl.base , (gdt).tbl.limit ) 
    
    void X86_32_CALL x86_32_gdt_descriptor_set_gdt(struct x86_32_gdt* dest , const struct _x86_32_gdt_descriptor* src);
    /*initiallize the gdt table with the gdt table that the gdt descriptor points to */


#endif 