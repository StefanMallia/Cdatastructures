#ifndef _PQUEUE_H_
#define _PQUEUE_H_
#include <stdbool.h>

struct pqnode 
{
	int element;
	int priority;
	struct pqnode * next;
	
	
} Pqnode;

struct priority_q
{
	Pqnode * front;
	Pqnode * rear;
	int elements;
} Priority_q






struct priority_q* create_q(int max_size)
{
	
	


	struct priority_q * Q = (struct priority_q *)malloc(sizeof(struct priority_q) * max_size);
	

	return Q;


}


void enqueue(struct priority_q* Q, int x, int p)
{
	int index = sizeof(Q.element);	
	

	Q[index].element = x;
	Q[index].priority = p;

	

}


void destroy(struct priority_q* obj)
{
    if(obj)
        free(obj);
}







int main()
{
	
	struct priority_q *Queue = create_q(10);
	printf("%lu\n", sizeof(Q));
	enqueue(Queue,10,11);
	enqueue(Queue,20,21);
	enqueue(Queue,30,31);

	printf("%d %d %d %d %d %d %lu\n", Queue[0].element, Queue[0].priority, Queue[1].element, Queue[1].priority, Queue[2].element, Queue[2].priority, sizeof(Queue)/sizeof(Queue[0]));
	
	destroy(Queue);


	return 0;
}
