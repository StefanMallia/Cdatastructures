//#ifndef _PQUEUE_H_
//#define _PQUEUE_H_
#include <stdbool.h>
#include <string.h> /*has the strcpy prototype*/
#include <stdlib.h> /* has the malloc prototype */
#include <stdio.h>

typedef struct
{
	int elem;
	int priority;
}
Element;

typedef struct
{
	int max_size;
	int start;
	int end;
	Element * elems;
}
RingBuffer;

void sort(RingBuffer * rb);
int size(RingBuffer * rb);



RingBuffer * create_q(int max_size)
{

	RingBuffer * ringbuffer = calloc(1, sizeof(RingBuffer));
	ringbuffer->max_size = max_size+1;
	ringbuffer->start = 0;
	ringbuffer->end = 0;
	ringbuffer->elems = calloc(ringbuffer->max_size, sizeof(Element));
	
	return ringbuffer;
	
}


void enqueue(RingBuffer * rb, int x, int p)
{
	rb->elems[rb->end].elem = x;
	rb->elems[rb->end].priority = p;
	rb->end = (rb->end + 1) % rb->max_size;
	if (rb->end == rb->start)
		rb->start = (rb->start + 1) % rb->max_size;


	sort(rb);

}

void sort(RingBuffer * rb)
{

//Selection Sort 

	Element * temp = (Element *) malloc(sizeof(Element));
	Element * rbnew = calloc(rb->max_size, sizeof(Element));
	Element empty = {.elem = 0, .priority = 0};
	int indexmemory;
	int i;
	int j;

	for(i = 0; i < size(rb); i++)
	{
		*temp = rb->elems[rb->start];
		indexmemory = rb->start;
		for(j = 1; j < size(rb); j++)
		{
			if(rb->elems[(rb->start + j) % rb->max_size].priority > temp->priority)
			{
				*temp = rb->elems[(rb->start + j) % rb->max_size];
				indexmemory = (rb->start + j) % rb->max_size;
			}
		}
		//printf("rb->elem[indexmemory] = %d %d\n", rb->elems[indexmemory].priority, rb->elems[indexmemory].elem);
		rb->elems[indexmemory] = empty;
		

		//printf("rb->elem[indexmemory] = %d %d\n", rb->elems[indexmemory].priority, rb->elems[indexmemory].elem);
		rbnew[(rb->start+i) % rb->max_size] = *temp;
	}
	//free(rb->elems);
	//rb->elems = calloc(rb->max_size, sizeof(Element));
	//for(i = 0; i < size(rb); i++)
	//{
	//	rb->elems[rb->start+i] = rbnew[rb->start+i];
	//	printf("here: %d %d", rbnew[rb->start+i].elem, rbnew[rb->start+i].priority);
		
	//}
	memcpy(rb->elems, rbnew, sizeof(Element)*rb->max_size);

	free(rbnew);
}

int size(RingBuffer * rb)
{
	int count = 0;
	int i = 0;
	while((rb->start+i) %rb->max_size != rb->end)
	{
		i++;
		count++;
	}

	return count;
}


void dequeue(RingBuffer * rb)
{
	if(rb->start % rb->max_size != rb->end % rb->max_size)
		rb->start++;
	else
		printf("\nQueue is empty\n");
}


Element peek(RingBuffer * rb)
{
	return rb->elems[rb->start];
}


bool is_empty(RingBuffer * rb)
{
	if(rb->start == rb->end)
		return true;
	else	
		return false;
}





RingBuffer * merge(RingBuffer * rb1, RingBuffer * rb2)
{
	RingBuffer * rbnew = calloc(1, sizeof(RingBuffer));
	rbnew->max_size = rb1->max_size + rb2->max_size - 1;
	rbnew->start = 0;
	rbnew->end = 0;
	rbnew->elems = calloc(rbnew->max_size, sizeof(Element));
	
	int i;
	for(i = 0; i < size(rb1); i++)
	{
		rbnew->elems[i] = rb1->elems[(rb1->start + i) % rb1->max_size];
		rbnew->end = (rbnew->end + 1) % rbnew->max_size;
	}

	for(i = 0; i < size(rb2); i++)
	{	
		rbnew->elems[(size(rb1) + i) % rb2->max_size] = rb2->elems[(rb2->start + i) % rb2->max_size];
		rbnew->end = (rbnew->end + 1) % rbnew->max_size;
	}

	//sort(rbnew);
	

	return rbnew;
}


void clear(RingBuffer * rb)
{
	rb->start = 0;
	rb->end = 0;
}


void store(RingBuffer * rb, char * filename)
{
	//char filetype[] = ".bin";	
	//strncat(filelol,filetype,4);

	FILE * pFile = fopen(filename, "wb");
	
	
	if (pFile != NULL)
	{

		fseek(pFile, 0, SEEK_END);
		fwrite(rb, sizeof(RingBuffer), 1, pFile);

		fclose(pFile);
	}
	else
		printf("Error Writing/n");		
}



RingBuffer * load(char filename[])
{
	FILE * pFile = fopen(filename, "rb");
	RingBuffer * rb;
		

	if(pFile != NULL)
	{
		rb = calloc(1, sizeof(RingBuffer));
		fseek(pFile, 0, SEEK_SET);
		fread(rb, sizeof(RingBuffer), 1, pFile);

		fclose(pFile);
	}
	else
		printf("Error with read");

	return rb;
}
		


int main()
{   
	RingBuffer * ring1 = create_q(4);


	enqueue(ring1, 1, 71);
	enqueue(ring1, 2, 71);
	enqueue(ring1, 3, 71);
	enqueue(ring1, 4, 71);
	enqueue(ring1, 5, 100);


	enqueue(ring1, 10, 71);
	enqueue(ring1, 15, 61);
/*	enqueue(ring1, 16, 11);
	enqueue(ring1, 12, 21);
	enqueue(ring1, 62, 31);
	enqueue(ring1, 24, 61);
	enqueue(ring1, 77, 65);
	enqueue(ring1, 24, 616);
	enqueue(ring1, 36, 67);
	enqueue(ring1, 23, 81);
	enqueue(ring1, 27, 41);
	enqueue(ring1, 64, 61);
	enqueue(ring1, 54, 21);

	printf("Size of this queue: %d", size(ring1));

*/
	RingBuffer * ring2 = create_q(4);

	enqueue(ring2, 5, 100);
	enqueue(ring2, 10, 71);
	enqueue(ring2, 15, 61);




   	
	Element * Queue1 = ring1->elems;
	int i = 0;

	printf("\npeek ring 1: element: %d\tpriority: %d\n", peek(ring1).elem, peek(ring1).priority);
	
	printf("\nEnqueuedring 1:\n\tElement\tPriority\n\n");
	while(i<size(ring1))
	{
		int position = (ring1->start+i) % ring1->max_size;
		printf("\t%d\t%d\n", Queue1[position].elem, Queue1[position].priority);
		i++;
	}

	Element * Queue2 = ring2->elems;
	i = 0;

	printf("\npeek ring 2: element: %d\tpriority: %d\n", peek(ring2).elem, peek(ring2).priority);
	
	printf("\nEnqueued ring 2:\n\tElement\tPriority\n\n");
	while(i<size(ring2))
	{
		int position = (ring2->start+i) % ring2->max_size;
		printf("\t%d\t%d\n", Queue2[position].elem, Queue2[position].priority);
		i++;
	}

	RingBuffer * ring3 = merge(ring1, ring2);






	Element * Queue3 = ring3->elems;
	i = 0;

	printf("\npeek ring 3: element: %d\tpriority: %d\n", peek(ring3).elem, peek(ring3).priority);
	
	printf("\nEnqueued ring 3:\n\tElement\tPriority\n\n");
	while(i<size(ring3))
	{
		int position = (ring3->start+i) % ring3->max_size;
		printf("\t%d\t%d\n", Queue3[position].elem, Queue3[position].priority);
		i++;
	}











/*

		dequeue(ring1);dequeue(ring1);	dequeue(ring1);	dequeue(ring1); dequeue(ring1);	
		i = 0;

		printf("\nEnqueued ring 1:\n\tElement\tPriority\n\n");
	while(i<size(ring1))
	{
		int position = (ring1->start+i) % ring1->max_size;
		printf("\t%d\t%d\n", Queue1[position].elem, Queue1[position].priority);
		i++;
	}
*/
	store(ring1, "ring.bin");
	RingBuffer * ring4 = load("ring.bin");


	Element * Queue4 = ring4->elems;
	i = 0;

	printf("\npeek ring 4: element: %d\tpriority: %d\n", peek(ring4).elem, peek(ring4).priority);
	
	printf("\nEnqueued ring 4:\n\tElement\tPriority\n\n");
	while(i<size(ring4))
	{
		int position = (ring4->start+i) % ring4->max_size;
		printf("\t%d\t%d\n", Queue4[position].elem, Queue4[position].priority);
		i++;
	}



	return 0;
}
