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


struct pqnode * create_q(int max_size)
{
	
	struct pqnode * Qhead = NULL;
	struct pqnode * Qprev, * Qcurrent;

	int i=0;
	for(i=0; i<max_size; i++)
	{
		Qcurrent = (struct pqnode *) malloc(sizeof(struct pqnode));
		if (Qhead == NULL) /*first structure*/
			Qhead = Qcurrent;
		else
			Qprev->next = Qcurrent;
			
		
		Qcurrent->next = NULL;
		Qprev = Qcurrent;
	}



	return Qhead;


}


void enqueue(struct pqnode * Queuehead, int x, int p)
{
	struct pqnode * current;
	current = Queuehead->next;

	while(current->next != NULL)
		current = current->next;


	if(current->next == NULL)
	{	
		current->element = x;
		current->priority = p;

	}

}


void destroy(struct pqnode * obj)
{
    if(obj)
        free(obj);
}







int main()
{
	
	struct pqnode * Queue1 = create_q(20);
	enqueue(Queue1,10,11);


	struct pqnode * Qcur;
	
	Qcur = Queue1;

	while(Qcur->next != NULL)
	{
		Qcur = Qcur->next;
		printf("	%d %d\n", Qcur->element, Qcur->priority);
	}


	
	


	return 0;
}
