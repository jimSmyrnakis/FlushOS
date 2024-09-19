#include "file.h"
#include <term/term.h>
#include "fat/fat16.h"

struct file_system* file_systems[PEACHOS_MAX_FILESYSTEMS];
struct file_descriptor* file_descriptors[PEACHOS_MAX_FILE_DESCRIPTORS];

struct file_system** fs_get_free_file_system(void){
    int i = 0;
    for ( i = 0 ; i < PEACHOS_MAX_FILESYSTEMS; i++){
        if (file_systems[i] == KNULL)
            return &file_systems[i]; 
    }
    return KNULL;
}

void fs_insert_file_system(struct file_system* file_system){
    struct file_system** fs = fs_get_free_file_system();
    if (fs == KNULL){
        error_stat = ENOFS;
        vgaPrintStr("Im Pannicing :( :{O ");
        while(1); //just something for the terror
    }

    (*fs) = file_system; // this is where user land can use too
}

static void fs_static_insert(void){
    //this is mine initials system_files
    fs_insert_file_system(fat16_init());
}

void initiallize_file_systems(void){
    int i = 0;
    for ( i = 0;i < PEACHOS_MAX_FILESYSTEMS ; i++)
        file_systems[i] = KNULL;

    fs_static_insert();

}

void initiallize_file_descriptors(void){

    int i = 0; 
    for ( i = 0; i < PEACHOS_MAX_FILE_DESCRIPTORS ; i++)
        file_descriptors[i] = KNULL;

}

void fs_init(){
    initiallize_file_descriptors();
    initiallize_file_systems();
}

static int file_new_descriptor(struct file_descriptor** descriptor_out){
    error_stat = KERNEL_OK;
    for (int i  = 0; i < PEACHOS_MAX_FILE_DESCRIPTORS; i++){
        if (file_descriptors[i] == KNULL){
            file_descriptors[i] = kzalloc(sizeof(struct file_descriptor));
            if (file_descriptors[i] == KNULL)
                goto out;
            
            (*descriptor_out) = file_descriptors[i];
            (*descriptor_out)->index = i + 1;
        }
    }

out:
    return error_stat;
}

static struct file_descriptor* file_get_descriptor(int fd){
    error_stat = KERNEL_OK;
    if ((fd > PEACHOS_MAX_FILE_DESCRIPTORS) || (fd <= 0)){
        error_stat = EOUTOFRANGE;
        return KNULL;
    }
    if (file_descriptors[fd-1]->index != fd){
        error_stat = EINVALID_FILE_DESCRIPTOR;
        return KNULL;
    }
    return file_descriptors[fd-1];
}

int fopen(const char* filename , const char* mode){
    error_stat = ENOTIMPLEMENT;
    return error_stat;
}

struct file_system* fs_resolve(struct disk* disk){

    for (int i = 0; i <  PEACHOS_MAX_FILESYSTEMS ; i++){
        if (file_systems[i] == KNULL)
            continue;

        if (file_systems[i]->resolve(disk) == 0)
            return file_systems[i];
    }
    return KNULL;
}