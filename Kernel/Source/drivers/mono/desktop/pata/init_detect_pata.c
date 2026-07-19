#include "pata.h"
#include "pata_registers.h"
#include <print.h>


pata_diskx primary_master_disk;
pata_diskx primary_slave_disk;
pata_diskx secondary_master_disk;
pata_diskx secondary_slave_disk;

#define IDENTIFY_LBA48 0x0400 // set if lba48 is supported
#define IDENTIFY_WORD_LBA48 83 
#define IDENTIFY_WORD_LBA28_SEC_COUNT1 60
#define IDENTIFY_WORD_LBA28_SEC_COUNT2 61
#define IDENTIFY_WORD_LBA48_SEC_COUNT1 100
#define IDENTIFY_WORD_LBA48_SEC_COUNT2 101
#define IDENTIFY_WORD_LBA48_SEC_COUNT3 102
#define IDENTIFY_WORD_LBA48_SEC_COUNT4 103

#include <stdint.h>
#include <stdbool.h>


#define IDENTIFY_WORD_LOGICAL_SECTOR_INFO 106
#define IDENTIFY_WORD_LOGICAL_SECTOR_SIZE_LOW 117
#define IDENTIFY_WORD_LOGICAL_SECTOR_SIZE_HIGH 118


#define IDENTIFY_WORD_106_VALID (1 << 14)
#define IDENTIFY_WORD_106_LONG_PHYSICAL (1 << 12)

void ata_delay_400ns(uint16_t ATA_CTRL_BASE ){
    uint8_t status ;

    // wait to be ready 
    for (int i = 0; i < 10 ; i++)
        inb(&status , ATA_CTRL_BASE + ALTERNATE_STATUS);
}

// AI GENERATED - function 
uint32_t ata_get_logical_sector_size(uint16_t* identify)
{
    uint16_t word106 = identify[IDENTIFY_WORD_LOGICAL_SECTOR_INFO];

    /*
        Bit 14 = words 117-118 are valid
    */
    if (!(word106 & IDENTIFY_WORD_106_VALID))
    {
        // ATA default logical sector size
        return 512;
    }


    uint32_t sector_size =
        ((uint32_t)identify[IDENTIFY_WORD_LOGICAL_SECTOR_SIZE_LOW]) |
        ((uint32_t)identify[IDENTIFY_WORD_LOGICAL_SECTOR_SIZE_HIGH] << 16);


    /*
        Safety check
        Logical sector size must be reasonable
    */
    if (sector_size == 0)
        return 512;


    return sector_size;
}

void init_pata_drive(uint16_t ATA_IO , uint16_t ATA_BUSS , uint16_t SELECT_DRIVE , pata_diskx* pdisk){

    // disable interrupts -- first driver focus on be polling driver 
    uint8_t control_device_value = NIEN;
    outb(control_device_value , ATA_BUSS + DEVICE_CONTROL);
    // check if ready or any error exist's (let errors for later)
    uint8_t status = 0;
    inb(&status , ATA_IO | STATUS_REGISTER);
    while (status &  STATUS_DRIVER_BUSY){
        inb(&status , ATA_IO | STATUS_REGISTER);
    }


}


void detect_pata_drive(uint16_t ATA_IO , uint16_t ATA_BUSS , uint16_t SELECT_DRIVE , pata_diskx* pdisk){
    
    outb( SELECT_DRIVE , ATA_IO + DRIVE_REGISTER);
    ata_delay_400ns(ATA_BUSS);
    
    outb(0 , ATA_IO + SECTOR_COUNT_REG);
    outb(0 , ATA_IO + LBA_LOW_REGISTER);
    outb(0 , ATA_IO + LBA_MID_REGISTER);
    outb(0 , ATA_IO + LBA_HIG_REGISTER);
    outb(CMD_IDENTIFY_DEVICE , ATA_IO + COMMAND_REGISTER);

    // now read status reg
    uint8_t status = 0xFF;

    // wait to be ready 
    inb(&status , ATA_IO | STATUS_REGISTER);
    if (status == 0){
        
        goto not_detected;
    }
    // if device exists
    // wait unitl bsy is clear
    inb(&status , ATA_IO | STATUS_REGISTER);
    while (status &  STATUS_DRIVER_BUSY){
        inb(&status , ATA_IO | STATUS_REGISTER);
    }

    // read lba l/h/m and sector count registers 
    // if not zero disk is not pata (maybe CD/DVD)
    // but they will not supported now
    uint8_t lba_l , lba_h , lba_m , sec_count_reg ;
    inb( &sec_count_reg , ATA_IO | SECTOR_COUNT_REG);
    inb( &lba_l , ATA_IO | LBA_LOW_REGISTER);
    inb( &lba_m , ATA_IO | LBA_MID_REGISTER);
    inb( &lba_h , ATA_IO | LBA_HIG_REGISTER);
    if ( sec_count_reg || lba_h || lba_m || lba_l || (status & STATUS_ERROR)){
        goto not_detected;
    }
    
    // continue polling status until is data ready
    inb(&status , ATA_IO | STATUS_REGISTER);
    while (!(status &  STATUS_PIO_READY)){
        inb(&status , ATA_IO | STATUS_REGISTER);
    }

    // now read 512 bytes of data haved all important info 
    uint16_t count = 0 ;
    uint16_t identify_buffer[256];
    while(count < 256){

        inw(&identify_buffer[count] , ATA_IO | DATA_REGISTER);

        count++;
    }

    // find if has 28 or 48 bit lba , sectors count  and sector lenght
    uint16_t has_lba48 = 0 ; //identify_buffer[IDENTIFY_WORD_LBA48] & IDENTIFY_LBA48;
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
    pdisk->ata_io = ATA_IO;
    pdisk->ata_buss = ATA_BUSS;
    pdisk->ata_drive = SELECT_DRIVE;
    pdisk->lba28_last_high = 0x00;

    if      ( (ATA_IO == PRIMARY_CONTROL_IO) && (SELECT_DRIVE == SELECT_MASTER_DRIVE) )
        pdisk->_disk = PATA_PRIMARY_MASTER;
    else if ( (ATA_IO == PRIMARY_CONTROL_IO) && (SELECT_DRIVE == SELECT_SLAVE_DRIVE) )
        pdisk->_disk = PATA_PRIMARY_SLAVE;
    else if ( (ATA_IO == SECONDARY_CONTROL_IO) && (SELECT_DRIVE == SELECT_MASTER_DRIVE) )
        pdisk->_disk = PATA_SECONDARY_MASTER;
    else if ( (ATA_IO == SECONDARY_CONTROL_IO) && (SELECT_DRIVE == SELECT_SLAVE_DRIVE) )
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
    uint16_t ATA_IO = PRIMARY_CONTROL_IO;
    uint16_t ATA_BUSS = PRIMARY_CONTROL_BUSS;
    uint16_t SELECT_DRIVE = SELECT_MASTER_DRIVE;
    detect_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &primary_master_disk);
    if (primary_master_disk.valid == false){
        print("PATA PRIMARY MASTER DRIVE : Not exists\n");
        return ;
    }
    current_primary_drive = &primary_master_disk;
    
    init_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &primary_master_disk);

    disk_create(
        &primary_master_disk._module , 
        &primary_master_disk , 
        primary_master_disk._attrs);

    print("PATA PRIMARY MASTER DRIVE :\n");
    print("capacity : ");
    uintptr_t cap =  primary_master_disk._attrs.sector_count * primary_master_disk._attrs.sector_length;
    printHex((void*)cap);
    print("\n");
    print("lba base : ");
    uintptr_t lbb = primary_master_disk._attrs.lba_base;
    printHex((void*)lbb);
    print("\n");
    if (primary_master_disk.pata_lba28)
        print("lba28");
    else 
        print("lba48");
    print("\n");
    print("sector len : ");
    printHex((void*)primary_master_disk._attrs.sector_length);
    print("\n");
    
}

void detect_primary_slave_disk(void){
    uint16_t ATA_IO = PRIMARY_CONTROL_IO;
    uint16_t ATA_BUSS = PRIMARY_CONTROL_BUSS;
    uint16_t SELECT_DRIVE = SELECT_SLAVE_DRIVE;
    detect_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &primary_slave_disk);
    if (primary_slave_disk.valid == false){
        print("PATA PRIMARY SLAVE DRIVE : Not exists\n");
        return ;
    }
    current_primary_drive = &primary_slave_disk;
    
    init_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &primary_slave_disk);

    disk_create(
        &primary_slave_disk._module , 
        &primary_slave_disk , 
        primary_slave_disk._attrs);

    print("PATA PRIMARY SLAVE DRIVE :\n");
    print("capacity : ");
    uintptr_t cap =  primary_slave_disk._attrs.sector_count * primary_slave_disk._attrs.sector_length;
    printHex((void*)cap);
    print("\n");
    print("lba base : ");
    uintptr_t lbb = primary_slave_disk._attrs.lba_base;
    printHex((void*)lbb);
    print("\n");
    if (primary_slave_disk.pata_lba28)
        print("lba28");
    else 
        print("lba48");
    print("\n");
    print("sector len : ");
    printHex((void*)primary_slave_disk._attrs.sector_length);
    print("\n");
}

void detect_secondary_master_disk(void){
    uint16_t ATA_IO = SECONDARY_CONTROL_IO;
    uint16_t ATA_BUSS = SECONDARY_CONTROL_BUSS;
    uint16_t SELECT_DRIVE = SELECT_MASTER_DRIVE;
    detect_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &secondary_master_disk);
    if (secondary_master_disk.valid == false){
        print("PATA SECONDARY MASTER DRIVE : Not exists\n");
        return ;
    }
    current_secondary_drive = &secondary_master_disk;
    

    init_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &secondary_master_disk);

    disk_create(
        &secondary_master_disk._module , 
        &secondary_master_disk , 
        secondary_master_disk._attrs);

    print("PATA SECONDARY MASTER DRIVE :\n");
    print("capacity : ");
    uintptr_t cap =  secondary_master_disk._attrs.sector_count * secondary_master_disk._attrs.sector_length;
    printHex((void*)cap);
    print("\n");
    print("lba base : ");
    uintptr_t lbb = secondary_master_disk._attrs.lba_base;
    printHex((void*)lbb);
    print("\n");
    if (secondary_master_disk.pata_lba28)
        print("lba28");
    else 
        print("lba48");
    print("\n");
    print("sector len : ");
    printHex((void*)secondary_master_disk._attrs.sector_length);
    print("\n");
}

void detect_secondary_slave_disk(void){
    uint16_t ATA_IO = SECONDARY_CONTROL_IO;
    uint16_t ATA_BUSS = SECONDARY_CONTROL_BUSS;
    uint16_t SELECT_DRIVE = SELECT_SLAVE_DRIVE;
    detect_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &secondary_slave_disk);
    if (secondary_slave_disk.valid == false){
        print("PATA SECONDARY SLAVE DRIVE : Not exists\n");
        return ;
    }
    current_secondary_drive = &secondary_slave_disk;


    init_pata_drive(ATA_IO , ATA_BUSS , SELECT_DRIVE , &secondary_slave_disk);

    disk_create(
        &secondary_slave_disk._module , 
        &secondary_slave_disk , 
        secondary_slave_disk._attrs);

    print("PATA SECONDARY SLAVE DRIVE :\n");
    print("capacity : ");
    uintptr_t cap =  secondary_slave_disk._attrs.sector_count * secondary_slave_disk._attrs.sector_length;
    printHex((void*)cap);
    print("\n");
    print("lba base : ");
    uintptr_t lbb = secondary_slave_disk._attrs.lba_base;
    printHex((void*)lbb);
    print("\n");
    if (secondary_slave_disk.pata_lba28)
        print("lba28");
    else 
        print("lba48");
    print("\n");
    print("sector len : ");
    printHex((void*)secondary_slave_disk._attrs.sector_length);
    print("\n");
}


bool pata_detect_disks(void){
    detect_secondary_master_disk();
    detect_secondary_slave_disk();
    // do last the primary master , for not needed to switch on it
    // at the next read/write ops
    detect_primary_slave_disk();
    detect_primary_master_disk();


    

    return true;

}