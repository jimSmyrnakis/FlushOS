#include "status.h"

int   error_stat = 0;

int   errno(void){
    return error_stat;
}