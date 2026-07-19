#ifndef __FLUSHOS_DRIVER_H__
#define __FLUSHOS_DRIVER_H__
    #include <stdint.h>
    #include <stddef.h>

    #include <disk/disk.h>

    enum driver_type {
        BLOCK_DRIVER 
    };
    typedef enum driver_type driver_type;


    struct driver{
        driver_type      type;

        errno (*init)(void);
        errno (*fini)(void);
        errno (*probe)(void);
        
        uint32_t        id;
        char name[32];
    };

    typedef struct driver driver;

    /**
     * @brief 
     * 
     * @return errno 
     */
    errno driver_init(void);
    /**
     * @brief 
     * 
     * @param driv 
     * @return errno 
     */
    errno driver_register(driver* driv);
    /**
     * @brief 
     * 
     * @param driv 
     * @return errno 
     */
    errno driver_unregister(driver* driv);
    /**
     * @brief 
     * 
     * @return int 
     */
    int driver_get_max(void);

    

    
    





#endif 