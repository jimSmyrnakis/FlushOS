#ifndef __FLUSHOS_RESOURCE_H__
#define __FLUSHOS_RESOURCE_H__

    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>
    #include "../errno.h"

    struct resources{
        uint8_t* io_ports;
        
    };

    //void resources_init(void);

    //errno resource_req_io(uint16_t io_port);

    //errno resource_req_io_range(uint16_t io_start , uint16_t io_end );
 
#endif 