#ifndef __FLUSHOS_PATA_REGISTERS_H__
#define __FLUSHOS_PATA_REGISTERS_H__

    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>

    // ATA Busses
    #define PRIMARY_CONTROL_IO      0x1F0
    #define PRIMARY_CONTROL_BUSS    0x3F6
    #define SECONDARY_CONTROL_IO    0x170
    #define SECONDARY_CONTROL_BUSS  0x376

    // ATA Drivers Busses enable
    #define MASTER_BUSS 0xE0    // LBA + select master buss device
    #define SLAVE_BUSS  0xF0    // LBA + select slave buss device

    // CONTROL ATA IO REGISTERS
    // ATA Registers
    #define DATA_REGISTER       0x0 // RW (LBA28 - 16 bit , LBA48 - 16 bit)
    #define ERROR_REGISTER      0x1 // R  (LBA28 -  8 bit , LBA48 - 16 bit)
    #define FEATURES_REGISTER   0x1 // W -- not used just reference it
    #define SECTOR_COUNT_REG    0x2 // RW (LBA28 -  8 bit , LBA48 - 16 bit)
    #define LBA_LOW_REGISTER    0x3 // RW (LBA28 -  8 bit , LBA48 - 16 bit)
    #define LBA_MID_REGISTER    0x4 // RW (LBA28 -  8 bit , LBA48 - 16 bit)
    #define LBA_HIG_REGISTER    0x5 // RW (LBA28 -  8 bit , LBA48 - 16 bit)
    #define DRIVE_REGISTER      0x6 // RW (8bit , in lba28 4 higher bit are in lowers bit of this reg)
    #define STATUS_REGISTER     0x7 // R  (8bit)
    #define COMMAND_REGISTER    0x7 // W  (8bit)

    // ATA STATUS REGISTER FLAGS
    #define STATUS_ERROR        0x01    // Is there any error
    #define STATUS_PIO_READY    0x08    // Disk ready to accept pio 
    #define STATUS_DRIVE_FAULT  0x20    // Disk has hardware / firmware fault
    #define STATUS_DRIVE_READY  0x40    // Bit is clear when drive is spun down, or after an error.
    //Set otherwise
    #define STATUS_DRIVER_BUSY  0x80    // Indicates the drive is preparing to send/receive 
    //data (wait for it to clear). In case of 'hang' (it never clears), do a software reset.

    // Driver Register
    #define LBA28_27_24 0x0F 
    #define DRV         0x10
    #define LBA         0x40
    #define SELECT_MASTER_DRIVE 0xA0
    #define SELECT_SLAVE_DRIVE  0xB0
    

    // ERROR REGISTER FLAGS 8 bits
    #define AMNF    0x01	//Address mark not found. -- not used any more ()
    #define TKZNF   0x02    //Track zero not found. -- not used any more (is for callibration)
    #define ABRT	0x04    //Aborted command. 
    #define MCR	    0x08    //Media change request.
    #define IDNF	0x10    //ID not found.
    #define MC	    0x20    //Media changed.
    #define UNC	    0x40    //Uncorrectable data error.
    #define BBK	    0x80    //Bad Block detected.




    // CONTROL ATA BUSS REGISTERS
    #define ALTERNATE_STATUS    0x0     // R
    #define DEVICE_CONTROL      0x0     // W
    #define DRIVE_ADDRESS       0x1     // R

    // ALTERNATE REGISTERS has same flags with status register

    // Device Control Register
    #define NIEN 0x02   // Set this to stop the current device from sending interrupts.
    #define SRST 0x04   // Set, then clear (after 5us), this to do a "Software Reset" 
    //on all ATA drives on a bus, if one is misbehaving.
    #define HOB  0x80   // Set this to read back the High Order Byte of the last LBA48 
    //value sent to an IO port.

    // Drive Address Register
    #define DS0 0x01    // Drive 0 select. Clears when drive 0 selected.
    #define DS1 0x02    // Drive 1 select. Clears when drive 1 selected.
    #define WTG 0x40    // Write gate; goes low while writing to the drive is in progress.

    // Commands 
    #define CMD_READ_LBA28_SECTORS      0x20    // read sectors  
    #define CMD_WRITE_LBA28_SECTORS     0x30    // write sectors
    #define CMD_READ_LBA48_SECTORS      0x24    // read lba 48 bit sectors
    #define CMD_WRITE_LBA48_SECTORS     0x34    // write lba 48 bit sectors
    #define CMD_LBA28_FLUSH_CACHE       0xE7    // flush lba 28 bit sectors
    #define CMD_LBA48_FLUSH_CACHE       0xEA    // flush lba 48 bit sectors
    #define CMD_IDENTIFY_DEVICE         0xEC    // For identify each device buss 
    // and extensions 







    // IDENTIFY

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
#endif 