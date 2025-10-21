#include "file.h"
#include "../config.h"
#include "../std/memory.h"
#include "../std/string.h"
#include "../heap/kheap.h"
#include "path_parser.h"
#include "../disk/disk.h"
#include "../disk/disk_stream.h"
#include "../drivers/mono/file_systems/FAT16/fat16.h"

#ifndef NULL
#define NULL ((void*)0)
#endif 
struct file_system* file_systems[KERNEL_MAX_FILE_SYSTEMS];
struct file_descriptor* file_descriptors[KERNEL_MAX_FILE_DESCRIPTORS];

static struct file_system** file_system_get_free_file_system(void){
    uint32_t i = 0 ;
    for (i = 0 ; i < KERNEL_MAX_FILE_SYSTEMS; i++){
        if (file_systems[i] == NULL){
            return &file_systems[i];
        }
    }

    return NULL;
}

static errno file_system_get_free_descriptor(struct file_descriptor** descr_out){
    uint32_t i = 0 ;
    for (i = 0 ; i < KERNEL_MAX_FILE_DESCRIPTORS; i++){
        if (file_descriptors[i] == NULL){
            struct file_descriptor* descr = 
            (struct file_descriptor*)kzalloc(sizeof(struct file_descriptor));
            file_descriptors[i] = descr;
            (*descr_out) =  file_descriptors[i];
            descr->index = i + 1;
            return FLUSHOS_EGOOD;
        }
    }

    return FLUSHOS_ENOMEM;
}

static struct file_descriptor* file_system_get_descriptor(uint32_t fd)
{
    if (fd == 0 || fd >= KERNEL_MAX_FILE_DESCRIPTORS)
    {
        return NULL;
    }
    // Descriptors start at 1
    int index = fd - 1;
    return file_descriptors[index];
}

static void file_system_load_kernel_disks(void){
    file_system_insert(fat16_init());
}

void file_system_init(void){
    memset(file_systems , (int)NULL , KERNEL_MAX_FILE_SYSTEMS * sizeof(void*));
    memset(file_descriptors , (int)NULL , KERNEL_MAX_FILE_DESCRIPTORS * sizeof(void*));
    // after that we load all core kernel file systems that we have implemented , others
    // may come in form of device files inside these file systems . Yeap we speak about
    // device drivers guys , this is some cool things about kernel development , you learn 
    // everything of how things working :) .
    file_system_load_kernel_disks();
}

file_mode string_to_file_mode(const char* mode){
    file_mode res = FILE_MODE_INVALID;

    if (strncmp(mode, "r", 1) == 0)
    {
        res = FILE_MODE_READ;
    }
    else if(strncmp(mode, "w", 1) == 0)
    {
        res = FILE_MODE_WRITE;
    }
    else if(strncmp(mode, "a", 1) == 0)
    {
        res = FILE_MODE_APPEND;
    }

    return res;
}

int  fopen(const char* filename , const char* mode){
    if (filename == NULL || !mode){
        return 0; // invalid argument's
    }

    struct path_root* paths = path_parser_parse(filename , NULL);
    if (paths == NULL)
        return 0; // bad path syntax

    if (paths->first == NULL){
        return 0; // no valid to try open root folder 
    }

    // check if this disk exist's
    struct disk* disk = disk_get(paths->disk_no);
    if (disk == NULL){
        return 0;
    }

    // check if there is a bounded file system in this disk :)
    struct file_system* fs = disk->fs;
    if (fs == NULL){
        return 0;
    }

    // take the file mode into flags
    file_mode fmode = string_to_file_mode(mode);
    if (fmode == FILE_MODE_INVALID){
        return 0;
    }

    // call open of the file system 
    void* priv = fs->open(disk , paths->first , fmode);
    if (priv == NULL){
        return 0;
    }

    
    // now create a new descriptor
    struct file_descriptor* descr = NULL;
    errno res = file_system_get_free_descriptor(&descr);
    if (res != 0){
        return res;
    }

    // fill the descriptor
    descr->disk = disk;
    descr->fsystem = fs;
    descr->mode = fmode;
    descr->private_data = priv;


    
    return descr->index;
}

struct file_system* fs_resolve(struct disk* disk){

    if (disk == NULL)
        return NULL;

    struct file_system* fs = NULL;
    uint32_t i = 0 ;
    for (i = 0 ; i < KERNEL_MAX_FILE_SYSTEMS; i++){
        if ( (file_systems[i] != NULL ) && (file_systems[i]->resolve(disk) == FLUSHOS_EGOOD) ){
            fs = file_systems[i];
            break;
        }
    }

    return fs;
}
void file_system_insert(struct file_system* fs){
    // TODO : in the future if the fs is NULL then make the system panic :)
    struct file_system** free_fs = file_system_get_free_file_system();
    // TODO: in the future if there is no other file system left make panic the 
    // kernel 

    (*free_fs) = fs;


}

errno fread(void* ptr, uint32_t size, uint32_t nmemb, int fd){
    errno res = FLUSHOS_EGOOD;
    if ((size == 0) || (nmemb == 0) || (fd < 1) )
    {
        return FLUSHOS_EBADARG;
    }

    struct file_descriptor* desc = file_system_get_descriptor(fd);
    if (!desc)
    {
        return FLUSHOS_EBADARG;
    }

    res = desc->fsystem->read(desc->disk, desc->private_data, size, nmemb, (char*) ptr);
out:
    return res;
}



