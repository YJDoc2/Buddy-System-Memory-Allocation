#include <stdlib.h>
#include "memory.h"

Memory get_mem(int max_size){
    Memory ret; 
    ret.max_size = max_size;
    ret.start = (Node*)calloc(1,sizeof(Node));
    ret.end = ret.start;
    ret.start->prev = NULL;
    ret.start->next = NULL;
    return ret;
}

Node* get_node(int size){
    Node* ret = (Node*)calloc(1,sizeof(Node));
    ret->size = size;
    return ret;
}

void insert_node(Memory memory,Node *t){
    if(memory.start == NULL){
        memory.start = memory.end = t;
        return;
    }
    //* Insertion at start
    if(memory.start->size < t->size){
        t->next=memory.start;
        t->prev = NULL;
        memory.start->prev = t;
        memory.start = t;
        return;
    }
    //* Insertion at end
    if(memory.end->size > t->size){
        memory.end->next = t;
        t->prev = memory.end;
        t->next = NULL;
        memory.end = t;
        return;
    }
    Node* temp = memory.start;
    while(temp != NULL){
        if(temp->size > t->size && temp->next->size <= t->size){
            t->prev = temp;
            t->next = temp->next;
            temp->next = t;
            t->next->prev =t;
            return;
        }
        temp = temp->next;
    }
}