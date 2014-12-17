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

	pqnode * Qhead;


	Qhead = (pqnode *) malloc(sizeof(pqnode));
	Qhead->next = NULL;
   

	linkedlists * linkedlist = (linkedlists *)malloc(sizeof(linkedlists));
	linkedlist->max_size = max_size;
	linkedlist->headnode = Qhead;




	return linkedlist;


}


void enqueue(linkedlists * linkedlist, int x, int p)
{


	pqnode * current;

	current = linkedlist->headnode;
	int max_size = linkedlist->max_size;
	int i = 0;

	for(i=0; i<max_size && current->next != NULL; i++)
		current = current->next;
		


	current->element = x;
	current->priority = p;

	current->next = (pqnode *) malloc(sizeof(pqnode));


}

void dequeue(linkedlists * linkedlist)
{
/*FIFO*/

	pqnode * current;
	pqnode * prev;
	
	current = linkedlist->headnode;
	int temppriority = -1;   

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
   

	if(current->priority == 0 && current->next == NULL)
		return true;
	else	
		return false;
}


int size(linkedlists * linkedlist)
{
	pqnode * current;
	current = linkedlist->headnode;
	int count = 0;
	while(current->next != NULL)
	{
		count++;
		current=current->next;
	}
	return count;
}

void clear(pqnode * obj)
{
	if(obj)
		free(obj);
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
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,61);
	enqueue(linkedlist1,40,41);
   
	pqnode * Qcur;
   	
	pqnode * Queue1 = linkedlist1->headnode;
	Qcur = Queue1;

	printf("\nEnqueued:\n\tElement\tPriority\n\n");
	while(Qcur->next != NULL)
	{
		printf("\t%d\t%d\n", Qcur->element, Qcur->priority);
		Qcur = Qcur->next;
	}

	printf("\n\nPeek: %d\t%d\n", peek(linkedlist1)->element, peek(linkedlist1)->priority);

	dequeue(linkedlist1);
	Qcur = Queue1;

	printf("\nDequeue:\n\tElement\tPriority\n\n");
	while(Qcur->next != NULL)
	{
		printf("\t%d\t%d\n", Qcur->element, Qcur->priority);
		Qcur = Qcur->next;
	}

	


  
	return 0;
}
