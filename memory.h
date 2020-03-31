#ifndef MEMORY
#define MEMORY

typedef struct Node{
    int size;
    char occupied;
    char pid;
    struct Node *prev;
    struct Node *next;
    
} Node;

typedef struct Memory{
    int max_size;
    Node *start;
    Node* end;
} Memory;

Memory get_mem(int max_size);
Node* get_node(int size);
void insert_node(Memory m,Node *n);

#endif
