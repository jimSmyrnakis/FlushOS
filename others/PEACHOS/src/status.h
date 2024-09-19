#ifndef STATUS_H
#define STATUS_H


    #define KERNEL_OK                   (0)
    #define EINVALIDARGS                (1)
    #define EBADPATH                    (2)
    #define ENOMEMORY                   (3)
    #define EOUTOFRANGE                 (4)
    #define ECORRUPTDATA                (5)
    #define ENOTALLIGN                  (6)
    #define ENOFS                       (7)
    #define EINVALID_FILE_DESCRIPTOR    (8)
    #define ENOTIMPLEMENT               (9)

    int   errno(void);
    extern int   error_stat;

#endif 