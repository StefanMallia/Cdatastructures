#include <stdbool.h>
#include <string.h> /*has the strcpy prototype*/
#include <stdlib.h> /* has the malloc prototype */
#include <stdio.h>
#include "LINKEDLIST.h"



linkedlists * create_q(int max_size)
{	//first malloc the Linkedlist (linkedlists contains all nodes and one int for max, but for now it is empty except for max int)
	linkedlists * linkedlist = (linkedlists *)malloc(sizeof(linkedlists));
	linkedlist->max_size = max_size;
	linkedlist->headnode = NULL;//headnode set to NULL until next 

	return linkedlist;
}


void enqueue(linkedlists * linkedlist, int x, int p)
{
	

	if(linkedlist->headnode == NULL)//if linkedlist contains no nodes
	{	//malloc and assign first node
		linkedlist->headnode = (pqnode *) malloc(sizeof(pqnode));
		
		linkedlist->headnode->element = x;
		linkedlist->headnode->priority = p;
		linkedlist->headnode->next = NULL;
	}
	else
	{
		pqnode * current = linkedlist->headnode;//starting from first node to iterate

		int max_size = linkedlist->max_size;
		int i = 2;//counter

		while(current->next != NULL)
		{
			current = current->next;
			i++;
		}
			
			
		if(i <= max_size)
		{//for example if max size is 2 and only one node exists then the while loop above does not execute and i is left at 2
			current->next = (pqnode *) malloc(sizeof(pqnode));			
			current = current->next;			
			
			current->element = x;
			current->priority = p;
			current->next = NULL;
		}
		else
			printf("\nLinked list is full with %d elements.\n", i-1);
	}

}

void dequeue(linkedlists * linkedlist)
{
/*FIFO*/
	pqnode * current = NULL;
	pqnode * prev = NULL;//prev required to connect previous to next
	
	current = linkedlist->headnode;
	int temppriority = 0;   

	while(current != NULL)
	{//iterate and record highest priority
		if(current->priority > temppriority)
			temppriority = current->priority;

		current = current->next;
	}
   
	current = linkedlist->headnode;
	
	while(current->priority != temppriority && current != NULL)
	{//iterate until largest priority is found
		prev = current;
		current=current->next;
	}   

	if(temppriority == current->priority && current != NULL)
	{
	
		prev->next = current->next;
		free(current);
	}
}


pqnode * peek(linkedlists * linkedlist)
{
	pqnode * current;

	current = linkedlist->headnode;
	int temppriority = 0;   
   
	while(current != NULL)
	{//iterate and record highest priority
		if(current->priority > temppriority)
			temppriority = current->priority;
       
		current = current->next;
	}

	current = linkedlist->headnode;

	while(temppriority != current->priority && current != NULL)
	//iterate until highest priority is found
		current=current->next;
		

	if(temppriority == current->priority)
	{
		return current;
	}
	else
		return NULL;
}


bool is_empty(linkedlists * linkedlist)
{
	pqnode * current;
	current = linkedlist->headnode;
   

	if(current == NULL)
		return true;
	else	
		return false;
}


int size(linkedlists * linkedlist)
{
	pqnode * current = linkedlist->headnode;
	int count = 0;

	while(current != NULL)
	{//iterate and count
		count++;
		current=current->next;
	}
	return count;
}


linkedlists * merge(linkedlists *linkedlistQ, linkedlists* linkedlistR)
{	//new queue has combined max size. 
	linkedlistQ->max_size = linkedlistQ->max_size + linkedlistR->max_size;

	pqnode * current = linkedlistQ->headnode;
	
	while(current->next != NULL)
		current = current->next;
	
	current->next = linkedlistR->headnode;
	free(linkedlistR);

	return linkedlistQ;
}


void clear(linkedlists * linkedlist)
{
	pqnode * current = linkedlist->headnode;
	pqnode * prev;

	while(current != NULL)
	{//iterate and clear
		prev = current;
		current = current->next;
		free(prev);
	}
}


void store(linkedlists * linkedlist, char * filename)
{	//append ll.bin to distinguish from ringbuffer and to save as binary filie
	char filetype[6] = "ll.bin";
	char filename2[20] = "\0";
	strncpy(filename2, filename, strlen(filename));	
	strncat(filename2,filetype,6);
	printf("%s", filename2);

	FILE * pFile = fopen(filename2, "wb");
	
	
	if (pFile != NULL)
	{	//first fwrite the linkedlist struct, then the maxsize, then each individual node
		pqnode * Current = linkedlist->headnode;
		pqnode * holdnext = NULL;
		
		linkedlist->headnode = NULL;

		fseek(pFile, 0, SEEK_END);
		fwrite(linkedlist, sizeof(linkedlists), 1, pFile);

		linkedlist->headnode = Current;	

		int numnodes = size(linkedlist);
		fseek(pFile, 0, SEEK_END);
		fwrite(&numnodes, sizeof(int), 1, pFile);
 


		while(Current != NULL)
		{
			holdnext = Current->next;
			Current->next = NULL;

			fseek(pFile, 0, SEEK_END);
			fwrite(Current, sizeof(pqnode), 1, pFile);


			Current->next = holdnext;
			
			Current = Current->next;
		}
		printf("\nWrite Successful\n");
		fclose(pFile);
	}
	else
		printf("\nError Writing\n");		
}



linkedlists * load(char * filename)
{	//same process as store but using also using malloc

	char filetype[6] = "ll.bin";
	char filename2[20] = "\0";
	strncpy(filename2, filename, strlen(filename));	
	strncat(filename2,filetype,6);
	printf("%s", filename2);

	FILE * pFile = fopen(filename2, "rb");
	linkedlists * linkedlist;
		

	if(pFile != NULL)
	{
		linkedlist = (linkedlists *) malloc(sizeof(linkedlists));
		fseek(pFile, 0, SEEK_SET);
		fread(linkedlist, sizeof(linkedlist), 1, pFile);
				
		int numnodes;
		fseek(pFile, sizeof(linkedlists), SEEK_SET);
		fread(&numnodes, sizeof(int), 1, pFile); 
		
		if(numnodes > 0)
		{
			pqnode * current = NULL;
		
			linkedlist->headnode = (pqnode *) malloc(sizeof(pqnode));
			current = linkedlist->headnode;

			fseek(pFile, sizeof(linkedlists)+sizeof(int), SEEK_SET);
			fread(current, sizeof(pqnode), 1, pFile);
			current->next = NULL; 

			int i;
			for(i = 1; i < numnodes; i++)
			{
				current->next = (pqnode *) malloc(sizeof(pqnode));
				current = current->next;			
			
				fread(current, sizeof(pqnode), 1, pFile);
				
				current->next = NULL;		
			}
		}
		printf("\nRead successful\n");
		fclose(pFile);
	}
	else
	{
		printf("\nError with read\n");
		return NULL;
	}

	return linkedlist;
}
		


