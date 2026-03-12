#ifndef __FLUSHOS_STD_LINKEDLIST_H
#define __FLUSHOS_STD_LINKEDLIST_H

    #include "../common_defs.h"
    #include "../errno.h"

    /**
     * 
     * @brief A simple link list of single link per element
     */
    struct linklist{

        void*            data;
        struct linklist* next;
    };

    /**
     * @brief Insert a new element to the link list after the prev element . If the prev is NULL
     * then the element is inserted as the first element and the head is point to it (that's why 
     * double pointer , i change where your head pointer point's to :) )
     * 
     * @param[in] element Pointer to the element to be inserted .
     * @param[in] prev Pointer to the prev element witch the element will insert in front of it .
     * @param[inout] head Double Pointer to the first element of the link list . 
     * @return  FLUSHOS_EGOOD if everything complited fine , or anything else otherwise .
     */
    errno linklist_insert(struct linklist** head , struct linklist* element , struct linklist* prev);


    


#endif 