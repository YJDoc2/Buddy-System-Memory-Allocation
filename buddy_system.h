#ifndef BUDDY_SYS
#define BUDDY_SYS

//* Init Function for memory. Must Be called before alloc or delloc.
//* Prepares holes list.
void make_mem(int max_size);

//* Function to allocate memory
void* alloc(int pid,int size);

//* Function to de-allocate memory
int delloc(void *node);

//* Iterates through memory Chunks and prints status of each chunk.
void print_stat();

#endif