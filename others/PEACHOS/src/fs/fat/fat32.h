#ifndef FAT32_H
#define FAT32_H

    #include <status.h>
    #include <def.h>
    #include <config.h>
    #include <fs/file.h>
    
    struct file_system* fat32_init(void);
    int fat32_resolve(struct disk* disk);
    void* fat32_open(struct disk* disk,struct path_part* part , FILE_MODE mode);

#endif 