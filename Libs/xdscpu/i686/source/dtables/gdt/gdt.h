#ifndef X86_32_GDT_H
#define X86_32_GDT_H

    #include "../dtables.h"


/*==============================================================================
  ===============================GDTR===========================================
  ==============================================================================
*/

    /**
     * @author Dimitris Smyrnakis
     * @details This struct (and every struct start's with _ ) is a cpu specific struct , and the
     * zero field is a good usage as specified by intel documantation , alignment with 4 bytes is 
     * required for avoiding alignment check fault's and perfomance penaldy
     */
    struct _x86_32_gdtr{

        uint16_t zero ; // zero is for alingment 
        uint16_t limit; // the beggining of limit is where the gdt descriptor actualy start
        uint32_t base ; // base address of the gdt table 

    }X86_32_SYSTEM_STRUCT;

    /**
     * @author Dimitris Smyrnakis
     * @details A very simple micro that set's all the fields for the gdtr (register) 
     */
    #define x86_32_gdtr_set(Gdt_descriptor , Limit , Base ) {(Gdt_descriptor).zero = 0; (Gdt_descriptor).limit = (Limit); (Gdt_descriptor).base = (Base);}

    /**
     * @author Dimitris Smyrnakis
     * @details This function is implemented in assembly (using intel syntax) and loads the gdtr register on the cpu
     */
    extern void     X86_32_CALL _x86_32_set_gdtr(struct _x86_32_gdtr* desc);
    /**
     * @author Dimitris Smyrnakis
     * @details This function is implemented in assembly (intel syntax) and store's back to the struct the gdtr register values(limit,base)
     */
    extern void     X86_32_CALL _x86_32_get_gdtr(struct _x86_32_gdtr* desc);
    
/*==============================================================================
  ===============================GDT============================================
  ==============================================================================
*/

    /**
     * @author Dimitris Smyrnakis 
     * @brief A struct that has the gdt table descriptor 
     */
    struct x86_32_gdt{
        struct x86_32_dtable tbl; // the dtable struct for the descriptor table
    };


    /**
     * @author Dimitris Smyrnakis
     * @brief Same as dtable init exacly , (for moment we don't do any check specific to gdt)
     */
    x86_32_err_type X86_32_CALL x86_32_gdt_init(
        struct x86_32_gdt*          gdt           ,
        void*                       begin_addr    ,
        void*                       end_addr      ,
        struct _x86_32_descriptor   init_val  
    );

    /**
     * @author Dimitris Smyrnakis
     * @brief Same as dtable set descriptor exacly , (for moment we don't do any check specific to gdt)
     */
    x86_32_err_type X86_32_CALL x86_32_gdt_set_descriptor(
        struct x86_32_gdt*          gdt         ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );

    /**
     * @author Dimitris Smyrnakis
     * @brief Same as dtable get descriptor exacly , (for moment we don't do any check specific to gdt)
     */
    x86_32_err_type X86_32_CALL x86_32_gdt_get_descriptor(
        struct x86_32_gdt*          gdt         ,
        uint16_t                    index       ,
        struct _x86_32_descriptor*  desc 
    );

/*==============================================================================
  ===============================GDT And GDTR===================================
  ==============================================================================
*/


    /**
     * @author Dimitris Smyrnakis
     * @brief takes a gdt struct and gdtr struct and fills in the gdtr , all by value (This is a macro for moment)
     */
    #define x86_32_gdt_set_gdtr(gdt, gdtr) x86_32_gdtr_set( gdtr , (uint32_t)(gdt).tbl.base , (gdt).tbl.limit ) 
    
    /**
     * @author Dimitris Smyrnakis
     * @brief 
     */
    void X86_32_CALL x86_32_gdtr_set_gdt(struct x86_32_gdt* dest , const struct _x86_32_gdtr* src);
    /*initiallize the gdt table with the gdt table that the gdtr points to */


#endif 