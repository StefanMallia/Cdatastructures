//#ifndef _PQUEUE_H_
//#define _PQUEUE_H_
#include <stdbool.h>
#include <string.h> /*has the strcpy prototype*/
#include <stdlib.h> /* has the malloc prototype */
#include <stdio.h>

typedef struct rbnode
{
	int element;
	int priority;
	struct rbnode * next;   
}rbnode;


typedef struct linkedlists
{
	int max_size;
	struct rbnode * headnode;
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
		linkedlist->headnode = (rbnode *) malloc(sizeof(rbnode));
		
		linkedlist->headnode->element = x;
		linkedlist->headnode->priority = p;
		linkedlist->headnode->next = NULL;
	}
	else		
	{
		rbnode * current = linkedlist->headnode;

		int max_size = linkedlist->max_size;
		int i = 2;

		while(current->next != NULL)
		{
			current = current->next;
			i++;
		}
			
			
		if(i <= max_size)
		{
			current->next = (rbnode *) malloc(sizeof(rbnode));			
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

	rbnode * current;
	rbnode * prev;
	
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


rbnode * peek(linkedlists * linkedlist)
{

/* mostly copied from dequeue */

	rbnode * current;

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
	rbnode * current;
	current = linkedlist->headnode;
   

	if(current == NULL)
		return true;
	else	
		return false;
}


int size(linkedlists * linkedlist)
{
	rbnode * current = linkedlist->headnode;
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

	rbnode * current = linkedlistQ->headnode;
	
	while(current->next != NULL)
		current = current->next;
	
	current->next = linkedlistR->headnode;
	free(linkedlistR);

	return linkedlistQ;
}


void clear(linkedlists * linkedlist)
{
	rbnode * current = linkedlist->headnode;
	rbnode * prev;

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
		rbnode * Current = linkedlist->headnode;
		rbnode * holdnext = NULL;
		
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
			fwrite(Current, sizeof(rbnode), 1, pFile);


			Current->next = holdnext;
			
			Current = Current->next;
		}
		fclose(pFile);
	}
	else
		printf("Error Writing/n");		
}



linkedlists * load(char filename[])
{
	FILE * pFile = fopen(filename, "rb");
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
			rbnode * current = NULL;
		
			linkedlist->headnode = (rbnode *) malloc(sizeof(rbnode));
			current = linkedlist->headnode;

			fseek(pFile, sizeof(linkedlists)+sizeof(int), SEEK_SET);
			fread(current, sizeof(rbnode), 1, pFile);
			current->next = NULL; 

			int i;
			for(i = 1; i < numnodes; i++)
			{
				current->next = (rbnode *) malloc(sizeof(rbnode));
				current = current->next;			
			
				fread(current, sizeof(rbnode), 1, pFile);
				
				current->next = NULL;		
			}
		}
		fclose(pFile);
	}
	else
		printf("Error with read");

	return linkedlist;
}
		




int main()
{   
	linkedlists * linkedlist1 = create_q(20);	
	
	enqueue(linkedlist1,10,11);
	enqueue(linkedlist1,20,21);
	enqueue(linkedlist1,30,31);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,51);
	enqueue(linkedlist1,40,100);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,61);
	enqueue(linkedlist1,40,41);
   
	rbnode * Qcur;
   	
	rbnode * Queue1 = linkedlist1->headnode;
	Qcur = Queue1;
	
	printf("\nEnqueued:\n\tElement\tPriority\n\n");
	while(Qcur != NULL)
	{
		printf("\t%d\t%d\n", Qcur->element, Qcur->priority);
		Qcur = Qcur->next;
	}

	printf("\n\nPeek: %d\t%d\n", peek(linkedlist1)->element, peek(linkedlist1)->priority);
printf("\n\nSize: %d\n", size(linkedlist1));

	//dequeue(linkedlist1);
	Qcur = Queue1;

	printf("\nDequeue:\n\tElement\tPriority\n\n");
	while(Qcur != NULL)
	{
		printf("\t%d\t%d\n", Qcur->element, Qcur->priority);
		Qcur = Qcur->next;
	}

	store(linkedlist1, "thisfile.bin");
	linkedlists * qu1 = load("thisfile.bin");

	rbnode * Queue2 = qu1->headnode;
	Qcur = Queue2;
	
	printf("\nMax size: %d\tPeek: %d\t%d\n", qu1->max_size, peek(qu1)->element, peek(qu1)->priority);
	printf("Number of elements: %d\n", size(qu1));
	printf("\nEnqueued in loaded queue:\n\tElement\tPriority\n\n");
	while(Qcur != NULL)
	{
		printf("\t%d\t%d\n", Qcur->element, Qcur->priority);
		Qcur = Qcur->next;
	}

	


  
	return 0;
}
