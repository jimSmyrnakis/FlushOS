#ifndef __FLUSHOS_COMMON_DEFS_H__
#define __FLUSHOS_COMMON_DEFS_H__

    #include <stdint.h>
    #include <stddef.h>

    // all modes of a file 
    typedef uint16_t file_mode;
    enum {
        FILE_MODE_READ = 0x01,
        FILE_MODE_WRITE = 0x02,
        FILE_MODE_APPEND = 0x04,
        FILE_MODE_INVALID = 0x08
    };

    // the seek mode , a relative pointer in the file 
    enum seek_mode {
        SEEK_CUR,
        SEEK_END,
        SEEK_SET
    };


#endif 