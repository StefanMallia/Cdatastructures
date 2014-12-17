//#ifndef _PQUEUE_H_
//#define _PQUEUE_H_
#include <stdbool.h>
#include <string.h> /*has the strcpy prototype*/
#include <stdlib.h> /* has the malloc prototype */
#include <stdio.h>




struct pqnode
{
	int element;
	int priority;
	struct pqnode * next;   
   
};


struct linkedlists
{
	int max_size;
	struct pqnode * headnode;

};

struct linkedlists * create_q(int max_size)
{
/* takes max_size as input and creates a linked list with max_size empty arrays

Qhead is set to NULL and Qprev and Qcurrent are just declared without assigning values.

Qcurrent is assigned a memory space and Qhead is assigned Qcurrent

Qcurrent is assigned memory space on a loop of max_size iterations and the
previous element's ->next is assigned Qcurrent.

Returns the first structure Qhead which is only a pointer with no values

*/

	struct pqnode * Qhead;
	struct pqnode * Qelement1;

	Qhead = (struct pqnode*) malloc(sizeof(struct pqnode));
	Qelement1 = (struct pqnode*) malloc(sizeof(struct pqnode));
	Qelement1->next = NULL;
	Qhead = Qelement1;
   

	struct linkedlists * linkedlist = (struct linkedlists *)malloc(sizeof(struct linkedlists));
	linkedlist->max_size = max_size;
	linkedlist->headnode = Qhead;




	return linkedlist;


}


void enqueue(struct pqnode * Queuehead, int x, int p)
{

/* creates current struct so that Queuehead input is not modified

iterates and changes to filled elements defined as those with >0 priority

once an empty element is found the 2nd and 3rd arguments are inputted

x is element and p is priority


*/
	struct pqnode * current;
	current = Queuehead->next;

	while(current->next != NULL)
	current = current->next;

   


	if(current->next == NULL)
	{   

	current->element = x;
	current->priority = p;

	current->next = (struct pqnode*) malloc(sizeof(struct pqnode));
	current = current->next;
	current->next = NULL;

	}

}

void dequeue(struct pqnode * Queuehead)
{

/* current and prev struct are used to preserve Queuehead original pointer value

temppriority is a temporary value that will change every time a larger priority is found.

while loop scans whole linked list, temppriority should end up being assigned the largest priority.

once largest priority is set to temppriority, another while loop will scan the linked list again to search for the highest priority and stops once largest priority is found.

prev->next is set to current->next and current is freed from memory.


*/
	struct pqnode * current;
	struct pqnode * prev;

	current = Queuehead->next;
	int temppriority = 0;   
   
	while(current->next != NULL)
	{
		if(current->priority > temppriority)
			temppriority = current->priority;
       
		current = current->next;
	}
   
	current = Queuehead->next;

	while(temppriority != current->priority || current != NULL)
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


struct pqnode * peek(struct pqnode * Queuehead)
{

/* mostly copied from dequeue */

	struct pqnode * current;

	current = Queuehead->next;
	int temppriority = 0;   
   
	while(current->next != NULL)
	{
		if(current->priority > temppriority)
		temppriority = current->priority;
       
	current = current->next;
	}

	while(temppriority != current->priority || current != NULL)
		{
	current=current->next;
	}   

	if(temppriority == current->priority)
	{
		return current;
	}
	else
		return NULL;
}


int is_empty(struct pqnode * Queuehead)
{
	struct pqnode * current;
	current = Queuehead->next;
   
	while(current->priority == 0)
	{
		if(current->next == NULL)
			return 1;
		current = current->next;
	}
	return 0;
}

void destroy(struct pqnode * obj)
{
	if(obj)
		free(obj);
}







int main()
{
   
	struct pqnode * Queue1 = create_q(20)->headnode;
	enqueue(Queue1,10,11);
	enqueue(Queue1,20,21);
	enqueue(Queue1,30,31);
	enqueue(Queue1,40,41);
	enqueue(Queue1,40,41);
	enqueue(Queue1,40,51);
	enqueue(Queue1,40,41);
	enqueue(Queue1,40,41);
	enqueue(Queue1,40,61);
	enqueue(Queue1,40,41);

   


	struct pqnode * Qcur;
   
	Qcur = Queue1;

	printf("\n\tElement\tPriority\n\n");
	while(Qcur->next != NULL)
	{
		Qcur = Qcur->next;
		printf("\t%d\t%d\n", Qcur->element, Qcur->priority);
	}

	//dequeue(Queue1);


   
	Qcur = Queue1;
	printf("\n\tElement\tPriority\n\n");
	while(Qcur->next != NULL)
	{
		Qcur = Qcur->next;
		printf("\t%d\t%d\n", Qcur->element, Qcur->priority);
	}
   


	return 0;
}
