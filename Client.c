#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LINKEDLIST.h"
#include "RINGBUFFER.h"

int Lcounter = 0; //a counter of number of existing queues
int Rcounter = 0;


typedef struct
{
	linkedlists * ll;
	char name[20];
}LLarray;

typedef struct
{

	RingBuffer * RB;
	char name[20];
}RBarray;




void appendllqueue(linkedlists * linkedlist, char * queuename, LLarray * Llist);
int accessllqueue(char * queuename, LLarray * Llist);
void appendRBqueue(RingBuffer * linkedlist, char * queuename, RBarray * RBuffer);
int accessRBqueue(char * queuename, RBarray * RBuffer);

int main()
{
	LLarray * Llist = (LLarray *)calloc(5, sizeof(LLarray));
	RBarray * RBuffer = (RBarray *)calloc(5, sizeof(RBarray));
	char ch;
	
	printf("\nWelcome to the queueing application");

	BEGINNING:
	printf("\n\na. Linked List\nb. Ring Buffer\n\n");
	printf("Please make a selection (1 or 2 or enter 'q' to cancel):\n\n");
	
	
	scanf("%c%*c", &ch);
	{

		if('q' == ch)
			return 0;

		switch(ch)
		{
			case 'a':
				goto CASE1;

			case 'b':
				goto CASE2;
		
			default:
				printf("\nThat is not a valid choice\n");
				goto BEGINNING;
		}
	}

	CASE1:
	{
		

	char queuename[20];
	char ch2 = NULL;


		printf("\n\nActions:\n\n");
		printf("a. Create a Linked List Queue\nb. Make an entry into a queue\nc. Dequeue highest priority element\nd. Highest priority element\ne. Check whether queue is empty\nf. Size of queue\ng. Merge two queue's\nh. Clear queue of contents\ni. Store existing queue to file\nj. Load queue from file\n");
		printf("Please make a selection (enter 'q' to cancel):\n\n");

		scanf("%c%*c", &ch2);
		{
			
			if('q' == ch2)
				return 0;

			switch(ch2)
			{
				case 'a':
				{
					printf("\nName of Linked List:\n");
					fgets(queuename, sizeof(queuename), stdin);

					printf("\nMaximum size of Linked List:\n");
					int max_size;
					scanf("%d%*c", &max_size);



					appendllqueue(create_q(max_size), queuename, Llist);
					Lcounter++;

					goto BEGINNING;
				}

				case 'b':
				{
					printf("\nEnter the queue name:\n");
					fgets(queuename, 15, stdin);


					printf("\nEnter an integer element:\n");
					int element;
					scanf("%d%*c", &element);
				
					printf("\nEnter an integer priority:\n");
					int priority;
					scanf("%d%*c", &priority);
					if(accessllqueue(queuename, Llist) == -1)
						printf("\nError accessing queue\n");
					
					enqueue(Llist[accessllqueue(queuename, Llist)].ll, element, priority);
				
					goto BEGINNING;
				}

				case 'c':
				{
					printf("\nName of Linked List:\n");

					fgets(queuename, 15, stdin);

					dequeue(Llist[accessllqueue(queuename, Llist)].ll);

					goto BEGINNING;
				}

				case 'd':
				{
					printf("\nName of Linked List:\n");

					fgets(queuename, 15, stdin);

					printf("\nHighest priority element is: %d\nwith a priority of: %d", peek(Llist[accessllqueue(queuename, Llist)].ll)->element, peek(Llist[accessllqueue(queuename, Llist)].ll)->priority);

					goto BEGINNING;
				}

				case 'e':
				{
					printf("\nName of Linked List:\n");

					fgets(queuename, 15, stdin);

					if(is_empty(Llist[accessllqueue(queuename, Llist)].ll))
						printf("Queue is empty\n");
					else
						printf("Queue is not empty\n");
				
					goto BEGINNING;
				}
				case 'f':
				{
					printf("\nName of Linked List:\n");

					fgets(queuename, 15, stdin);


					printf("Size of queue is %d\n",size(Llist[accessllqueue(queuename, Llist)].ll));

					goto BEGINNING;
				}
				case 'g':
				{
					printf("\nName of Linked List 1:\n");
					char queuename1[20];
					fgets(queuename1, 15, stdin);


					printf("\nName of Linked List 2:\n");
					char queuename2[20];
					fgets(queuename2, 15, stdin);

					printf("\nName of new Linked List (note that this does not delete previous two queues):\n");
					char queuename3[20];
					fgets(queuename3, 15, stdin);

					appendllqueue(merge(Llist[accessllqueue(queuename1, Llist)].ll, Llist[accessllqueue(queuename2, Llist)].ll), queuename3, Llist);
					Lcounter++;

					goto BEGINNING;
				}
				case 'h':
				{
					printf("\nName of Linked List:\n");

					fgets(queuename, 15, stdin);

					clear(Llist[accessllqueue(queuename, Llist)].ll);
					Llist[accessllqueue(queuename, Llist)].ll = NULL;
					strncpy(Llist[accessllqueue(queuename, Llist)].name, "\0", 20);
					

					goto BEGINNING;
				}
				case 'i':
				{
					printf("\nName of Linked List:\n");

					fgets(queuename, 15, stdin);

					store(Llist[accessllqueue(queuename, Llist)].ll, queuename);

				

					goto BEGINNING;
				}
				case 'j':
				{
					printf("\nName of Linked List:\n");

					fgets(queuename, 15, stdin);


					appendllqueue(load(queuename), queuename, Llist);
					Lcounter++;
				

					goto BEGINNING;
				}
				default:
					printf("\nThat is not a valid choice\n");
					goto BEGINNING;
			}



		
		}
	return 0;
	}

	CASE2:
	{
		

	char queuename[20];
	char ch2 = NULL;


		printf("\n\nActions:\n\n");
		printf("a. Create a RingBuffer Queue\nb. Make an entry into a queue\nc. Dequeue highest priority element\nd. Highest priority element\ne. Check whether queue is empty\nf. Size of queue\ng. Merge two queue's\nh. Clear queue of contents\ni. Store existing queue to file\nj. Load queue from file\n");
		printf("Please make a selection (enter 'q' to cancel):\n\n");

		scanf("%c%*c", &ch2);
		{
			
			if('q' == ch2)
				return 0;

			switch(ch2)
			{
				case 'a':
				{
					printf("\nName of Ring Buffer:\n");
					fgets(queuename, sizeof(queuename), stdin);

					printf("\nMaximum size of Ring Buffer:\n");
					int max_size;
					scanf("%d%*c", &max_size);



					appendRBqueue(create_qR(max_size), queuename, RBuffer);
					Rcounter++;

					goto BEGINNING;
				}

				case 'b':
				{
					printf("\nEnter the queue name:\n");
					fgets(queuename, 15, stdin);


					printf("\nEnter an integer element:\n");
					int element;
					scanf("%d%*c", &element);
				
					printf("\nEnter an integer priority:\n");
					int priority;
					scanf("%d%*c", &priority);
					if(accessRBqueue(queuename, RBuffer) == -1)
						printf("\nError accessing queue\n");
					

					enqueueR(RBuffer[accessRBqueue(queuename, RBuffer)].RB, element, priority);

					goto BEGINNING;
				}

				case 'c':
				{
					printf("\nName of Ring Buffer:\n");

					fgets(queuename, 15, stdin);

					dequeueR(RBuffer[accessRBqueue(queuename, RBuffer)].RB);

					goto BEGINNING;
				}

				case 'd':
				{
					printf("\nName of Ring Buffer:\n");

					fgets(queuename, 15, stdin);

					printf("\nHighest priority element is: %d\nwith a priority of: %d", peekR(RBuffer[accessRBqueue(queuename, RBuffer)].RB).elem, peekR(RBuffer[accessRBqueue(queuename, RBuffer)].RB).priority);

					goto BEGINNING;
				}

				case 'e':
				{
					printf("\nName of Ring Buffer:\n");

					fgets(queuename, 15, stdin);

					if(is_emptyR(RBuffer[accessRBqueue(queuename, RBuffer)].RB))
						printf("Queue is empty\n");
					else
						printf("Queue is not empty\n");
				
					goto BEGINNING;
				}
				case 'f':
				{
					printf("\nName of Ring Buffer:\n");

					fgets(queuename, 15, stdin);

					printf("Size of queue is %d\n",sizeR(RBuffer[accessRBqueue(queuename, RBuffer)].RB));

					goto BEGINNING;
				}
				case 'g':
				{
					printf("\nName of Ring Buffer 1:\n");
					char queuename1[20];
					fgets(queuename1, 15, stdin);


					printf("\nName of Ring Buffer 2:\n");
					char queuename2[20];
					fgets(queuename2, 15, stdin);

					printf("\nName of new Ring Buffer (note that this does not delete previous queues):\n");
					char queuename3[20];
					fgets(queuename3, 15, stdin);


					
					appendRBqueue(mergeR(RBuffer[accessRBqueue(queuename1, RBuffer)].RB, RBuffer[accessRBqueue(queuename2, RBuffer)].RB), queuename3, RBuffer);

					Rcounter++;
					goto BEGINNING;
				}
				case 'h':
				{
					printf("\nName of Ring Buffer:\n");

					fgets(queuename, 15, stdin);

					clearR(RBuffer[accessRBqueue(queuename, RBuffer)].RB);
					RBuffer[accessRBqueue(queuename, RBuffer)].RB = NULL;
					strncpy(RBuffer[accessRBqueue(queuename, RBuffer)].name, queuename, 20);
				

					goto BEGINNING;
				}
				case 'i':
				{
					printf("\nName of Ring Buffer:\n");

					fgets(queuename, 15, stdin);

					storeR(RBuffer[accessRBqueue(queuename, RBuffer)].RB, queuename);
				

					goto BEGINNING;
				}
				case 'j':
				{
					printf("\nName of Ring Buffer:\n");

					fgets(queuename, 15, stdin);


					appendRBqueue(loadR(queuename), queuename, RBuffer);
					Lcounter++;
				

					goto BEGINNING;
				}
				default:
					printf("\nThat is not a valid choice\n");
					goto BEGINNING;
			}

		}
	return 0;
	}



}


void appendllqueue(linkedlists * linkedlist, char * queuename, LLarray * Llist)
{
	if(accessllqueue(queuename, Llist) == -1)
	{
		strncpy(Llist[Lcounter].name, queuename, 20);

		Llist[Lcounter].ll = linkedlist;
		printf("\nYour chosen name is: %s", Llist[Lcounter].name);

	}
	else
		printf("\nThis name already exists");
		
}


int accessllqueue(char * queuename, LLarray * Llist)
{
	int accesscount=0;
	while(accesscount != Lcounter)
	{
		//printf("\nLlist[%d].name: %s\nqueuename: %s\nlcounter: %d", accesscount, Llist[accesscount].name, queuename, Lcounter);
		if(strcmp(Llist[accesscount].name, queuename) == 0)
			return accesscount;
		accesscount++;
	}
	
	
	return -1;
}

void appendRBqueue(RingBuffer * RBqueue, char * queuename, RBarray * RBuffer)
{
	if(accessRBqueue(queuename, RBuffer) == -1)
	{

		strncpy(RBuffer[Rcounter].name, queuename, 20);


		RBuffer[Rcounter].RB = RBqueue;
		printf("\nYour chosen name is: %s", RBuffer[Rcounter].name);

	}
	else
		printf("\nThis name already exists");
		
}


int accessRBqueue(char * queuename, RBarray * RBuffer)
{
	int accesscount=0;
	while(accesscount != Rcounter)
	{
		if(strcmp(RBuffer[accesscount].name, queuename) == 0)
			return accesscount;
		accesscount++;
	}
	
	
	return -1;
}




	
