#ifndef FILE_H
#define FILE_H

    #include <status.h>
    #include <def.h>
    #include <config.h>
    #include <kheap.h>
    #include "pparser.h"

    


    typedef uint32_t FILE_SEEK_MODE;
    enum{
        SEEK_SET,
        SEEK_CUR,
        SEEK_END
    };

    typedef uint32_t FILE_MODE;
    enum{
        FILE_MODE_READ,
        FILE_MODE_WRITE,
        FILE_MODE_APPEND,
        FILE_MODE_INVALID
    };

    struct disk;
    
    typedef void*(*FS_OPEN_FUNCTION)(struct disk* disk,struct path_part* part , FILE_MODE mode );
    typedef int (*FS_RESOLVE_FUNCTION)(struct disk* disk);
    //return's 0 if the specific file system can read this type of storage physical or logical device
    //as it's file system header type

    struct file_system{
        char name[20];
        FS_OPEN_FUNCTION    open;
        FS_RESOLVE_FUNCTION resolve;
    };

    struct file_descriptor{
        int index;
        struct file_system* file_system;
        struct disk* disk;
        void* private_metadata;
    };

    void fs_init();
    int fopen(const char* filename , const char* mode);
    void fs_insert_file_system(struct file_system* file_system);
    struct file_system* fs_resolve(struct disk* disk);

#endif 