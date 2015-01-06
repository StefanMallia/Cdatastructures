#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LINKEDLIST.h"
#include "RINGBUFFER.h"


typedef struct LLarray
{
	linkedlists * ll;
	char * name;
	struct LLarray * next;	
}LLarray;

typedef struct RBarray
{
	RingBuffer * RB;
	char * name;
	struct RBarray * next;
}RBarray;


void printqueuesll(LLarray * llheadnode);
char * getstring();
void appendllqueue(linkedlists * linkedlist, char * queuename, LLarray * llheadnode);
LLarray * accessllqueue(char * queuename, LLarray * llheadnode);
void clearllqueue(char * queuename, LLarray * llheadnode);
void appendRBqueue(RingBuffer * RBqueue, char * queuename, RBarray * rbheadnode);
RBarray * accessRBqueue(char * queuename, RBarray * rbheadnode);
void clearrbqueue(char * queuename, RBarray * rbheadnode);



int main()
{
	LLarray * llheadnode = (LLarray *) malloc(sizeof(LLarray));
	llheadnode->ll = NULL;
	llheadnode->name = NULL;
	llheadnode->next = NULL;


	RBarray * rbheadnode = (RBarray *) malloc(sizeof(RBarray));
	rbheadnode->RB = NULL;
	rbheadnode->name = NULL;
	rbheadnode->next = NULL;

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
		

	char * queuename;

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
					queuename = getstring();


					printf("\nMaximum size of Linked List:\n");
					int max_size;
					scanf("%d%*c", &max_size);



					appendllqueue(create_q(max_size), queuename, llheadnode);


					goto BEGINNING;
				}

				case 'b':
				{
					printf("\nEnter the queue name:\n");
					scanf("%s%*c", queuename);


					printf("\nEnter an integer element:\n");
					int element;
					scanf("%d%*c", &element);
				
					printf("\nEnter an integer priority:\n");
					int priority;
					scanf("%d%*c", &priority);
					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						enqueue(accessllqueue(queuename, llheadnode)->ll, element, priority);
				
					goto BEGINNING;
				}

				case 'c':
				{
					printf("\nName of Linked List:\n");

					queuename = getstring();

					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						dequeue(accessllqueue(queuename, llheadnode)->ll);

					goto BEGINNING;
				}

				case 'd':
				{
					printf("\nName of Linked List:\n");

					queuename = getstring();
					printqueuesll(llheadnode);
					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("\nHighest priority element is: %d\nwith a priority of: %d", peek(accessllqueue(queuename, llheadnode)->ll)->element, peek(accessllqueue(queuename, llheadnode)->ll)->priority);

					goto BEGINNING;
				}

				case 'e':
				{
					printf("\nName of Linked List:\n");

					queuename = getstring();
					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
					{
						if(is_empty(accessllqueue(queuename, llheadnode)->ll))
							printf("Queue is empty\n");
						else
							printf("Queue is not empty\n");
					}
					goto BEGINNING;
				}
				case 'f':
				{
					printf("\nName of Linked List:\n");

					queuename = getstring();
					printqueuesll(llheadnode);
					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("Size of queue is %d\n",size(accessllqueue(queuename, llheadnode)->ll));

					goto BEGINNING;
				}
				case 'g':
				{
					printf("\nName of Linked List 1:\n");
					char * queuename1;
					queuename1 = getstring();


					printf("\nName of Linked List 2:\n");
					char * queuename2;
					queuename2 = getstring();

					if((accessllqueue(queuename1, llheadnode) == NULL) || (accessllqueue(queuename2, llheadnode) == NULL))
						printf("\nThis queue does not exist\n");
					else
					{
						printf("\nName of new Linked List (note that this does not delete previous two queues):\n");
						char * queuename3;
						queuename3 = getstring();

						appendllqueue(merge(accessllqueue(queuename1, llheadnode)->ll, accessllqueue(queuename2, llheadnode)->ll), queuename3, llheadnode);

					}
					goto BEGINNING;
				}
				case 'h':
				{
					printf("\nName of Linked List:\n");

					queuename = getstring();
					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
					{
						clear(accessllqueue(queuename, llheadnode)->ll);
						clearllqueue(queuename, llheadnode);
					}

					goto BEGINNING;
				}
				case 'i':
				{
					printf("\nName of Linked List:\n");

					queuename = getstring();
					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						store(accessllqueue(queuename, llheadnode)->ll, queuename);

					goto BEGINNING;
				}
				case 'j':
				{
					printf("\nName of Linked List:\n");
					queuename = getstring();
					
					appendllqueue(load(queuename), queuename, llheadnode);

					printf("-----%s-----", queuename);

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
		

	char * queuename;

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
					queuename = getstring();

					printf("\nMaximum size of Ring Buffer:\n");
					int max_size;
					scanf("%d%*c", &max_size);




					appendRBqueue(create_qR(max_size), queuename, rbheadnode);


					goto BEGINNING;
				}

				case 'b':
				{
					printf("\nEnter the queue name:\n");
					queuename = getstring();


					printf("\nEnter an integer element:\n");
					int element;
					scanf("%d%*c", &element);
				
					printf("\nEnter an integer priority:\n");
					int priority;
					scanf("%d%*c", &priority);
					if(accessRBqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else					
						enqueueR(accessRBqueue(queuename, rbheadnode)->RB, element, priority);

					goto BEGINNING;
				}

				case 'c':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessRBqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						dequeueR(accessRBqueue(queuename, rbheadnode)->RB);

					goto BEGINNING;
				}

				case 'd':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessRBqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("\nHighest priority element is: %d\nwith a priority of: %d", peekR(accessRBqueue(queuename, rbheadnode)->RB).elem, peekR(accessRBqueue(queuename, rbheadnode)->RB).priority);

					goto BEGINNING;
				}

				case 'e':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessRBqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
					{
						if(is_emptyR(accessRBqueue(queuename, rbheadnode)->RB))
							printf("Queue is empty\n");
						else
							printf("Queue is not empty\n");
					}
				
					goto BEGINNING;
				}
				case 'f':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessRBqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("Size of queue is %d\n",sizeR(accessRBqueue(queuename, rbheadnode)->RB));

					goto BEGINNING;
				}
				case 'g':
				{

					printf("\nName of Ring Buffer 1:\n");
					char * queuename1;
					queuename1 = getstring();


					printf("\nName of Ring Buffer 2:\n");
					char * queuename2;
					queuename2 = getstring();
					if(accessRBqueue(queuename1, rbheadnode) == NULL || accessRBqueue(queuename2, rbheadnode) == NULL)
						printf("\nSelection does not exist\n");
					else
					{
						printf("\nName of new Ring Buffer (note that this does not delete previous queues):\n");
						char * queuename3;
						queuename3 = getstring();
					

					
					appendRBqueue(mergeR(accessRBqueue(queuename1, rbheadnode)->RB, accessRBqueue(queuename2, rbheadnode)->RB), queuename3, rbheadnode);
					}

					goto BEGINNING;
				}
				case 'h':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessRBqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
					{
						clearR(accessRBqueue(queuename, rbheadnode)->RB);
						clearrbqueue(queuename, rbheadnode);
					}

					goto BEGINNING;
				}
				case 'i':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();

					if(accessRBqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						storeR(accessRBqueue(queuename, rbheadnode)->RB, queuename);
				

					goto BEGINNING;
				}
				case 'j':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();


					appendRBqueue(loadR(queuename), queuename, rbheadnode);


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


void printqueuesll(LLarray * llheadnode)
{
	LLarray * current = llheadnode;

	while(current->name != NULL)
	{
		printf("%s", current->name);
		current = current->next;
	}
}

char * getstring()
{	
	char * string;

	scanf("%s%*c", string);

	return string;
}

void appendllqueue(linkedlists * linkedlist, char * queuename, LLarray * llheadnode)
{
	if(accessllqueue(queuename, llheadnode) == NULL)
	{
		if(llheadnode->next == NULL)
		{
			llheadnode->name = (char *)calloc(strlen(queuename)+1, sizeof(char));			
			strncpy(llheadnode->name, queuename, strlen(queuename));
			llheadnode->ll = linkedlist;
			printf("\nYour chosen name is: %s", llheadnode->name);
			llheadnode->next = (LLarray*) malloc(sizeof(LLarray));
			llheadnode->next->ll = NULL;
			llheadnode->next->name = NULL;
			llheadnode->next->next = NULL;

		}
		else
		{
			LLarray * current  = llheadnode;
			
			while(current->next != NULL)
				current = current->next;

			current->name = (char *)calloc(strlen(queuename)+1, sizeof(char));
			strncpy(current->name, queuename, strlen(queuename));
			current->ll = linkedlist;
			printf("\nYour chosen name is: %s", current->name);
			current->next = (LLarray*) malloc(sizeof(LLarray));
			current->next->ll = NULL;
			current->next->name = NULL;			
			current->next->next = NULL;
		}

	}
	else
		printf("\nThis name already exists");

		
}


LLarray * accessllqueue(char * queuename, LLarray * llheadnode)
{

	LLarray * current = llheadnode;
	while(current->next != NULL && strcmp(current->name, queuename) != 0)
		current = current->next;

	if(current->name == NULL)
		return NULL;
	if(strcmp(current->name, queuename) == 0)
		return current;
	else
		return NULL;
}

void clearllqueue(char * queuename, LLarray * llheadnode)
{
	LLarray * previous;
	LLarray * current = llheadnode;

	while(strcmp(current->name, queuename) != 0 && current->next != NULL)
	{
		previous = current;
		current = current->next;
	}

	if(strcmp(current->name, queuename) != 0 && current->next == NULL)
		printf("Queue does not exist");
	else
	{
		previous->next = current->next;
		free(current);
	}
}

	

void appendRBqueue(RingBuffer * RBqueue, char * queuename, RBarray * rbheadnode)
{
	if(accessRBqueue(queuename, rbheadnode) == NULL)
	{
		if(rbheadnode->next == NULL)
		{
			rbheadnode->name = (char *)calloc(strlen(queuename)+1, sizeof(char));			
			strncpy(rbheadnode->name, queuename, strlen(queuename));
			rbheadnode->RB = RBqueue;
			printf("\nYour chosen name is: %s", rbheadnode->name);
			rbheadnode->next = (RBarray*) malloc(sizeof(RBarray));
			rbheadnode->next->RB = NULL;
			rbheadnode->next->name = NULL;
			rbheadnode->next->next = NULL;

		}
		else
		{
			RBarray * current  = rbheadnode;
			
			while(current->next != NULL)
				current = current->next;

			current->name = (char *)calloc(strlen(queuename)+1, sizeof(char));
			strncpy(current->name, queuename, strlen(queuename));
			current->RB = RBqueue;
			printf("\nYour chosen name is: %s", current->name);
			current->next = (RBarray*) malloc(sizeof(RBarray));
			current->next->RB = NULL;
			current->next->name = NULL;			
			current->next->next = NULL;
		}

	}
	else
		printf("\nThis name already exists");

		
}


RBarray * accessRBqueue(char * queuename, RBarray * rbheadnode)
{
	RBarray * current = rbheadnode;
	while(current->next != NULL && strcmp(current->name, queuename) != 0)
		current = current->next;

	if(current->name == NULL)
		return NULL;
	if(strcmp(current->name, queuename) == 0)
		return current;
	else
		return NULL;
}

void clearrbqueue(char * queuename, RBarray * rbheadnode)
{
	RBarray * previous;
	RBarray * current = rbheadnode;

	while(strcmp(current->name, queuename) != 0 && current->next != NULL)
	{
		previous = current;
		current = current->next;
	}

	if(strcmp(current->name, queuename) != 0 && current->next == NULL)
		printf("Queue does not exist");
	else
	{
		previous->next = current->next;
		free(current);
	}
}





	
