#include "smallRegex.h"

//for small regex exprensions

kbool charInRange(char ch , char start , char end ){
    if (start > end )
    {
        char temp = start;
        start = end;
        end   = temp;
    }
    return (ch >= start) && (ch <= end);
}

kbool charInRangeE(char ch , char start , char end){
    return charInRange(ch , start - 1 , end -1);
}

uint8_t charIsDigit(char c){
    return charInRange(c , '0' , '9' );
}

int charGetDigit(char c){
    return ((int)c) - ((int)'0');
} 