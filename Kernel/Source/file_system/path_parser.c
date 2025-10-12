#include "path_parser.h"
#include "../std/string.h"
#include "../std/memory.h"
#include "../heap/kheap.h"
#include "../config.h"
#include "../errno.h"

#ifndef NULL
#define NULL ((void*)0)
#endif 
// The current implementation is just something that works 
// memory allocation is very badly used here 

// check if the begining of the path is right
static int is_path_with_valid_format(const char* file_path){ 
    size_t len = strnlen(file_path , KERNEL_MAX_PATH_SIZE);
    return (len >= 3 && str_is_digit(file_path[0]) && memcmp((void*)&file_path[1], ":/", 2) == 0);
}

// if everything goes ok then return's the disk number (index)
// and removes the disk specification part on the path
static errno path_parser_disk_no(const char** path , int* disk_no){
    if (!is_path_with_valid_format(*path))
        return FLUSHOS_EBADPATH;

    *disk_no = str_to_digit((*path)[0]);

    (*path) += 3;
    
    return FLUSHOS_EGOOD;
}

// return's the full struct of the path root witch is the disk where is at
static struct path_root* path_parser_get_root(int disk_no){
    struct path_root* root = (struct path_root*)kzalloc(sizeof(struct path_root));
    if (root == NULL) return NULL;

    root->disk_no = disk_no;
    root->first = NULL;
    
    return root;
}

// returns the string of the first directory/filename (returns just the text
// until it finds a / or null terminate character :)
static const char* path_parser_get_path_part(const char** path){
    char* result_path_part = kzalloc(KERNEL_MAX_PATH_SIZE);
    int i = 0;
    while(**path != '/' && **path != 0x00)
    {
        result_path_part[i] = **path;
        *path += 1;
        i++;
    }

    if (**path == '/')
    {
        // Skip the forward slash to avoid problems
        *path += 1;
    }

    if(i == 0)
    {
        kfree(result_path_part);
        result_path_part = 0;
    }

    return result_path_part;
} 

// creates the next part from the current path
static struct path_part* path_parser_next_part(struct path_part* last , const char** path){
    struct path_part* next_part = (struct path_part*)kzalloc(sizeof(struct path_part));
    if (next_part == NULL)
        return NULL;

    next_part->next = NULL;
    next_part->part = path_parser_get_path_part(path);
    if (next_part->part == NULL){
        kfree(next_part);
        return NULL;
    }

    if (last != NULL)
        last->next = next_part;

    return next_part;
}

// frees all allocated memory
void path_parser_free_parts(struct path_root* root){
    if (!root) return ;

    struct path_part* path = root->first;

    while (path != NULL){
        struct path_part* next = path->next;

        kfree((char*)path->part);
        kfree(path);

        path = next;
    }

    kfree(root);
}

struct path_root* path_parser_parse(const char* path, const char* current_directory_path){
    // 
    const char* temp_path = path;

    if (
        (strnlen(path , KERNEL_MAX_PATH_SIZE) == KERNEL_MAX_PATH_SIZE)
        &&
        (path[KERNEL_MAX_PATH_SIZE] != '\0')
    ){
        // :) you thought
        return NULL; // dont deal with it bruh 
    }

    int disk_no;
    errno res = path_parser_disk_no(&temp_path , &disk_no);
    if (res != FLUSHOS_EGOOD)
        return NULL;
    
    struct path_root* root = path_parser_get_root(disk_no);
    if (root == NULL)
        return NULL;

    struct path_part* part = path_parser_next_part(NULL , &temp_path);
    if (part == NULL){
        kfree(root);
        return NULL;
    }

    root->first = part;
    part->next  = NULL;

    while(part){
        struct path_part* next = path_parser_next_part(part , &temp_path);
        part->next = next;
        part = next;
    };


    return root;    
}