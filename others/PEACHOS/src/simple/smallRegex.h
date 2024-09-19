#ifndef SMALLREGEX_H
#define SMALLREGEX_H

    #include <def.h>
    #include <status.h>
    #include <config.h>
    #include "string.h"


    kbool charInRange(char ch , char start , char end );

    kbool charInRangeE(char ch , char start , char end);

    uint8_t charIsDigit(char c);

    int charGetDigit(char c);

#endif 