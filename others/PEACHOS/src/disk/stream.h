#ifndef STREAM_H 
#define STREAM_H

    #include <status.h>
    #include <config.h>
    #include <def.h>
    #include "disk.h"

    struct disk_stream{
        uint32_t pos; // what position we are curently seeking from
        struct disk* disk; // the disk we using
        
    };
    struct disk_stream* disk_stream_new(uint16_t disk_id);

    int disk_stream_seek(struct disk_stream* stream , uint32_t pos);

    int disk_stream_read(struct disk_stream* stream , uint32_t count , void* buffer );

    void disk_stream_close(struct disk_stream* stream);
    
#endif 