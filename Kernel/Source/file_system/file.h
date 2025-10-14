#ifndef __FLUSHOS_FILE_H__
#define __FLUSHOS_FILE_H__

    #include "../disk/disk.h"
    #include "path_parser.h"
    #include "../errno.h"
    #include <stdint.h>
    #include <stddef.h>
    #include "../common_defs.h"
    
    // The open file resolve function type (signature)
    typedef void* (*file_system_open)(struct disk* , struct path_part * , file_mode bit_mode);
    // The resolve function is responsible for checking if the file system in the specific
    // disk has the file system (like FAT 16 , FAT 32 , NFAT FAT 12 , EXT2 etc) that the file
    // system that is responsible ()
    typedef errno (*file_system_resolve)(struct disk* );    

    struct file_system
    {
        file_system_open        open;
        file_system_resolve     resolve;

        char                    name[64];
        
    };

    struct file_descriptor
    {
        uint32_t index;
        struct file_system* fsystem;
        void* private_data; // open function return pointer 
        struct disk* disk;
    };

    void file_system_init(void);
    errno                 fopen       (const char* filename , file_mode mode);
    struct file_system* fs_resolve  (struct disk* disk);

    void file_system_insert(struct file_system* fs);


#endif