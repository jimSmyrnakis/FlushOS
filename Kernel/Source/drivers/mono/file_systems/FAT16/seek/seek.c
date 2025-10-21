#include "common.c"

errno fat16_seek(void* private, int offset, enum seek_mode seek_mode){
    
    struct fat16_descriptor* descr = (struct fat16_descriptor* )private;
    if (descr->item->type != FAT16_FILE_TYPE_SIMPLE_FILE){
        return FLUSHOS_INVLDIO;
    }

    if (offset >= (int32_t)descr->item->file.filesize){
        return FLUSHOS_EBADARG;
    }

    switch(seek_mode){
        case SEEK_CUR: descr->pos += offset; break;
        case SEEK_END: return FLUSHOS_ENIMPL;
        case SEEK_SET: descr->pos = offset; break;
        default:
            return FLUSHOS_EBADARG;
    }
    

    return FLUSHOS_EGOOD;
}