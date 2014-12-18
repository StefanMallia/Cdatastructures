//#ifndef _PQUEUE_H_
//#define _PQUEUE_H_
#include <stdbool.h>
#include <string.h> /*has the strcpy prototype*/
#include <stdlib.h> /* has the malloc prototype */
#include <stdio.h>

typedef struct pqnode
{
	int element;
	int priority;
	struct pqnode * next;   
}pqnode;


typedef struct linkedlists
{
	int max_size;
	struct pqnode * headnode;
}linkedlists;


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
	//char filetype[] = ".bin";	
	//strncat(filelol,filetype,4);

	FILE * pFile = fopen(filename, "wb");
	
	
	if (pFile != NULL)
	{
		pqnode * Current = linkedlist->headnode;
		pqnode * holdnext = NULL;

		fseek(pFile, 0, SEEK_END);
		fwrite(linkedlist, sizeof(linkedlist), 1, pFile);

		while(Current != NULL)
		{
			holdnext = Current->next;
			Current->next = NULL;

			fseek(pFile, 0, SEEK_END);
			fwrite(Current, sizeof(pqnode), 0, pFile);

			printf("Writing:%d %d to file\n", Current->element, Current->priority);

			Current->next = holdnext;
			
			Current = Current->next;
			
			holdnext = NULL;

		}
		fclose(pFile);


	}
	else
		printf("Error Writing/n");		
}



linkedlists * load(char filename[])
{
	FILE * pFile = fopen(filename, "rb");
	linkedlists * linkedlist = NULL;
	//pqnode * node = NULL;	

	if(pFile != NULL)
	{
		linkedlist = (linkedlists *) malloc(sizeof(linkedlists));
		fseek(pFile, 0, SEEK_SET);
		int size = fread(linkedlist, sizeof(linkedlist), 1, pFile);
		printf("size of elements read %d\n", size);
		fclose(pFile); 
	}
	else
		printf("Error with read");

	return linkedlist;
}
		




int main()
{
   
	linkedlists * linkedlist1 = create_q(25);
	
	
	enqueue(linkedlist1,10,11);
	enqueue(linkedlist1,20,21);
	enqueue(linkedlist1,30,31);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,51);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,61);
	enqueue(linkedlist1,40,41);
   
	pqnode * Qcur;
   	
	pqnode * Queue1 = linkedlist1->headnode;
	Qcur = Queue1;

	printf("\nEnqueued:\n\tElement\tPriority\n\n");
	while(Qcur != NULL)
	{
		printf("\t%d\t%d\n", Qcur->element, Qcur->priority);
		Qcur = Qcur->next;
	}

	printf("\n\nPeek: %d\t%d\n", peek(linkedlist1)->element, peek(linkedlist1)->priority);

	dequeue(linkedlist1);
	Qcur = Queue1;

	printf("\nDequeue:\n\tElement\tPriority\n\n");
	while(Qcur != NULL)
	{
		printf("\t%d\t%d\n", Qcur->element, Qcur->priority);
		Qcur = Qcur->next;
	}

	store(linkedlist1, "thisfile.bin");
	linkedlists * qu1 = load("thisfile.bin");

	printf("%d %d", qu1->max_size, qu1->headnode->element);

	


  
	return 0;
}
