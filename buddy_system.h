#ifndef BUDDY_SYS
#define BUDDY_SYS

void make_mem(int max_size);
void* alloc(int pid,int size);
int delloc(void *node);

void print_stat();

#endif