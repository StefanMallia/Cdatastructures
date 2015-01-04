#include <stdio.h>
#include "RINGBUFFER.h"


int main()
{   
	RingBuffer * ring1 = create_qR(4);


	enqueueR(ring1, 1, 71);
	enqueueR(ring1, 2, 71);
	enqueueR(ring1, 3, 71);
	enqueueR(ring1, 4, 71);
	enqueueR(ring1, 5, 100);


	enqueueR(ring1, 10, 71);
	enqueueR(ring1, 15, 61);
	enqueueR(ring1, 16, 11);
	enqueueR(ring1, 12, 21);
	enqueueR(ring1, 62, 31);
	enqueueR(ring1, 24, 61);
	enqueueR(ring1, 77, 65);
	enqueueR(ring1, 24, 616);
	enqueueR(ring1, 36, 67);
	enqueueR(ring1, 23, 81);
	enqueueR(ring1, 27, 41);
	enqueueR(ring1, 64, 61);
	enqueueR(ring1, 54, 21);

	printf("Size of this queue: %d", sizeR(ring1));


	RingBuffer * ring2 = create_qR(4);

	enqueueR(ring2, 5, 100);
	enqueueR(ring2, 10, 71);
	enqueueR(ring2, 15, 61);




   	
	Element * Queue1 = ring1->elems;
	int i = 0;

	printf("\npeek ring 1: element: %d\tpriority: %d\n", peekR(ring1).elem, peekR(ring1).priority);
	
	printf("\nEnqueuedring 1:\n\tElement\tPriority\n\n");
	while(i<sizeR(ring1))
	{
		int position = (ring1->start+i) % ring1->max_size;
		printf("\t%d\t%d\n", Queue1[position].elem, Queue1[position].priority);
		i++;
	}

	Element * Queue2 = ring2->elems;
	i = 0;

	printf("\npeek ring 2: element: %d\tpriority: %d\n", peekR(ring2).elem, peekR(ring2).priority);
	
	printf("\nEnqueued ring 2:\n\tElement\tPriority\n\n");
	while(i<sizeR(ring2))
	{
		int position = (ring2->start+i) % ring2->max_size;
		printf("\t%d\t%d\n", Queue2[position].elem, Queue2[position].priority);
		i++;
	}

	RingBuffer * ring3 = mergeR(ring1, ring2);






	Element * Queue3 = ring3->elems;
	i = 0;

	printf("\npeek ring 3: element: %d\tpriority: %d\n", peekR(ring3).elem, peekR(ring3).priority);
	
	printf("\nEnqueued ring 3:\n\tElement\tPriority\n\n");
	while(i<sizeR(ring3))
	{
		int position = (ring3->start+i) % ring3->max_size;
		printf("\t%d\t%d\n", Queue3[position].elem, Queue3[position].priority);
		i++;
	}













		dequeueR(ring1);dequeueR(ring1);	dequeueR(ring1);	dequeueR(ring1); dequeueR(ring1);	
		i = 0;

		printf("\nEnqueued ring 1:\n\tElement\tPriority\n\n");
	while(i<sizeR(ring1))
	{
		int position = (ring1->start+i) % ring1->max_size;
		printf("\t%d\t%d\n", Queue1[position].elem, Queue1[position].priority);
		i++;
	}

	storeR(ring1, "ring.bin");
	RingBuffer * ring4 = loadR("ring.bin");


	Element * Queue4 = ring4->elems;
	i = 0;

	printf("\npeek ring 4: element: %d\tpriority: %d\n", peekR(ring4).elem, peekR(ring4).priority);
	
	printf("\nEnqueued ring 4:\n\tElement\tPriority\n\n");
	while(i<sizeR(ring4))
	{
		int position = (ring4->start+i) % ring4->max_size;
		printf("\t%d\t%d\n", Queue4[position].elem, Queue4[position].priority);
		i++;
	}



	return 0;
}
