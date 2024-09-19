#ifndef X86_32_SEGMENT_H
#define X86_32_SEGMENT_H

    #include "../../core.h"
    #include "../../error.h"
    #include "../descriptors.h"

    bool X86_32_CALL x86_32_check_segment_size(uint32_t base , uint32_t limit);

#endif