#ifndef __FLUSHOS_DISK_STREAM_H__
#define __FLUSHOS_DISK_STREAM_H__

    #include "disk.h"
    struct disk_stream{
        uint64_t pos; // the position in bytes in the current disk driver (give as sector + offset in it)
        struct disk* disk; // the disk representation of the real hardware device :)
    };

    enum seek_type{
        SEEK_STR , 
        SEEK_END ,
        SEEK_CUR
    };



#endif 