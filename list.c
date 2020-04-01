#include<stdlib.h>
#include "list.h"
#include "memory.h"

void* get_hole(List *l,int size){

    if(l->start == NULL){
        return (void*)-1;
    }
    Node *prev = l->start;
    Node *n = l->start;
    void* loc = (void*)-1;
    //* Only one node;
    if(l->start->next == NULL){
        //* No sufficient sized chunk available
        if(l->start->size < size){
            return loc;
        }
        l->start = NULL;
        loc = n->loc;
        free(n);
        return loc;
    }
    
    //* More than one node
    while(n != NULL && n->next != NULL){
        //* As the list is ordered small -> large
        if(n->size >= size){
            prev->next = n->next;
            loc = n->loc;
            free(n);
            return loc;
        }
        prev = n;
        n = n->next;
    }
    if(n != NULL && n->size >= size){
        prev->next = n->next;
        loc = n->loc;
        free(n);
        return loc;
    }
    return (void*)-1;
}

void add_hole(List *l,int size,void*loc){
    Node *n = (Node *)malloc(sizeof(Node));
    n->loc = loc;
    n->size = size;
    n->next = NULL;
    //* List ordering is from small -> large
    if(l->start == NULL){
        l->start = n;
        return;
    }
    if(l->start->size > size ){
        n->next = l->start;
        l->start = n;
        return;
    }
    Node* temp = l->start;
    while(temp->next != NULL && temp->next->size <= size){
        temp = temp->next;
    }
    if(temp->next == NULL){
        temp->next =n;
        return;
    }else{
        n->next = temp->next;
        temp->next =n;
        return;
    }
}

void* find_adjecent_hole(List *l,void *loc,int size){

    Node *temp = l->start;
    Node *prev = l->start;
    void * ret = (void*)-1;
    while(temp != NULL && temp->size != size){
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL) {
        return (void*)-1;
    }
    Chunk *in = (Chunk *)loc;
    while(temp != NULL && temp->size == size){
        prev = temp;
        Chunk *t = (Chunk *)temp->loc;
        if(in-in->size == t || in + in->size == t){
            if(l->start == temp){
                l->start = temp->next;
            }else{
                prev->next = temp->next;
            }
            ret = temp->loc;
            free(temp);
            return ret;
        }
        temp = temp->next;
    }
    return (void*)-1;

}