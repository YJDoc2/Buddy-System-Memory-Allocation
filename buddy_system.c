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
    insert_hole(&holes,max_size,mem);
}

void* alloc(int pid,int size){
    Chunk *temp = (Chunk*)mem;
    
    temp = (Chunk*)get_hole(&holes,size);

    // No hole with adequate size found
    if(temp == (Chunk *)-1){
        return (void*)-1;
    }

    // We keep subdividing into two parts, until current size is just adequate for the reuirement.
    while(temp->size/2 >= size){
        // Inser hole of half size, which begins at current position+half-size
        insert_hole( &holes , temp->size/2 , (void*)(temp+temp->size/2) );
        // Set allocation pid of the 'other' hole to -1
        (temp + temp->size/2)->pid = -1;
        // Set size of both holes to half of original size
        temp->size = (temp + temp->size/2)->size = temp->size/2;
    }
    // Set allocation pid 
    temp->pid = pid;
    return temp;
    
        
    
    
}

int delloc(void *pos){
    
    if(pos < (void *)mem || pos > (void*)((Chunk*)mem+max_size)){
        // The memory pointed by pos is not allocated by this.
        return -1;
    }

    Chunk *d = (Chunk*)pos;
    d->pid = -1;

    Chunk *temp = (Chunk*)get_adjecent_hole(&holes,d,d->size);

    // Keep combining the adjecent holes until no adjecnt hole of same size remains
    while(temp != (Chunk*)-1){
        int size = temp->size;
        // Set starting position of the combined hole,whichever of temp and pos that comes first.
        Chunk *loc = temp > d ? d : temp;
        memset(loc,0,size*2);
        loc->pid = -1;
        loc->size = size*2;
        d = loc;
        temp = (Chunk*)get_adjecent_hole(&holes,loc,size*2);
    }
    // Add final combined hole to list
    insert_hole(&holes,d->size,d);
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