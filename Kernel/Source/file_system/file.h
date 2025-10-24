#ifndef __FLUSHOS_FILE_H__
#define __FLUSHOS_FILE_H__

    #include "../disk/disk.h"
    #include "path_parser.h"
    #include "../errno.h"
    #include <stdint-gcc.h>
    #include <stddef.h>
    #include "../common_defs.h"
    #define KERNEL_MAX_FILE_NAME_SIZE 64
    enum {
        FILE_STATUS_READ_ONLY = 0x00000001 
    };
    typedef uint32_t file_status_flags;
    struct file_stat{
        file_status_flags  status;
        char name[KERNEL_MAX_FILE_NAME_SIZE];
        uint32_t size;
        
    };
    // The open file resolve function type (signature)
    // The resolve function is responsible for checking if the file system in the specific
    // disk has the file system (like FAT 16 , FAT 32 , NFAT FAT 12 , EXT2 etc) that the file
    // system that is responsible ()
    typedef errno (*file_system_resolve)(struct disk* );

    typedef void* (*file_system_open)(struct disk* , struct path_part * , file_mode bit_mode);
    typedef errno (*file_system_read)(struct disk* disk, void* private, uint32_t size, uint32_t nmemb, char* out); 
    typedef errno (*file_system_seek)(void* private, int offset, enum seek_mode seek_mode);
    typedef errno (*file_system_stat)(struct disk* disk, void* private , struct file_stat* stat );
    typedef errno (*file_system_close)(void* private);

    struct file_system
    {
        file_system_resolve     resolve;
        file_system_open        open;
        file_system_read        read;
        file_system_seek        seek;
        file_system_stat        stat;
        file_system_close       close;
        char                    name[KERNEL_MAX_FILE_NAME_SIZE];
        
    };

    struct file_descriptor
    {
        uint32_t index;
        struct file_system* fsystem;
        void* private_data; // open function return pointer 
        struct disk* disk;
        file_mode mode;
    };

    

    void file_system_init(void);
    int  fopen(const char* filename , const char* mode);
    struct file_system* fs_resolve  (struct disk* disk);
    errno fread(void* ptr, uint32_t size, uint32_t nmemb, int fd);
    void file_system_insert(struct file_system* fs);
    errno fseek(int fd, int offset, enum seek_mode mode);
    errno fstat(int fd, struct file_stat* stat);
    errno fclose(int fd);
#endif