#include "pata.h"
#include <print.h>
#include "pata_registers.h"
#include "pata_special_cmds.h"

errno pata_switch_drive(pata_diskx* pdisk , uint8_t lba27_24 ){
    uint16_t ata_io_base = pdisk->ata_io;
    uint16_t ata_ctrl_base = pdisk->ata_buss;
    uint16_t ata_drive = pdisk->ata_drive;
    pata_diskx** current = &current_primary_drive;
    if (ata_io_base == SECONDARY_ATA_IO_BASE)
        current = &current_secondary_drive;

    /*if ( 
        ((*current)->ata_drive == pdisk->ata_drive) && 
        (
            ((pdisk->lba28_last_high == lba27_24) ) || 
            (pdisk->pata_lba28 == false) 
        ) 
    )
        return FLUSHOS_EGOOD;*/
    
    uint8_t drive_sel = pdisk->ata_drive | LBA | 0xA0;
    
    if (pdisk->pata_lba28 == true){
        drive_sel |= ( lba27_24 & 0x0F);
    }
    // select drive
    outb( drive_sel , ata_io_base + DRIVE_REGISTER);

    


    // delay 
    ata_delay_400ns(ata_ctrl_base);

    
    errno error = ata_wait_ready(ata_io_base, ata_ctrl_base); // RDY & BSY check

    if (error != FLUSHOS_EGOOD)
        return error;

    (*current) = pdisk;

    if (pdisk->pata_lba28 == true)
        pdisk->lba28_last_high = lba27_24;

    
    return error;
}