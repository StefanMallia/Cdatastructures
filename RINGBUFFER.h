#ifndef _RINGBUFFER_PRIORITYQUEUE_h
#define _RINGBUFFER_PRIORITYQUEUE_h

#include <stdbool.h>



typedef struct//element struct
{
	int elem;
	int priority;
}
Element;

typedef struct//struct that contains elements
{
	int max_size;
	int start;
	int end;
	Element * elems;
}
RingBuffer;

void sortR(RingBuffer * rb);
int sizeR(RingBuffer * rb);



RingBuffer * create_qR(int max_size);

void enqueueR(RingBuffer * rb, int x, int p);

void sortR(RingBuffer * rb);

int sizeR(RingBuffer * rb);

void dequeueR(RingBuffer * rb);

Element peekR(RingBuffer * rb);

bool is_emptyR(RingBuffer * rb);

RingBuffer * mergeR(RingBuffer * rb1, RingBuffer * rb2);

void clearR(RingBuffer * rb);

void storeR(RingBuffer * rb, char * filename);

RingBuffer * loadR(char filename[]);


#endif
