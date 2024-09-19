#include "pgdr.h"

x86_32_err_type X86_32_CALL x86_32_pdir_set(const struct x86_32_pdir* pd){
    x86_32_err_type err = X86_32_E_OK;

    //write to cr3 request struct 
    struct x86_32_cr3 cr3_request;
    cr3_request.pwt    =  pd->write_through ;
    cr3_request.pcd    = !pd->caching       ;
    cr3_request.pdbase =  pd->addr          ;

    //get the real value to be loaded
    _x86_32_cr3 cr3_value;
    err = x86_32_cr3_set(&cr3_value , &cr3_request);
    if (err != X86_32_E_OK)
        goto out;
        
    //write the value to the actual register
    _x86_32_cr3_write(&cr3_value);

    //page directory is loaded to the register

out:
    return err;
}

void X86_32_CALL x86_32_pdir_get(struct x86_32_pdir* pd){
        
    //read the value from the cr3 register
    _x86_32_cr3 cr3_value;
    _x86_32_cr3_read(&cr3_value);

    //write that value to request cr3
    struct x86_32_cr3 cr3_request;
    x86_32_cr3_get(&cr3_request , &cr3_value);

    //save the value to the structure
    pd->caching         = !cr3_request.pcd   ;
    pd->write_through   =  cr3_request.pwt   ;
    pd->addr            =  cr3_request.pdbase;

}

void X86_32_CALL x86_32_enable_paging(void){
    _x86_32_cr0       cr0_value  ;
    struct x86_32_cr0 cr0_request;

    //read the cr0 value
    _x86_32_cr0_read(&cr0_value);

    //write the value to a request cr0 structure
    x86_32_cr0_get(&cr0_request , &cr0_value);

    //change the paging enable bit (pg)
    cr0_request.pg = true;

    //create the new cr0 value
    x86_32_cr0_set(&cr0_value , &cr0_request);

    //load the value back to the real register cr0
    _x86_32_cr0_write(&cr0_value);

}

void X86_32_CALL x86_32_disable_paging(void){
    _x86_32_cr0       cr0_value  ;
    struct x86_32_cr0 cr0_request;

    //read the cr0 value
    _x86_32_cr0_read(&cr0_value);

    //write the value to a request cr0 structure
    x86_32_cr0_get(&cr0_request , &cr0_value);

    //change the paging enable bit (pg)
    cr0_request.pg = false;

    //create the new cr0 value
    x86_32_cr0_set(&cr0_value , &cr0_request);

    //load the value back to the real register cr0
    _x86_32_cr0_write(&cr0_value);

}