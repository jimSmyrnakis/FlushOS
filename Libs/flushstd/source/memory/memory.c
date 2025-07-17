#include "memory.h"
#define castArray( Ptr  , Index , Type ) ( *( ( (Type*) Ptr )  + Index) ) 


int memcpy(void* dest ,const void* src ,int cnt){

    if (cnt <= 0)
        return 1;

    int i;
    for (i = 0 ; i < cnt ; i++)
        castArray(dest , i , char ) = castArray(src  , i , char ); 

    return 0;
}

int memcmp(void* dt1 , void* dt2 , int cnt , bool little_endian){
    if (cnt <= 0)
        return 1;

    int i;
    unsigned char byte_dt1;
    unsigned char byte_dt2;

    for(i =(little_endian ? 0 : cnt-1 ) ; little_endian ?  (i < cnt) : (i >= 0) ; little_endian ? (i++) : (i--)){
            
        byte_dt1 = castArray(dt1 , i , unsigned char);
        byte_dt2 = castArray(dt2 , i , unsigned char);

        if (byte_dt1 > byte_dt2)
            return  +1;
        
        if (byte_dt1 < byte_dt2)
            return -1;
        
    }

    return 0;
}

int memwrite( void* base , int cnt , uint8_t default_value , bool little_endian){
    if ( cnt <= 0)
        return 1;
    
    int i = 0;
    for(i =(little_endian ? 0 : cnt-1 ) ; little_endian ?  (i < cnt) : (i >= 0) ; little_endian ? (i++) : (i--))
        castArray(base , i , uint8_t ) = default_value;

    return 0;
}


