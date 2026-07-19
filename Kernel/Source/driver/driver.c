#include "driver.h"
#include <print.h>
#include <std/string.h>
#include <std/memory.h>
#define MAX_DRIVERS 256
driver* drivers[MAX_DRIVERS] = {0};

errno driver_init(void){
    memset(drivers , 0 , sizeof(drivers));
    return FLUSHOS_EGOOD;
}


errno driver_register(driver* driv){
    if (!driv)
        return FLUSHOS_EBADARG;

    for(int i=0;i<MAX_DRIVERS;i++)
    {
        if(drivers[i] == NULL)
        {
            driv->id = i;
            drivers[i] = driv;
            errno res ;
            if (drivers[i]->init){
                res = drivers[i]->init();
                if(res != FLUSHOS_EGOOD)
                {
                    drivers[i] = NULL;
                    return res;
                }
            }
            
            
            res = drivers[i]->probe();

            if(res != FLUSHOS_EGOOD)
            {
                driv->fini();
                drivers[i] = NULL;
                return res;
            }
            print("Driver Registered : ");
            print(driv->name);
            print("\n");
            return FLUSHOS_EGOOD;
        }
    }
    
    return FLUSHOS_EOOB;
}

errno driver_unregister(driver* driv){
    if (!driv)
        return FLUSHOS_EBADARG;

    if (driv->id >= MAX_DRIVERS)
        return FLUSHOS_EOOB;

    if (driv != drivers[driv->id])
        return FLUSHOS_NDTCD;

    errno res = driv->fini();
    drivers[driv->id] = NULL;
    print("Unregister Driver");
    print(driv->name);
    print("With error code ");
    printHex((void*)res);
    print("\n");

    return res;
}