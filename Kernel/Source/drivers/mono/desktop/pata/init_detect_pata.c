#include "pata.h"
#include "pata_registers.h"
#include "pata_special_cmds.h"
#include <print.h>


pata_diskx primary_master_disk;
pata_diskx primary_slave_disk;
pata_diskx secondary_master_disk;
pata_diskx secondary_slave_disk;





void init_pata_drive(
    uint16_t io_base , uint16_t ctrl_base , 
    uint16_t SELECT_DRIVE , pata_diskx* pdisk ){

    // disable interrupts -- first driver focus on be polling driver 
    uint8_t control_device_value = NIEN;
    outb(control_device_value , ctrl_base + DEVICE_CONTROL);
    // check if ready or any error exist's (let errors for later)
    errno error = FLUSHOS_EGOOD;
    error = ata_wait_not_busy(io_base , ctrl_base);
    if (error != FLUSHOS_EGOOD){
        pdisk->valid = false;
        return ;
    }

    error = disk_create(&pdisk->_module , pdisk , pdisk->_attrs);
    if (error != FLUSHOS_EGOOD)
    {
        // theoreticly a panic here 
        return ;
    }
}


void detect_pata_drive(uint16_t io_base , uint16_t ctrl_base , uint16_t SELECT_DRIVE , pata_diskx* pdisk){
    
    outb( SELECT_DRIVE , io_base + DRIVE_REGISTER);
    ata_delay_400ns(ctrl_base);
    
    outb(0 , io_base + SECTOR_COUNT_REG);
    outb(0 , io_base + LBA_LOW_REGISTER);
    outb(0 , io_base + LBA_MID_REGISTER);
    outb(0 , io_base + LBA_HIG_REGISTER);

    ata_send_command(io_base , ctrl_base , CMD_IDENTIFY_DEVICE);
   

    // now read status reg
    uint8_t status = 0xFF;
    errno error = FLUSHOS_EGOOD;
    // check status if is zero . If yes 
    // then this is not ata spec drive 
    // and should stop .
    inb(&status , io_base + STATUS_REGISTER);
    if (status == 0){
        goto not_detected;
    }
    // if status is zero then 
    // wait unitl bsy is clear
    error = ata_wait_not_busy(io_base , ctrl_base);
    if (error != FLUSHOS_EGOOD){
        goto not_detected;
    }
        
    // read lba l/h/m and sector count registers 
    // if not zero disk is not pata (maybe CD/DVD)
    // but they will not supported now
    uint8_t lba_l , lba_h , lba_m , sec_count_reg ;
    inb( &sec_count_reg , io_base + SECTOR_COUNT_REG);
    inb( &lba_l , io_base + LBA_LOW_REGISTER);
    inb( &lba_m , io_base + LBA_MID_REGISTER);
    inb( &lba_h , io_base + LBA_HIG_REGISTER);
    if ( sec_count_reg || lba_h || lba_m || lba_l || (status & STATUS_ERROR)){
        goto not_detected;
    }
    
    // continue polling status until is data ready
    error = ata_wait_drq(io_base , ctrl_base);
    if (error != FLUSHOS_EGOOD){
        goto not_detected;
    }

    // now read 512 bytes of data haved all important info 
    uint16_t count = 0 ;
    uint16_t identify_buffer[256];
    while(count < 256){

        inw(&identify_buffer[count] , io_base + DATA_REGISTER);

        count++;
    }

    // find if has 28 or 48 bit lba , sectors count  and sector lenght
    uint16_t has_lba48 = identify_buffer[IDENTIFY_WORD_LBA48] & IDENTIFY_LBA48;
    uint32_t sec_count_lba28 =
    ((uint32_t)identify_buffer[60]) |
    ((uint32_t)identify_buffer[61] << 16);
    uint64_t sec_count_lba48 =
    ((uint64_t)identify_buffer[100]) |
    ((uint64_t)identify_buffer[101] << 16) |
    ((uint64_t)identify_buffer[102] << 32) |
    ((uint64_t)identify_buffer[103] << 48);
    uint64_t sec_count = (has_lba48) ? sec_count_lba48 : (uint64_t)sec_count_lba28;
    uint32_t sector_length = ata_get_logical_sector_size(identify_buffer);

    // now we assign the correct disk attributes
    pdisk->valid = true;
    pdisk->_attrs.lba_base = 0;
    pdisk->_attrs.sector_count = sec_count;
    pdisk->_attrs.sector_length = sector_length;
    pdisk->_attrs.zero = 0;
    pdisk->pata_lba28 = has_lba48 ? false : true;
    pdisk->ata_io = io_base;
    pdisk->ata_buss = ctrl_base;
    pdisk->ata_drive = SELECT_DRIVE;
    pdisk->lba28_last_high = 0x00;
    
    if      ( (io_base == PRIMARY_ATA_IO_BASE) && (SELECT_DRIVE == SELECT_MASTER_DRIVE) )
        pdisk->_disk = PATA_PRIMARY_MASTER;
    else if ( (io_base == PRIMARY_ATA_IO_BASE) && (SELECT_DRIVE == SELECT_SLAVE_DRIVE) )
        pdisk->_disk = PATA_PRIMARY_SLAVE;
    else if ( (io_base == SECONDARY_ATA_IO_BASE) && (SELECT_DRIVE == SELECT_MASTER_DRIVE) )
        pdisk->_disk = PATA_SECONDARY_MASTER;
    else if ( (io_base == SECONDARY_ATA_IO_BASE) && (SELECT_DRIVE == SELECT_SLAVE_DRIVE) )
        pdisk->_disk = PATA_SECONDARY_SLAVE;
    else 
        pdisk->_disk = PATA_PRIMARY_MASTER;
        
    if (has_lba48 == 0){
        pdisk->_module.read = pata_read_lba28;
        pdisk->_module.write = pata_write_lba28;
    }
    else {
        pdisk->_module.read = pata_read_lba48;
        pdisk->_module.write = pata_write_lba48;
    }
    

    return ;

    not_detected:
        
        pdisk->valid = false;
        return;
}

void detect_primary_master_disk(void){
    uint16_t io_base = PRIMARY_ATA_IO_BASE;
    uint16_t ctrl_base = PRIMARY_ATA_CONTROL_BASE;
    uint16_t SELECT_DRIVE = SELECT_MASTER_DRIVE;
    detect_pata_drive(io_base , ctrl_base , SELECT_DRIVE , &primary_master_disk);
    if (primary_master_disk.valid == false){
        print("PATA PRIMARY MASTER DRIVE : Not exists\n");
        return ;
    }
    current_primary_drive = &primary_master_disk;
    
    init_pata_drive(io_base , ctrl_base , SELECT_DRIVE , &primary_master_disk );

    
    
}

void detect_primary_slave_disk(void){
    uint16_t ATA_IO = PRIMARY_ATA_IO_BASE;
    uint16_t ATA_BUSS = PRIMARY_ATA_CONTROL_BASE;
    uint16_t SELECT_DRIVE = SELECT_SLAVE_DRIVE;

    detect_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &primary_slave_disk);
    if (primary_slave_disk.valid == false){
        return ;
    }
    current_primary_drive = &primary_slave_disk;
    
    init_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &primary_slave_disk);


    
}

void detect_secondary_master_disk(void){
    uint16_t ATA_IO = SECONDARY_ATA_IO_BASE;
    uint16_t ATA_BUSS = SECONDARY_ATA_IO_CONTROL_BASE;
    uint16_t SELECT_DRIVE = SELECT_MASTER_DRIVE;
    detect_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &secondary_master_disk);
    if (secondary_master_disk.valid == false){
        print("PATA SECONDARY MASTER DRIVE : Not exists\n");
        return ;
    }
    current_secondary_drive = &secondary_master_disk;
    

    init_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &secondary_master_disk);


    
}

void detect_secondary_slave_disk(void){
    uint16_t ATA_IO = SECONDARY_ATA_IO_BASE;
    uint16_t ATA_BUSS = SECONDARY_ATA_IO_CONTROL_BASE;
    uint16_t SELECT_DRIVE = SELECT_SLAVE_DRIVE;
    detect_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &secondary_slave_disk);
    if (secondary_slave_disk.valid == false){
        print("PATA SECONDARY SLAVE DRIVE : Not exists\n");
        return ;
    }
    current_secondary_drive = &secondary_slave_disk;


    init_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &secondary_slave_disk);


    
}


bool pata_detect_disks(void){
    detect_secondary_master_disk();
    detect_secondary_slave_disk();
    detect_primary_slave_disk();
    detect_primary_master_disk();


    

    return true;

}

