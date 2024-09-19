#include "pgcr.h"

void X86_32_CALL x86_32_paging_cache_reload(void){
    _x86_32_cr0 cpu_val;
    struct x86_32_cr0 human_val;
    
    //check if paging is used so not exception is generated
    _x86_32_cr0_read(&cpu_val);
    x86_32_cr0_get(&human_val , &cpu_val);
    if (human_val.pg == false)
        return; // no entry in the tlb is sure , if paging is disable

    //with enable , disable and back enable paging the tlb is cleared 
    //and ready for the nexts tlb entries
    x86_32_disable_paging();
    x86_32_enable_paging();

        
}