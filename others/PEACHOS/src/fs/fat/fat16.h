#ifndef FAT16_H
#define FAT16_H
 
    #include <status.h>
    #include <def.h>
    #include <config.h>
    #include <fs/file.h>

    #define PEACHOS_FAT16_SIGNATURE     0x29
    #define PEACHOS_FAT16_ENTRY_SIZE    0x02
    #define PEACHOS_FAT16_BAD_SECTORS   0x0FF7
    #define PEACHOS_FAT16_UNUSED        0x00

    //fat16 attribute bit mask
    #define FAT16_FILE_READ_ONLY    0x01
    #define FAT16_FILE_HIDDEN       0x02
    #define FAT16_FILE_SYSTEM       0x04
    #define FAT16_FILE_VOLUME_LABEL 0x08
    #define FAT16_FILE_SUBDIRECTORY 0x10
    #define FAT16_FILE_ARCHIVED     0x20
    #define FAT16_FILE_DEVICE       0x40
    #define FAT16_FILE_RESERVED     0x80

    typedef uint32_t fat16_item_type;
    #define FAT16_ITEM_TYPE_DIRECTORY   ((fat16_item_type)0)
    #define FAT16_ITEM_TYPE_FILE        ((fat16_item_type)1)

    struct fat16_header_extended{
        uint8_t     drive_number;
        uint8_t     win_nt_bit;
        uint8_t     signature;
        uint32_t    volume_id;
        uint8_t     volume_id_string[11];
        uint8_t     system_id_string[8];
    } __attribute__((packed));

    struct fat16_header{
        uint8_t short_jump_instructiom[3];
        
    }

    extern struct file_system fat16;
    struct file_system* fat16_init(void);
    int fat16_resolve(struct disk* disk);
    void* fat16_open(struct disk* disk,struct path_part* part , FILE_MODE mode);

#endif 