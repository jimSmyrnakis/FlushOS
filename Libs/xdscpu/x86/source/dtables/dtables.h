#ifndef X86_32_DTABLES_H
#define X86_32_DTABLES_H

    #include "../core.h"
    #include "../error.h"
    #include "../descriptors/descriptors.h"
    #include "../descriptors/segment/segment.h"
    #include "../descriptors/system/system.h"

    struct x86_32_dtable{  
        uint32_t                    capacity    ; //number of bytes that are given for the desrioptor table (gdt,ldt,idt)
        uint32_t                    max_capacity; // max capacity of the descriptor table in bytes (for example a idt is 256*sizeof(struct _x86_32_descriptor) size in bytes)
        struct _x86_32_descriptor*  base        ; //the first address of the descriptor table
    };

    /*
     *
     *
     * Note : max_capacity identifies how many bytes in max the specific descriptor table can take not how mutch are given .
     *      If capacity found greater than max_capacity in the initiallization of the table then capacity == max_capacity  .
    */

    x86_32_err_type X86_32_CALL x86_32_dtable_init(
        struct x86_32_dtable*       dt            ,
        void*                       begin_addr    ,
        void*                       end_addr      ,
        uint32_t                    max_capacity  ,
        struct _x86_32_descriptor   init_val  
    );
    /*
     *
     *
     * dt ==> is the table structure that contains all the information needed for accessing the descriptor table
     * begin_addr ==> is the base address for the space that is given
     * end_addr ==> is the address of the last byte for the space that is given
     * max_capacity ==> is the max number of bytes for the descriptor table (is different beetween ldt,gdt and idt)   
     * init_val => Is the descriptor value that will initiallized all the descriptor table 
     * Return ==> 
     *              1. X86_32_E_OK if everything is ok 
     *              2. X86_32_E_BADPARAM if max capacity parameter is less than the descriptor size
     *              3. X86_32_E_SMLSPC if space is not enough even for one descriptor
     * More Info ==> If the beggin and end address are not multyple of descriptor size the capacity in dt struct do not
     * contain the extra unused bytes . If the same happen with max capacity then the dt->max_capacity is set to a multyple
     * of descriptor size and the unused bytes are removed .
    */

    x86_32_err_type X86_32_CALL x86_32_dtable_set_descriptor(
        struct x86_32_dtable*       dt          ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );
    /*
    *
    *
    * The dt is the dtable struct that must be initiallized first , then index is the descriptor position in an array
    * of descriptor's and the desc is the new element that will be added to the descriptor table (idt,ldt,gdt)
    * 
    * Return ==> X86_32_E_OK if everything is ok or X86_32_E_OOR for out of range (index >= size)
    */

    x86_32_err_type X86_32_CALL x86_32_dtable_get_descriptor(
        struct x86_32_dtable*       dt          ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );
    /*
     *
     *
     * as x86_32_dtable_set_descriptor but the desc pointer set with the value of the descriptor in this index
     * 
     * Return => X86_32_E_OK or X86_32_E_OOR for index >= size
    */

   #define x86_32_dtable_size(dt) ((dt)->capacity/sizeof(struct _x86_32_descriptor))

#endif 