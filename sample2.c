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


void enqueue(struct pqnode * Queuenode, int x, int p)
{
	while(Queuenode != NULL)
		Queuenode = Queuenode->next;

	if(Queuenode == NULL)
	{
		Queuenode->element = x;
		Queuenode->priority = p;
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
	printf("%lu\n", sizeof(Queue1));
	enqueue(Queue1,10,11);
	enqueue(Queue1,20,21);
	enqueue(Queue1,30,31);
	enqueue(Queue1,40,41);
	enqueue(Queue1,50,51);
	enqueue(Queue1,60,61);


	struct pqnode * Qcur;
	
	Qcur = Queue1;
	if (Queue1 == NULL)
		printf("No data entered");
	printf("%p", Queue1);
	while(Qcur != NULL)
	{
		Qcur = Qcur->next;
	}


	printf("%d %d\n", (*Qcur).element, (*Qcur).priority);
	
	


	return 0;
}
