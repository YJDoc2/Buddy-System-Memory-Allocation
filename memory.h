#ifndef MEMORY
#define MEMORY

typedef struct Chunk{
    int size;
    char pid;
} Chunk;

// typedef struct Memory{
//     int max_size;
//     Node *start;
//     Node* end;
// } Memory;

// Memory get_mem(int max_size);
// Node* get_node(int size);
// void insert_node(Memory m,Node *n);

#endif
