#include "linklist.h"
#include "../panic.h"
errno linklist_insert(struct linklist** head , struct linklist* element , struct linklist* prev){
    element->next = NULL;
    if (element == NULL)
    {
        DEBUG_LOG("element is NULL" , 0);
        return FLUSHOS_EBADARG;
    }

    if (head == NULL)
    {
        DEBUG_LOG("head is NULL" , 0);
        return FLUSHOS_EBADARG;
    }

    struct linklist* first_element = (*head);

    if ( (first_element == NULL) && (prev != NULL) ){
        DEBUG_LOG("no element in the list , but prev has a element " , 0);
        return FLUSHOS_EUNKNOWN;
    }

    if (prev == NULL) { // if element must inserted front or list is empty
        element->next = first_element;
        first_element = element;
    }
    else{ // if element should inserted second and after
        element->next = prev->next;
        prev->next = element;
    }

    (*head) = first_element;

    return FLUSHOS_EGOOD;
}

