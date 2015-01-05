#ifndef _LINKEDLIST_PRIORITYQUEUE_h
#define _LINKEDLIST_PRIORITYQUEUE_h
#include <stdbool.h>

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


linkedlists * create_q(int max_size);

void enqueue(linkedlists * linkedlist, int x, int p);

void dequeue(linkedlists * linkedlist);

pqnode * peek(linkedlists * linkedlist);

bool is_empty(linkedlists * linkedlist);

int size(linkedlists * linkedlist);

linkedlists * merge(linkedlists *linkedlistQ, linkedlists* linkedlistR);

void clear(linkedlists * linkedlist);

void store(linkedlists * linkedlist, char * filename);

linkedlists * load(char * filename);

#endif
