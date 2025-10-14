#include "disk_stream.h"
#include "../heap/kheap.h"
#include "../std/memory.h"
#include "../errno.h"
#ifndef NULL
#define NULL ((void*)0)
#endif 

struct disk_stream* disk_stream_create(int disk_no ){
    struct disk* disk = disk_get(disk_no);
    if (!disk)
        return NULL;

    struct disk_stream* stream = (struct disk_stream*)kzalloc(sizeof(struct disk_stream));
    if (stream){
        stream->disk = disk;
        stream->pos = 0;
    }

    return stream;
}

errno disk_stream_seek(struct disk_stream* stream , enum seek_type type , uint64_t pos){
    switch (type)
    {
    case SEEK_CUR:
        stream->pos = stream->pos + pos;
        break;
    case SEEK_STR:
        stream->pos = pos;
        break;
    case SEEK_END:
        stream->pos = pos; // for moment nothing , later will needed the total sectors in the disk struct as info 
        break;
    default:
        break;
    }

    return FLUSHOS_EGOOD;
}

errno disk_stream_read(struct disk_stream* stream , void* buffer , size_t size){
    if (!stream || !size || !buffer)
        return FLUSHOS_EBADARG;
    
    struct disk* disk = stream->disk;
    errno res = FLUSHOS_EGOOD;
    // we have to find the total sectors this number of 
    // bytes (size) and current pos 
    uint32_t sector_size = stream->disk->sector_size;
    uint32_t first_sector = stream->pos / sector_size; // tart from this sector
    uint32_t offset = stream->pos % sector_size; // and this byte in this sector
    
    
    uint8_t* temp_sector_data =  (uint8_t*)kzalloc(sector_size);
    if (!temp_sector_data){
        res = FLUSHOS_ENOMEM;
        goto out;
    }

    uint32_t curr_sector = first_sector;
    uint32_t curr_size = size;
    uint32_t curr_offset = offset;
    uint32_t sum_rsize = 0;
    while(curr_size != 0){
        res = disk_read_sector(disk , curr_sector , 1 , temp_sector_data);
        if (res != FLUSHOS_EGOOD)
            goto out;
        size_t rsize = (curr_size > sector_size) ? (sector_size - curr_offset) : curr_size;
        memcpy(buffer + sum_rsize, temp_sector_data + curr_offset , rsize);
        curr_size -= rsize;
        sum_rsize += rsize;
        curr_sector++;
        curr_offset = 0; // after the first iteration we dont need it any more 
        // but still this way the code is compatible with reading the first sector
        // right.
    }
    
out:
    kfree(temp_sector_data);
    return res;
} 

void disk_stream_destroy(struct disk_stream* stream){
    kfree(stream);

}


