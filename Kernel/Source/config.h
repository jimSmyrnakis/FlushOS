#ifndef __FLUSHOS_CONFIG_H__
#define __FLUSHOS_CONFIG_H__

    #define KERNEL_CODE_SELECTOR 0x08
    #define KERNEL_DATA_SELECTOR 0x10
    #define KERNEL_MAX_PATH_SIZE 256
    #define KERNEL_MAX_FILE_SYSTEMS 64
    #define KERNEL_MAX_FILE_DESCRIPTORS 1024
    #define KERNEL_MAX_PATH_PART_SIZE 8 // at least for 
    //fat16 support for moment (these must defined by file systems them self's actually)
    //but for moment it will do the job

#endif 