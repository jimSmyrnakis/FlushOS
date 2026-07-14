#ifndef __FLUSHOS_FAT16_STRUCTS_H__
#define __FLUSHOS_FAT16_STRUCTS_H__

    #include <stdint.h>
    #include <stddef.h>
    #include <disk/disk_stream.h>

    struct fat16_ebpb{ // The extended bios parameter block system struct
        uint8_t drive_number; // not used , but for simple bios on 
        //x86 it represents the drive number resines in dx register when 
        //first bios load your bootloader
        uint8_t win_nt_bit; // 0 (reseved) don't care is windows specific
        uint8_t signature; // 0x29 , the only think i can check for FAT16 existance check (1/millions to have in corrupt disk or other formated fs disk)
        uint32_t volume_id; // don't care
        uint8_t volume_id_string[11]; // not that mutch 
        uint8_t system_id_string[8]; // This says FAT16 , FAT12 , FAT32 , NFTS etc

    }__attribute__((packed));
    // this struct is right after bpb system struct

    struct fat16_bpb{ // the bios parameter block system struct
        uint8_t short_jmp_ins[3];
        uint8_t oem_identifier[8]; // name of the os , don't care too
        uint16_t bytes_per_sector; // defined by the disk struct 
        uint8_t sectors_per_cluster; // something default , something like 4-8 (or define at run time based on a cluster size) 
        uint16_t reserved_sectors; // this will have the number of sectors gviven to our kernel binnary
        uint8_t fat_copies; // we may support a backup 
        uint16_t root_dir_entries; // let them be 64 , 128
        uint16_t number_of_sectors; // all total sectors on the disk / partition , we may use a default one or ask the disk
        uint8_t media_type; // is not in any use any more , fether this informations will came only by the disk driver 
        //not bios or any other than the hardware it self.
        uint16_t sectors_per_fat; // the size in sectors of each fat16 struct
        uint16_t sectors_per_track; // we use lba , but still not good to trust the bios  
        uint16_t number_of_heads; // same as the above
        uint32_t hidden_sectors; // don't care , i will not support that right now 
        uint32_t sectors_big; // if number_of_sectors is zero means that this field express the actual size because of the disk total capacity
    }__attribute__((packed));
    // this struct is on the start of the disk (partitioned or not) - 0x7c00

    struct fat16_header{ // packed all these to one header struct
        struct fat16_bpb    bios_parameter_block;
        struct fat16_ebpb   extended_bios_parameter_block;

    }__attribute__((packed));

    // Note !!! The File Allocation Table 16 bit , is just a cluster used as an 
    // array with 16 bit values , each indicates if the cluster 
    // (after bpb,ebpb,boot,FAT1,FAT2,beggining) is allocated (not 0x0000) and if is 
    // eof (0xFFF8-0xFFFF) or there is a next one . An examble :
    // cluster 0 (beggining + 0) => 0x0003
    // cluster 1 (beggining + 1) => 0x0000
    // cluster 2 (beggining + 2) => 0xFFFF
    // cluster 3 (beggining + 3) => 0x0002
    // ...
    // This means that cluster 0 , cluster 3 , cluster 2 are in this turn and together
    // they made the total bytes of the file and cluster that is in. The cluster 1 is 
    // free for allocation if other file needs to expand or a new file/directory is created .


    
    struct fat16_directory_item 
    { 
        // this struct is used for the discription of a file/directory/other
        // and is the data that resins inside each data cluster of a directory
        uint8_t filename[8]; 
        uint8_t ext[3];
        uint8_t attribute;
        uint8_t reserved;
        uint8_t creation_time_tenths_of_a_sec;
        uint16_t creation_time;
        uint16_t creation_date;
        uint16_t last_access;
        uint16_t high_16_bits_first_cluster;
        uint16_t last_mod_time;
        uint16_t last_mod_date;
        uint16_t low_16_bits_first_cluster;
        uint32_t filesize;
    } __attribute__((packed));

    // definitions of the attribute field on the above system struct
    #define FAT16_ATTRIBUTE_READ_ONLY   ((uint8_t)0x01) // is it read only file/directory ?
    #define FAT16_ATTRIBUTE_HIDDEN      ((uint8_t)0x02) // is it a hidden file/directory ?
    #define FAT16_ATTRIBUTE_SYSTEM      ((uint8_t)0x04) // is it a special file/directory for the system that must remain untouch ? 
    #define FAT16_ATTRIBUTE_VOLUME_ID   ((uint8_t)0x08) // is a valume special cluster , not a file / directory
    #define FAT16_ATTRIBUTE_DIRECTORY   ((uint8_t)0x10) // is the item a directory
    #define FAT16_ATTRIBUTE_ARCHIVE     ((uint8_t)0x20) // this will not used yet


    // Everything after here is for us and the sake of simplification . O

    struct fat16_directory{ // this will be used for simplifing things for directories
        // this struct will be used when reading directory data clusters and filled with
        // all information need it.
        struct fat16_directory_item* directory_items; // all items in the directory
        uint32_t count; // items count of a directory 
        uint32_t first_sector; // first sector and last for the directory clusters 
        uint32_t last_sector; // these will make easier to find all sectors caculated
        // for the root directory , there is not mutch of a use for sub-directories 
        // as they clusters may splatter all around the disk .

    };

    // these are used from us for fast accessed info
    typedef uint32_t fat16_file_type; 
    #define FAT16_FILE_TYPE_DIRECTORY   0x00000001
    #define FAT16_FILE_TYPE_SIMPLE_FILE 0x00000000

    struct fat16_item{ // this will be used maynly for open files and will be filled with
        // all info needed from fopen of this file system
        union {
            struct fat16_directory directory; // for a directory 
            struct fat16_directory_item file; // for a simple file that the end path_part represents
        };
        fat16_file_type type;
    };

    typedef uint16_t fat16_entry;

    struct fat16_private{ // this will be filled and used by our fat16 file system 
        // and is important as is the data that the virtual file system will give to us
        // each time , these are known only to us and vfs give this as void* pointer
        struct fat16_header header; // the header
        struct fat16_directory root_directory; // the root directory (this is not a visible one)

        fat16_entry* FAT1;
        bool hasFAT2;
        fat16_entry* FAT2; // optional
        struct disk_stream* data_stream; // used only for file/directory data
        struct disk_stream* root_stream; // used for the root directory , just as shortcut
        
    };


    struct fat16_descriptor{ // this has everything we need for handling new requests for the same file/directory
        struct fat16_item* item; // the item
        int pos; // the offset in bytes inside the data cluster ==> sectors that the file is
    };



#endif 