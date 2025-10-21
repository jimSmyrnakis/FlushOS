#include "common.c"

errno fat16_stat(struct disk* disk, void* private , struct file_stat* stat){
    
    struct fat16_descriptor* descr = (struct fat16_descriptor* )private;
    if (descr->item->type != FAT16_FILE_TYPE_SIMPLE_FILE){
        return FLUSHOS_INVLDIO;
    }

    strncpy( stat->name , (const char*)descr->item->file.filename , KERNEL_MAX_FILE_NAME_SIZE);
    if (descr->item->file.attribute & FAT16_ATTRIBUTE_READ_ONLY){
        stat->status |= FILE_STATUS_READ_ONLY;
    }

    stat->size = descr->item->file.filesize;

    return FLUSHOS_EGOOD;
}