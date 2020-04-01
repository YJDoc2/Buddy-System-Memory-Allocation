#ifndef LIST
#define LIST

typedef struct Node{
    int size;
    void* loc;
    struct Node *next;
} Node;

typedef struct List{
    Node *start;
} List;

void* get_hole(List *l,int size);
void add_hole(List *l,int size,void* loc);
void* find_adjecent_hole(List *l,void *n,int size);

#endif
