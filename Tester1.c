#include <stdio.h>
#include "LINKEDLIST.h"

int main()
{   
	linkedlists * linkedlist1 = create_q(100);	
	
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
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,41);
	enqueue(linkedlist1,40,41);
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
printf("\n\nSize: %d\n", size(linkedlist1));

	dequeue(linkedlist1);
	Qcur = Queue1;

	printf("\nDequeued:\n\tElement\tPriority\n\n");
	while(Qcur != NULL)
	{
		printf("\t%d\t%d\n", Qcur->element, Qcur->priority);
		Qcur = Qcur->next;
	}

	store(linkedlist1, "thisfile.bin");
	linkedlists * qu1 = load("thisfile.bin");

	pqnode * Queue2 = qu1->headnode;
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

