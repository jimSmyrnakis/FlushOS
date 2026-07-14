#include "kernel.h"

//#include <inttypes.h> // optional, for PRI... macros if needed

struct linklist* head = NULL;
    struct linklist first_element;
    struct linklist second_element;



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

    
    int x = 1, y = 2;

    first_element.data = &x;
    first_element.next = NULL;

    second_element.data = &y;
    second_element.next = NULL;

    linklist_insert(&head, &first_element , NULL);
    linklist_insert(&head , &second_element , &first_element);

    struct linklist* it = (head);
    while (it != NULL){

        int val = *((int*)it->data);
        printHex((void*)val);
        print("\n");
        it = it->next;
    }

    int fd = fopen("0:/Hello.txt", "r");
    if (fd > 0)
    {
        print("\nWe opened hello.txt\n");
        char read_buffer[256] = {0};
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
    //struct _x86_32_gdtr gdtr;
    //_x86_32_get_gdtr(&gdtr);
    //struct x86_32_gdt gdt;
    //x86_32_gdtr_set_gdt(&gdt , &gdtr);
    //struct _x86_32_descriptor descr;
    //x86_32_gdt_get_descriptor(&gdt , 1 , &descr);
    //struct x86_32_code_segment code;
    //x86_32_descriptor_set_code_segment(&descr);
    //x86_32_gdt_get_descriptor(&my_gdt , 0 , &general_descriptor);
    panic("\n{Error at file " __FILE__ " in line " " hehe } " ": Just kernel panic !!!\n ");
    while(1) {}
}