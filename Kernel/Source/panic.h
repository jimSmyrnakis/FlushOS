#ifndef __FLUSHOS_PANIC_H__
#define __FLUSHOS_PANIC_H__

    #include <stdint.h>
    #include <stddef.h>
    #include "print.h"

    void panic(const char* msg);

    #define DEBUG_LOG(msg , error_code) { panic("Error[ In file " __FILE__ " at line (?) with code ==> ? ] : " #msg  );}

#endif 