#include<stdio.h>
#include<stdlib.h>
#include "virtual_mem.h"
#include "memory.h"

// Virtual Memory Capacity 
static int virtual_memory_capacity = 1024;

virtualMemoryQueue *front,*rear,*temp;
void* virtualMemoryEnqueue(int pid,int processSize)
{
	if(processSize<=virtual_memory_capacity){
		Chunk *processReturn = (Chunk *)malloc(sizeof(Chunk));
		virtualMemoryQueue *newnode = (virtualMemoryQueue *)malloc(sizeof(virtualMemoryQueue));
		newnode->next=NULL;
		newnode->pid=pid;
		newnode->size=processSize;
		if (front==NULL)
		{
			front=newnode;
			rear=newnode;
		}
		else
		{
			rear->next=newnode;
			rear=newnode;
		}
		virtual_memory_capacity-=processSize;
		processReturn->pid=pid;
		processReturn->size=processSize;
		return processReturn;
	}
	else{
		/*
			Error: Process size is too large
		*/
		return NULL;
	}
}
void* virtualMemoryDequeue(int freeMemory)
{
	if (freeMemory>front->size){
		if (front==NULL)
		{
			/*
				Error:Virtual Memory is Empty
			*/
			return NULL;
		}
		else
		{
			Chunk *processReturn = (Chunk *)malloc(sizeof(Chunk));
			processReturn->size=front->size;
			processReturn->pid=front->pid;
			// Note: we cannot simply do processReturn = front; here as it is getting cleared when we free(temp)
			temp=front;
			front=front->next;
			free(temp);
			virtual_memory_capacity+=processReturn->size;
			return processReturn;
		}
	}
}
void display_virtual_memory()
{
	temp=front;
	if (front!=NULL)
	{
		printf("Memory Free Size=%d\nMemory contains:\n",virtual_memory_capacity);
		while (temp!=NULL)
		{
			printf("%d \t",temp->size);			//Display the variables from top -> bottom
			temp=temp->next;
		}
		printf("\n");
	}
}
void flushQueue()								//To Empty the Queue
{
	if (front!=NULL)
	{
		while (front!=NULL)
		{
			temp=front;
			front=front->next;
			free(temp);
		}
	}
}
//For debugging
void main()
{
    void *temp1=virtualMemoryEnqueue(1,200);
    display_virtual_memory();

    void *temp2=virtualMemoryEnqueue(2,500);
    display_virtual_memory();

    //Temp3 will be null and it wont be pushed to the queue since 1200>(1024-200-500)
    void *temp3=virtualMemoryEnqueue(3,1200);
    display_virtual_memory();

    //Free memory > Front->size
    virtualMemoryDequeue(300);
    display_virtual_memory();

    //Free memory < Front->size
    virtualMemoryDequeue(200);
    display_virtual_memory();
}