#include "kernel.h"

//#include <inttypes.h> // optional, for PRI... macros if needed





int len  = 0;
struct file_stat s;
void kernel_main(void){
    disable_intt();
    pic_remap(0x20 , 0x28);

    text_mode_init(coloured_display);
    char st[] = "Hello World !!! from kernel os \n";
    print(st);
    
    
    
    interrupts_init();
    
    pic_enable_irq(1); // test keyboard interrupts :)
    
    kheap_init();
    enable_intt();
    


    disable_intt();
    struct paging_flags pflags;
    pflags.cache_disable = false;
    pflags.cache_write_through = true;
    pflags.present = true;
    pflags.user = true;
    pflags.writable = true;
    struct paging_info* pinfo =  paging_init(pflags);



    paging_switch(pinfo);

    paging_enable();
    enable_intt();


    file_system_init();
    disk_init();



    int fd = fopen("0:/Hello.txt", "r");
    if (fd > 0)
    {
        print("\nWe opened hello.txt\n");
        char read_buffer[256];
        fread(read_buffer , 5 , 1 , fd);
        print(read_buffer);
        print("\n");
        fseek(fd , 0 , SEEK_SET);
        fread(read_buffer , 5 , 1 , fd);
        print(read_buffer);
        print("\n");
        fseek(fd , -5 , SEEK_CUR);
        fread(read_buffer , 30 , 3 , fd);
        print(read_buffer);
        print("\n");

        
        fstat(fd ,&s);
        print("filesize : ");
        printHex((void*)s.size);
        print("\n");
        if (s.status & FILE_STATUS_READ_ONLY){
            print("File is read only \n");
        }
        print("filename : ");
        print(s.name);
        print("\n");

        errno res = fclose(fd);
        if (res != FLUSHOS_EGOOD){
            print("Something Wrong with fclose :( !!!\n");
        }
        res= fseek(fd , 0 , SEEK_SET);
        if (res != FLUSHOS_EGOOD){
            print("Something Wrong with fseek :( !!!\n");
        }
        res = fread(read_buffer , 5 , 1 , fd);
        if (res != FLUSHOS_EGOOD){
            print("Something Wrong with fread :( !!!\n");
        }
        print(read_buffer);
    }
    panic("\nError : Just kernel panic !!!\n at file " __FILE__ " in line " " hehe \n");
    while(1) {}
}