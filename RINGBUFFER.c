#include <stdbool.h>
#include <string.h> /*has the strcpy prototype*/
#include <stdlib.h> /* has the malloc prototype */
#include <stdio.h>
#include "RINGBUFFER.h"



RingBuffer * create_qR(int max_size)
{
	//using calloc to create an array of structs
	RingBuffer * ringbuffer = calloc(1, sizeof(RingBuffer));
	ringbuffer->max_size = max_size+1;//add one because one of the elements is not used
	ringbuffer->start = 0;
	ringbuffer->end = 0;
	ringbuffer->elems = calloc(ringbuffer->max_size, sizeof(Element));
	
	return ringbuffer;
	
}


void enqueueR(RingBuffer * rb, int x, int p)
{
	rb->elems[rb->end].elem = x;
	rb->elems[rb->end].priority = p;
	rb->end = (rb->end + 1) % rb->max_size;//iterate end indicator by one
	if (rb->end == rb->start)
		rb->start = (rb->start + 1) % rb->max_size;//iterate start indicator by one (modulus to stop from exceeding max size)

	sortR(rb);

}

void sortR(RingBuffer * rb)
{	//create temporary copy to sort
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

		rb->elems[indexmemory] = empty;
		
		rbnew[(rb->start+i) % rb->max_size] = *temp;
	}

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
{	//iterating start by one to change start location
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
	rbnew->max_size = rb1->max_size + rb2->max_size - 1; //adding two queues together leaves two unused elements, one is removed
	rbnew->start = 0;
	rbnew->end = 0;
	rbnew->elems = calloc(rbnew->max_size, sizeof(Element));
	
	int i;
	for(i = 0; i < sizeR(rb1); i++)//first write to new queue from queue1
	{
		rbnew->elems[i] = rb1->elems[(rb1->start + i) % rb1->max_size];
		rbnew->end = (rbnew->end + 1) % rbnew->max_size;
	}

	for(i = 0; i < sizeR(rb2); i++)//write to new queue from queue2
	{	
		rbnew->elems[(sizeR(rb1) + i) % rb2->max_size] = rb2->elems[(rb2->start + i) % rb2->max_size];
		rbnew->end = (rbnew->end + 1) % rbnew->max_size;
	}

	sortR(rbnew);//new queue is sorted
	

	return rbnew;
}


void clearR(RingBuffer * rb)
{
	rb->start = 0;
	rb->end = 0;
}


void storeR(RingBuffer * rb, char * filename)
{	//frwite as a whole due to no pointers present
	char filetype[6] = "rb.bin";
	char filename2[20] = "\0";
	strncpy(filename2, filename, strlen(filename));	
	strncat(filename2,filetype,6);
	printf("%s", filename2);

	FILE * pFile = fopen(filename2, "wb");
	
	
	if (pFile != NULL)
	{

		fseek(pFile, 0, SEEK_END);
		fwrite(rb, sizeof(RingBuffer), 1, pFile);

		printf("\nWrite Successful\n");
		fclose(pFile);
	}
	else
		printf("Error Writing/n");		
}



RingBuffer * loadR(char * filename)
{	//same process as store but using also using calloc

	char filetype[6] = "rb.bin";
	char filename2[20] = "\0";
	strncpy(filename2, filename, strlen(filename));	
	strncat(filename2,filetype,6);
	printf("%s", filename2);

	FILE * pFile = fopen(filename2, "rb");
	RingBuffer * rb;
		

	if(pFile != NULL)
	{
		rb = calloc(1, sizeof(RingBuffer));
		fseek(pFile, 0, SEEK_SET);
		fread(rb, sizeof(RingBuffer), 1, pFile);

		printf("\nRead successful\n");
		fclose(pFile);
	}
	else
		printf("Error with read");

	return rb;
}
		

