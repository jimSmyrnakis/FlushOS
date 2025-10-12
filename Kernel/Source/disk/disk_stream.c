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
    return FLUSHOS_ENIMPL;
    uint32_t sector_size = stream->disk->sector_size;
    uint32_t sector = stream->pos / sector_size;
    uint32_t offset = stream->pos % sector_size;
    uint64_t total_sectors = size / sector_size;
    uint64_t extra_bytes = (offset + (size % sector_size));
    total_sectors += extra_bytes / sector_size;
    uint8_t* sector_buffer = (uint8_t*)kzalloc(sector_size);
    if (!sector_buffer) return FLUSHOS_ENOMEM;
    uint8_t* bu8 = (uint8_t*)buffer;

    errno res = disk_read_sector(stream->disk , sector , 1 , sector_buffer);
    if (res != FLUSHOS_EGOOD){
        kfree(sector_buffer);
        return FLUSHOS_EUNKNOWN;
    }
    uint64_t start = offset;
    
    total_sectors--;
    for (size_t i = 0 ; i < total_sectors; i++){

        errno res = disk_read_sector(stream->disk , sector + i , 1 , sector_buffer);
        if (res != FLUSHOS_EGOOD){
            kfree(sector_buffer);
            return FLUSHOS_EUNKNOWN;
        }
        void* res2 = memcpy(bu8[start + i * sector_size] , sector_buffer , sector_size);
        if (res2 == NULL){
            kfree(sector_buffer);
            return FLUSHOS_EUNKNOWN;
        }
    }
    
out:
    kfree(sector_buffer);
    return FLUSHOS_EGOOD;
} 

void disk_stream_destroy(struct disk_stream* stream){
    kfree(stream);

}


