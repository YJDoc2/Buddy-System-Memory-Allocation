#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "buddy_system.h"

Memory mem_free,mem_alloc;

static Node* get_chunk(int size){
    //* Reverse traversal
    Node* temp = mem_free.end;
    while(temp != NULL){
        if(temp->prev == NULL){
            //* At start of the list
            mem_free.start = mem_free.end = NULL;
            return temp;
        }
        if(temp->size>=size && temp->prev->size <size){
            temp->prev->next= temp->next;
            temp->next->prev = temp->prev;
            return temp;
        }else{
            temp = temp->prev;
        }
        
    }
}
static void combine_chunks(Node *n,Node *bound){
    if(bound->size == n->size){
        bound->size = bound->size *2;
        //* Remove the 'bound' node from the mem_free list
        bound->prev->next = bound->next;
        bound->next->prev = bound->prev;
        free(n);
        combine_chunks(bound,bound->prev);
    }else{
        insert_node(mem_free,n);
    }
}

void make_mem(int max_size){
    mem_free = get_mem(max_size);
}

void* alloc(int pid,int size){
    if(size > mem_free.max_size){
        return (void*)-1;
    }
    Node* temp = get_chunk(size);
    int tsize = temp->size;
    while(1){
        if(tsize/2 > size){
            Node *t = get_node(tsize/2);
            insert_node(mem_free,t);
            temp->size = tsize/2;
            tsize = tsize/2;
        }else{
            //* Now temp is the node that has least possible size to accomodate process
            break;    
        }
    }
    temp->pid = pid;
    temp->occupied = 1;
    insert_node(mem_alloc,temp);
    return (void*)temp;
}

void delloc(void *n){
    Node *node = (Node *)n;
    Node *temp = mem_free.start;

    //* remove from mem_alloc
    if(mem_alloc.start == node){
        mem_alloc.start = node->next;
        node->next->prev = NULL;
    }else if(mem_alloc.end == node){
        mem_alloc.end = node->prev;
        node->prev->next = NULL;
    }else{
        node->prev->next = node->next;
    node->next->prev = node->prev;
    }
    
    while(temp != NULL && temp->next != NULL){
        if(temp->next->size < node->size){
            break;
        }else{
            temp = temp->next;
        }
    }
    combine_chunks(n,temp);
    return;
}

void print_free(){

    printf("Printing Free memory chunk status : \n");
    Node* temp = mem_free.start;
    while(temp != NULL){
        printf("%d\t",temp->size);
        temp = temp->next;
    }
    printf(" ;\n");
}

void print_alloc(){

    printf("Printing Allocated memory chunk status : \n");
    Node* temp = mem_alloc.start;
    while(temp != NULL){
        printf("%d\t",temp->size);
        temp = temp->next;
    }
    printf(" ;\n");
}