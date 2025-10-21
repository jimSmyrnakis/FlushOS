#include "panic.h"

void panic(const char* msg){
    print(msg);
    while(1) {};//halt cpu
}