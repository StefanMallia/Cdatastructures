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
	int i = rb->start;
	int j = rb->start+1;
	int indexstore;

	while(i % rb->max_size != rb->end % rb->max_size)
	{
		*temp = rb->elems[i];
		indexstore = i;
		while(j % rb->max_size != rb->end % rb->max_size)
		{
			if(rb->elems[j].priority > temp->priority)
			{
				*temp = rb->elems[j];
				indexstore = j;
			}
			j = (j+1) % rb->max_size;
		}
		rb->elems[indexstore] = rb->elems[i];
		rb->elems[i] = *temp;
		
		i = (i + 1) % rb->max_size;
		j = (i + 1) % rb->max_size;

	}
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

/*
void dequeue(linkedlists * linkedlist)
{


	rbnode * current;
	rbnode * prev;
	
	current = linkedlist->headnode;
	int temppriority = 0;   

	while(current != NULL)
	{
		if(current->priority > temppriority)
			temppriority = current->priority;
					
	
		current = current->next;

	}
   
	current = linkedlist->headnode;
	
	while(current->priority != temppriority && current != NULL)
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


rbnode * peek(linkedlists * linkedlist)
{

// mostly copied from dequeue 

	rbnode * current;

	current = linkedlist->headnode;
	int temppriority = 0;   
   
	while(current != NULL)
	{
		if(current->priority > temppriority)
			temppriority = current->priority;
       
		current = current->next;
	}

	current = linkedlist->headnode;

	while(temppriority != current->priority && current != NULL)
		current=current->next;
		

	if(temppriority == current->priority)
	{
		return current;
	}
	else
		return NULL;
}


bool is_empty(linkedlists * linkedlist)
{
	rbnode * current;
	current = linkedlist->headnode;
   

	if(current == NULL)
		return true;
	else	
		return false;
}





linkedlists * merge(linkedlists *linkedlistQ, linkedlists* linkedlistR)
{
	linkedlistQ->max_size = linkedlistQ->max_size + linkedlistR->max_size;

	rbnode * current = linkedlistQ->headnode;
	
	while(current->next != NULL)
		current = current->next;
	
	current->next = linkedlistR->headnode;
	free(linkedlistR);

	return linkedlistQ;
}


void clear(linkedlists * linkedlist)
{
	rbnode * current = linkedlist->headnode;
	rbnode * prev;

	while(current != NULL)
	{
		prev = current;
		current = current->next;
		free(prev);
	}
}


void store(linkedlists * linkedlist, char * filename)
{
	//char filetype[] = ".bin";	
	//strncat(filelol,filetype,4);

	FILE * pFile = fopen(filename, "wb");
	
	
	if (pFile != NULL)
	{
		rbnode * Current = linkedlist->headnode;
		rbnode * holdnext = NULL;
		
		linkedlist->headnode = NULL;

		fseek(pFile, 0, SEEK_END);
		fwrite(linkedlist, sizeof(linkedlists), 1, pFile);

		linkedlist->headnode = Current;	

		int numnodes = size(linkedlist);
		fseek(pFile, 0, SEEK_END);
		fwrite(&numnodes, sizeof(int), 1, pFile);
 


		while(Current != NULL)
		{
			holdnext = Current->next;
			Current->next = NULL;

			fseek(pFile, 0, SEEK_END);
			fwrite(Current, sizeof(rbnode), 1, pFile);


			Current->next = holdnext;
			
			Current = Current->next;
		}
		fclose(pFile);
	}
	else
		printf("Error Writing/n");		
}



linkedlists * load(char filename[])
{
	FILE * pFile = fopen(filename, "rb");
	linkedlists * linkedlist;
		

	if(pFile != NULL)
	{
		linkedlist = (linkedlists *) malloc(sizeof(linkedlists));
		fseek(pFile, 0, SEEK_SET);
		fread(linkedlist, sizeof(linkedlist), 1, pFile);
				
		int numnodes;
		fseek(pFile, sizeof(linkedlists), SEEK_SET);
		fread(&numnodes, sizeof(int), 1, pFile); 
		
		if(numnodes > 0)
		{
			rbnode * current = NULL;
		
			linkedlist->headnode = (rbnode *) malloc(sizeof(rbnode));
			current = linkedlist->headnode;

			fseek(pFile, sizeof(linkedlists)+sizeof(int), SEEK_SET);
			fread(current, sizeof(rbnode), 1, pFile);
			current->next = NULL; 

			int i;
			for(i = 1; i < numnodes; i++)
			{
				current->next = (rbnode *) malloc(sizeof(rbnode));
				current = current->next;			
			
				fread(current, sizeof(rbnode), 1, pFile);
				
				current->next = NULL;		
			}
		}
		fclose(pFile);
	}
	else
		printf("Error with read");

	return linkedlist;
}
		

*/


int main()
{   
	RingBuffer * ring1 = create_q(3);




	enqueue(ring1, 10, 71);
	enqueue(ring1, 15, 61);
	enqueue(ring1, 16, 11);
	enqueue(ring1, 12, 21);
	enqueue(ring1, 62, 31);
/*	enqueue(ring1, 24, 61);
	enqueue(ring1, 77, 65);
	enqueue(ring1, 24, 616);
	enqueue(ring1, 36, 67);
	enqueue(ring1, 23, 81);
	enqueue(ring1, 27, 41);
	enqueue(ring1, 64, 61);
	enqueue(ring1, 54, 21);
*/
	printf("Size of this queue: %d", size(ring1));

	
	
 

   	
	Element * Queue1 = ring1->elems;
	int i = 0;
	
	printf("\nEnqueued:\n\tElement\tPriority\n\n");
	while(i<size(ring1))
	{
		int position = (ring1->start+i) % ring1->max_size;
		printf("\t%d\t%d\n", Queue1[position].elem, Queue1[position].priority);
		i++;
	}


	


 
	return 0;
}
