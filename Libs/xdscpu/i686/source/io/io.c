#include "io.h"

#define IS_IN_BAD_RANGE(port) (((port) <= 0x00FF) && ((port) >= 0x00F8))
#define IS_IN_BAD_RANGE_B(port) IS_IN_BAD_RANGE(port)
#define IS_IN_BAD_RANGE_W(port) ( IS_IN_BAD_RANGE(port) || IS_IN_BAD_RANGE(port + 1) )
#define IS_IN_BAD_RANGE_D(port) ( IS_IN_BAD_RANGE_W(port) || IS_IN_BAD_RANGE_W(port + 2) )

x86_32_err_type X86_32_CALL x86_32_inb(x86_32_port port , uint8_t * data){

    if (IS_IN_BAD_RANGE_B(port))
        return X86_32_E_IORSVDPORT;

    (*data) = _x86_32_inb(port);

out:
    return X86_32_E_OK;
}

x86_32_err_type X86_32_CALL x86_32_inw(x86_32_port port , uint16_t* data){
    x86_32_err_type err = X86_32_E_OK;

    if (IS_IN_BAD_RANGE_W(port))
        return X86_32_E_IORSVDPORT;

    if (port % 2)
        err =  X86_32_W_IOBADALGN;

    (*data) = _x86_32_inw(port);

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_ind(x86_32_port port , uint32_t* data){
    x86_32_err_type err = X86_32_E_OK;

    if (IS_IN_BAD_RANGE_D(port))
        return X86_32_E_IORSVDPORT;

    if (port % 4)
        err =  X86_32_W_IOBADALGN;

    (*data) = _x86_32_ind(port);

out:
    return err;
}
    
x86_32_err_type X86_32_CALL x86_32_outb(x86_32_port port , uint8_t  data){
    x86_32_err_type err = X86_32_E_OK;
    
    if (IS_IN_BAD_RANGE_B(port)){
        err = X86_32_E_IORSVDPORT;
        goto out;
    }

    _x86_32_outb(port , data);

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_outw(x86_32_port port , uint16_t data){
    x86_32_err_type err = X86_32_E_OK;
    
    if (IS_IN_BAD_RANGE_B(port)){
        err = X86_32_E_IORSVDPORT;
        goto out;
    }

    if (port % 2)
        err = X86_32_W_IOBADALGN;

    _x86_32_outw(port , data);
    
out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_outd(x86_32_port port , uint32_t data){
    x86_32_err_type err = X86_32_E_OK;
    
    if (IS_IN_BAD_RANGE_B(port)){
        err = X86_32_E_IORSVDPORT;
        goto out;
    }

    if (port % 4)
        err = X86_32_W_IOBADALGN;

    _x86_32_outd(port , data);
    
out:
    return err;
} 

x86_32_err_type X86_32_CALL x86_32_insb(x86_32_port port , uint16_t count , uint8_t * buffer){
    x86_32_err_type err = X86_32_E_OK;
    
    if (IS_IN_BAD_RANGE_B(port)){
        err = X86_32_E_IORSVDPORT;
        goto out;
    }

    if (count == 0)
        err = X86_32_W_ZRCNT;

    _x86_32_insb(port , count , buffer);

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_insw(x86_32_port port , uint16_t count , uint16_t* buffer){
    x86_32_err_type err = X86_32_E_OK;
    
    if (IS_IN_BAD_RANGE_B(port)){
        err = X86_32_E_IORSVDPORT;
        goto out;
    }

    if (count == 0)
        err = X86_32_W_ZRCNT;
    
    if (port % 2)
        err = X86_32_W_IOBADALGN;

    _x86_32_insw(port , count , buffer);
    
out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_insd(x86_32_port port , uint16_t count , uint32_t* buffer){
    x86_32_err_type err = X86_32_E_OK;
    
    if (IS_IN_BAD_RANGE_B(port)){
        err = X86_32_E_IORSVDPORT;
        goto out;
    }

    if (count == 0)
        err = X86_32_W_ZRCNT;
    
    if (port % 4)
        err = X86_32_W_IOBADALGN;

    _x86_32_insd(port , count , buffer);
    
out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_outsb(x86_32_port port , uint16_t count , uint8_t * buffer){
    x86_32_err_type err = X86_32_E_OK;
    
    if (IS_IN_BAD_RANGE_B(port)){
        err = X86_32_E_IORSVDPORT;
        goto out;
    }

    if (count == 0)
        err = X86_32_W_ZRCNT;
    
    _x86_32_outsb(port , count , buffer);

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_outsw(x86_32_port port , uint16_t count , uint16_t* buffer){
    x86_32_err_type err = X86_32_E_OK;
    
    if (IS_IN_BAD_RANGE_B(port)){
        err = X86_32_E_IORSVDPORT;
        goto out;
    }

    if (count == 0)
        err = X86_32_W_ZRCNT;
    
    if (port % 2)
        err = X86_32_W_IOBADALGN;
    
    _x86_32_outsw(port , count , buffer);

out:
    return err;
}

x86_32_err_type X86_32_CALL x86_32_outsd(x86_32_port port , uint16_t count , uint32_t* buffer){
    x86_32_err_type err = X86_32_E_OK;
    
    if (IS_IN_BAD_RANGE_B(port)){
        err = X86_32_E_IORSVDPORT;
        goto out;
    }

    if (count == 0)
        err = X86_32_W_ZRCNT;
    
    if (port % 4)
        err = X86_32_W_IOBADALGN;
    
    _x86_32_outsd(port , count , buffer);

out:
    return err;
}