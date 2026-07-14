#ifndef __FLUSHOS_FAT16_H__
#define __FLUSHOS_FAT16_H__

    #include <stdint-gcc.h>
    #include <stddef.h>
    #include <stdbool.h>
    #include <common_defs.h>
    #include <disk/disk.h>
    #include <file_system/file.h>
    #include "fat16_structs.h"
    #include <heap/kheap.h>
    #include <std/memory.h>
    #include <std/string.h>
    
    extern struct file_system fat16_fs;

    // The open file resolve function type (signature)
    void* fat16_open(struct disk* , struct path_part * , file_mode bit_mode);
   
    errno fat16_resolve(struct disk* disk);   
    
        
    errno fat16_read(struct disk* disk, void* private, uint32_t size, uint32_t nmemb, char* out);
    errno fat16_seek(void* private, int offset, enum seek_mode seek_mode);
    errno fat16_stat(struct disk* disk, void* private , struct file_stat* stat);
    errno fat16_close(void* private );
    struct file_system* fat16_init(void);

#endif 