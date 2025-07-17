#include "segment.h"


bool X86_32_CALL x86_32_check_segment_size(uint32_t base , uint32_t limit){
    if ((UINT32_MAX - base + 1) >= (limit + 1) )
        return false;
    return true;
}
