#ifndef X86_32_DTABLES_H
#define X86_32_DTABLES_H

    #include "../core.h"
    #include "../error.h"
    #include "../descriptors/descriptors.h"
    #include "../descriptors/segment/segment.h"
    #include "../descriptors/system/system.h"

    /**
     * @author : Dimitris Smyrnakis
     * @details: This struct defines any descriptor table found on x86 protected mode architecture 
     * , these tables are gdt , ldt and idt . What is what is not a concern of the dtable 
     * struct , mainly corcern is where this struct is and loading it with many different descriptor
     * as simple bytes . The meaning of the descriptors still is not a concern of this struct , only 
     * inserting , removing and any reusable multiple times common code can be found here .  
     */
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

    /**
     * @author: Dimitris Smyrnakis
     * @brief: Initiallize the descriptor table memory
     * @param dt Is the table structure that contains all the information needed for accessing the descriptor table
     * @param begin_addr Is the address where the descriptor table will loaded in memory
     * @param end_addr Is the last byte on the space given (if is 1MB for examble the end_addr = begin_addr + 1MB - 1)
     * @param max_capacity Is just for security , checking if the table is not bigger than what the cpu specifies 
     * @param init_val Is the descriptor value that every descriptor in the table will load it in the initiallization
     * @return ==> 
     *              1. X86_32_E_OK if everything is ok 
     *              2. X86_32_E_BADPARAM if max capacity parameter is less than the descriptor size or addresses re NULL or the max capacity is zero
     *              3. X86_32_E_SMLSPC if space is not enough for at least two descriptor's 
     *              4. X86_32_E_UNALIGNELMNT if the base is not align to the descriptor size 
     * @warning ==> 
     *              1. If the beggin and end address are not multyple of descriptor size the capacity in dt struct do not
     *              contain the extra unused bytes . 
     *              2. If the same happen with max capacity then the dt->max_capacity is set to a multyple
     *              of descriptor size and the unused bytes are removed .
     * 
     */
    x86_32_err_type X86_32_CALL x86_32_dtable_init(
        struct x86_32_dtable*       dt            ,
        void*                       begin_addr    ,
        void*                       end_addr      ,
        uint32_t                    max_capacity  ,
        struct _x86_32_descriptor   init_val  
    );

    /**
     * @author Dimitris Smyrnakis
     * @brief Insert a new descriptor value on the (initialized) table at specific index
     * @param dt Is the descriptor table struct  
     * @param index Is the specific descriptor element in the table
     * @param desc A pointer to the new pointer value that must copy to the descriptor table of the system
     * @return ==> 
     *              1. X86_32_E_OK : if everything is succefull 
     *              2. X86_32_E_BADPARAM : If dt or desc is NULL
     *              3. X86_32_E_OOR : If the index is bigger than the number of available descriptor's in the table
     * 
     */
    x86_32_err_type X86_32_CALL x86_32_dtable_set_descriptor(
        struct x86_32_dtable*       dt          ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );

    /**
     * @author Dimitris Smyrnakis
     * @brief return's the descriptor value on the (initialized) table at the specific index
     * @param dt Is the descriptor table struct  
     * @param index Is the specific descriptor element in the table
     * @param desc A pointer to the new pointer value that must copy to the descriptor table of the system
     * @return ==> 
     *              1. X86_32_E_OK : if everything is succefull 
     *              2. X86_32_E_BADPARAM : If dt or desc is NULL
     *              3. X86_32_E_OOR : If the index is bigger than the number of available descriptor's in the table
     * 
     */
    x86_32_err_type X86_32_CALL x86_32_dtable_get_descriptor(
        struct x86_32_dtable*       dt          ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );


    /**
     * @author: Dimitris Smyrnakis
     * @brief : A macro that return's the total available descriptors in the table
     * @param : Just the descriptor table struct , works only if the table is right initialized
     */
    #define x86_32_dtable_size(dt) ((dt)->capacity/sizeof(struct _x86_32_descriptor))

#endif 