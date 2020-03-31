#ifndef BUDDY_SYS
#define BUDDY_SYS

void make_mem(int max_size);
void* alloc(int pid,int size);
void delloc(void *node);

void print_free();
void print_alloc();

#endif