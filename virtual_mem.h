#ifndef VIRTUAL_MEM
#define VIRTUAL_MEM
typedef struct processQueue	
{
	int size;
	int pid;
	struct processQueue *next;

}virtualMemoryQueue;

//To add a process to virtual memory queue
void* virtualMemoryEnqueue(int pid,int processSize);

//To remove the first element of queue if freememory >= front->size
void* virtualMemoryDequeue(int freeMemory);

//To display the memory
void display_virtual_memory();

// To empty the queue
void flushQueue();

#endif
