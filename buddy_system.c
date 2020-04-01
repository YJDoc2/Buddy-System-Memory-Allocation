#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "memory.h"
#include "list.h"
#include "buddy_system.h"

void *mem;
int max_size;
List holes;

void make_mem(int max){
    max_size = max;
    mem = calloc(max_size,sizeof(Chunk));
    ((Chunk*)mem)->size = max_size;
    ((Chunk*)mem)->pid = -1;
}

void* alloc(int pid,int size){
    Chunk *temp = (Chunk*)mem;
    //* First Time alloc
    if(temp->size != max_size){
        //* it ain't the first alloc!
        temp = (Chunk*)get_hole(&holes,size);
        if(temp == (Chunk *)-1) return (void*)-1;   
    }
    while(temp->size/2 >= size){
        add_hole(&holes,temp->size/2,(void*)(temp+temp->size/2));
        (temp + temp->size/2)->pid = -1;
        temp->size = (temp + temp->size/2)->size =temp->size/2;
    }
    if(temp->size >= size){
        temp->pid = pid;
        return temp;
    }else{
        return (void*)-1;
    }
    
}

int delloc(void *n){
    if(n == (void*)-1)return -1;
    Chunk *d = (Chunk*)n;
    d->pid = -1;

    Chunk *temp = (Chunk*)find_adjecent_hole(&holes,d,d->size);
    while(temp != (Chunk*)-1){
        int size = d->size;
        void *loc = temp > d ? d : temp;
        memset(loc,0,size*2);
        ((Chunk*)loc)->pid = -1;
        ((Chunk*)loc)->size = size*2;
        temp = (Chunk*)find_adjecent_hole(&holes,d,d->size);
    }
    d->pid = -1;
    add_hole(&holes,d->size,n);
    
        
}

void print_stat(){

    printf("Printing current status of memory : \n");
    Chunk *temp = (Chunk *)mem;
    int size =0;
    while(1){
        printf("%d:%d\t",temp->pid,temp->size);
        size += temp->size;
        if(size >= max_size)break;
        temp = (temp+temp->size);
    }
    printf("\n");
}