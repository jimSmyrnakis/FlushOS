#include "stream.h"
#include <kheap.h>

struct disk_stream* disk_stream_new(uint16_t disk_id){
    struct disk* disk = disk_get(disk_id);
    if (disk == KNULL)
        return KNULL;
    
    struct disk_stream* st = (struct disk_stream*)kzalloc(sizeof(struct disk_stream));
    if (st == KNULL){
        return KNULL;
    }

    st->pos = 0;
    st->disk = disk;

    return st;
}

int disk_stream_seek(struct disk_stream* stream , uint32_t pos){
    error_stat = KERNEL_OK;
    
    stream->pos = pos;

    return error_stat;
}

int disk_stream_read(struct disk_stream* stream , uint32_t count , void* buffer ){
    error_stat = KERNEL_OK;

    uint32_t sector_base = stream->pos/(PEACHOS_SECTOR_SIZE);
    uint16_t sector_offs = stream->pos%(PEACHOS_SECTOR_SIZE);
    uint8_t sector_buffer[PEACHOS_SECTOR_SIZE];
    
    //read the first sector
    int res = disk_read_blocks(stream->disk , sector_base , 1 , sector_buffer);
    if (res != KERNEL_OK)
    {
        return res;
    }

    // read the first sector (relative to the base)
    uint16_t total_to_read = (count + sector_offs) > PEACHOS_SECTOR_SIZE ? ( PEACHOS_SECTOR_SIZE - sector_offs) : count;
    uint16_t i ;
    for ( i = 0; i < total_to_read ; i++){
        ((uint8_t*)buffer)[i] = sector_buffer[i + sector_offs];
    }

    // update the stream
    stream->pos += total_to_read;
    if ((count - total_to_read) != 0){
        // call him self for the next sector
        return disk_stream_read(stream , count - total_to_read , ((uint8_t*)buffer) + total_to_read);
    }
    // this solution is simple and easy to implement but carefull for stack overflow



    return error_stat;
}

void disk_stream_close(struct disk_stream* stream){
    kfree(stream);
}

