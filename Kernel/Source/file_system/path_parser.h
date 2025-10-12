#ifndef __FLUSHOS_PATH_PARSER_H__
#define __FLUSHOS_PATH_PARSER_H__

    #include <stdint.h>
    #include <stddef.h>
    struct path_part
    {
        const char* part;
        struct path_part* next;
    };
    struct path_root
    {
        int disk_no;
        struct path_part* first;
    };



    struct path_root* path_parser_parse(const char* path, const char* current_directory_path);
    void path_parser_free_parts(struct path_root* root);
#endif 