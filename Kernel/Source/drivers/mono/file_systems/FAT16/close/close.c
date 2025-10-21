#include "common.c"

errno fat16_close(void* private ){
    
    struct fat16_descriptor* descr = (struct fat16_descriptor* )private;
    if (!descr){
        return FLUSHOS_INVLDIO;
    }

    
    fat16_free_fat16_descriptor(descr);


    return FLUSHOS_EGOOD;
}