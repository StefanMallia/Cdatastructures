#include <stdbool.h>
#include <string.h> /*has the strcpy prototype*/
#include <stdlib.h> /* has the malloc prototype */
#include <stdio.h>
#include "LINKEDLIST.h"



linkedlists * create_q(int max_size)
{
	linkedlists * linkedlist = (linkedlists *)malloc(sizeof(linkedlists));
	linkedlist->max_size = max_size;
	linkedlist->headnode = NULL;

	return linkedlist;
}


void enqueue(linkedlists * linkedlist, int x, int p)
{
	

	if(linkedlist->headnode == NULL)
	{
		linkedlist->headnode = (pqnode *) malloc(sizeof(pqnode));
		
		linkedlist->headnode->element = x;
		linkedlist->headnode->priority = p;
		linkedlist->headnode->next = NULL;
	}
	else		
	{
		pqnode * current = linkedlist->headnode;

		int max_size = linkedlist->max_size;
		int i = 2;

		while(current->next != NULL)
		{
			current = current->next;
			i++;
		}
			
			
		if(i <= max_size)
		{
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

	pqnode * current;
	pqnode * prev;
	
	current = linkedlist->headnode;
	int temppriority = 0;   

	while(current != NULL)
	{
		if(current->priority > temppriority)
			temppriority = current->priority;
					
	
		current = current->next;

	}
   
	current = linkedlist->headnode;
	
	while(current->priority != temppriority && current != NULL)
	{
		prev = current;
		current=current->next;
	}   

	if(temppriority == current->priority)
	{
		prev->next = current->next;
		free(current);
	}
}


pqnode * peek(linkedlists * linkedlist)
{

/* mostly copied from dequeue */

	pqnode * current;

	current = linkedlist->headnode;
	int temppriority = 0;   
   
	while(current != NULL)
	{
		if(current->priority > temppriority)
			temppriority = current->priority;
       
		current = current->next;
	}

	current = linkedlist->headnode;

	while(temppriority != current->priority && current != NULL)
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
	{
		count++;
		current=current->next;
	}
	return count;
}


linkedlists * merge(linkedlists *linkedlistQ, linkedlists* linkedlistR)
{
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
	{
		prev = current;
		current = current->next;
		free(prev);
	}
}


void store(linkedlists * linkedlist, char * filename)
{
	char filetype[6] = "ll.bin";
	char filename2[20] = "\0";
	strncpy(filename2, filename, strlen(filename));	
	strncat(filename2,filetype,6);
	printf("%s", filename2);

	FILE * pFile = fopen(filename2, "wb");
	
	
	if (pFile != NULL)
	{
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
{

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
		


