#include <stdbool.h>
#include <string.h> /*has the strcpy prototype*/
#include <stdlib.h> /* has the malloc prototype */
#include <stdio.h>
#include "RINGBUFFER.h"



RingBuffer * create_qR(int max_size)
{

	RingBuffer * ringbuffer = calloc(1, sizeof(RingBuffer));
	ringbuffer->max_size = max_size+1;
	ringbuffer->start = 0;
	ringbuffer->end = 0;
	ringbuffer->elems = calloc(ringbuffer->max_size, sizeof(Element));
	
	return ringbuffer;
	
}


void enqueueR(RingBuffer * rb, int x, int p)
{
	rb->elems[rb->end].elem = x;
	rb->elems[rb->end].priority = p;
	rb->end = (rb->end + 1) % rb->max_size;
	if (rb->end == rb->start)
		rb->start = (rb->start + 1) % rb->max_size;


	sortR(rb);

}

void sortR(RingBuffer * rb)
{

//Selection Sort 

	Element * temp = (Element *) malloc(sizeof(Element));
	Element * rbnew = calloc(rb->max_size, sizeof(Element));
	Element empty = {.elem = 0, .priority = 0};
	int indexmemory;
	int i;
	int j;

	for(i = 0; i < sizeR(rb); i++)
	{
		*temp = rb->elems[rb->start];
		indexmemory = rb->start;
		for(j = 1; j < sizeR(rb); j++)
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
	//for(i = 0; i < sizeR(rb); i++)
	//{
	//	rb->elems[rb->start+i] = rbnew[rb->start+i];
	//	printf("here: %d %d", rbnew[rb->start+i].elem, rbnew[rb->start+i].priority);
		
	//}
	memcpy(rb->elems, rbnew, sizeof(Element)*rb->max_size);

	free(rbnew);
}

int sizeR(RingBuffer * rb)
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


void dequeueR(RingBuffer * rb)
{
	if(rb->start % rb->max_size != rb->end % rb->max_size)
		rb->start++;
	else
		printf("\nQueue is empty\n");
}


Element peekR(RingBuffer * rb)
{
	return rb->elems[rb->start];
}


bool is_emptyR(RingBuffer * rb)
{
	if(rb->start == rb->end)
		return true;
	else	
		return false;
}





RingBuffer * mergeR(RingBuffer * rb1, RingBuffer * rb2)
{
	RingBuffer * rbnew = calloc(1, sizeof(RingBuffer));
	rbnew->max_size = rb1->max_size + rb2->max_size - 1;
	rbnew->start = 0;
	rbnew->end = 0;
	rbnew->elems = calloc(rbnew->max_size, sizeof(Element));
	
	int i;
	for(i = 0; i < sizeR(rb1); i++)
	{
		rbnew->elems[i] = rb1->elems[(rb1->start + i) % rb1->max_size];
		rbnew->end = (rbnew->end + 1) % rbnew->max_size;
	}

	for(i = 0; i < sizeR(rb2); i++)
	{	
		rbnew->elems[(sizeR(rb1) + i) % rb2->max_size] = rb2->elems[(rb2->start + i) % rb2->max_size];
		rbnew->end = (rbnew->end + 1) % rbnew->max_size;
	}

	//sortR(rbnew);
	

	return rbnew;
}


void clearR(RingBuffer * rb)
{
	rb->start = 0;
	rb->end = 0;
}


void storeR(RingBuffer * rb, char * filename)
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



RingBuffer * loadR(char filename[])
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
		

