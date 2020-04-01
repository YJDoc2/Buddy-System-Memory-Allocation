#include <stdio.h>
#include "buddy_system.h"


void main(){

    int max_size = 1024;
    make_mem(max_size);
    void *temp1 = alloc(1,512);
    print_stat();
    void *temp2 = alloc(2,120);
    print_stat();
    //* This allocation fails as no memory available.
    void *temp3 = alloc(3,512);
    delloc(temp1);
    print_stat();
    //* Now this succeds
    temp3 = alloc(3,512);
    print_stat();
    delloc(temp2);
    print_stat();
    delloc(temp3);
    print_stat();
    
    
}