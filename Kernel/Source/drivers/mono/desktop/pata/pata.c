#include "pata.h"
#include "pata_registers.h"
#include <print.h>


driver pata_driver = {
    .init   = pata_init     ,
    .fini   = pata_fini     ,
    .probe  = pata_probe    ,
    .type   = BLOCK_DRIVER  ,
    .name   = "PATA DRIVER"
};


pata_diskx* current_primary_drive = NULL;
pata_diskx* current_secondary_drive = NULL;


errno pata_init(void){


    return FLUSHOS_EGOOD;

}


errno pata_fini(void){
    return FLUSHOS_EGOOD;
}




errno pata_probe(void){

    pata_detect_disks();

    if (
            !primary_master_disk.valid
        &&  !primary_slave_disk.valid
        &&  !secondary_master_disk.valid
        &&  !secondary_slave_disk.valid
    ){
        print("No valid disk !!!");
        return FLUSHOS_EINVLD;
    }

    return FLUSHOS_EGOOD;

}
