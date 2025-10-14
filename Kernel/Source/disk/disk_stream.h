#ifndef __FLUSHOS_DISK_STREAM_H__
#define __FLUSHOS_DISK_STREAM_H__

    #include "disk.h"
    struct disk_stream{
        uint32_t pos; // the position in bytes in the current disk driver (give as sector + offset in it)
        struct disk* disk; // the disk representation of the real hardware device :)
    };

    enum seek_type{
        SEEK_STR , 
        SEEK_END ,
        SEEK_CUR
    };

    struct disk_stream* disk_stream_create(int disk_no );
    errno disk_stream_seek(struct disk_stream* stream , enum seek_type type , uint64_t pos);
    errno disk_stream_read(struct disk_stream* stream , void* buffer , size_t size);
    void disk_stream_destroy(struct disk_stream* stream);
#endif 