#include <stdio.h>
#include "memory.h"
#include "buddy_system.h"


void main(){

    int max_size = 1024;
    make_mem(max_size);

    void *temp1 = alloc(1,512);
    void *temp2 = alloc(2,120);
    print_free();
    print_alloc();
    void *temp3 = alloc(3,512);
    delloc(temp1);
    print_free();
    print_alloc();
    delloc(temp2);
    delloc(temp3);
    print_free();
    print_alloc();
    
}