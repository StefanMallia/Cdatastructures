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
void printqueuesrb(RBarray * rbheadnode);
char * getstring();
void appendllqueue(linkedlists * linkedlist, char * queuename, LLarray * llheadnode);
LLarray * accessllqueue(char * queuename, LLarray * llheadnode);
LLarray * clearllqueue(char * queuename, LLarray * llheadnode);
void appendrbqueue(RingBuffer * RBqueue, char * queuename, RBarray * rbheadnode);
RBarray * accessrbqueue(char * queuename, RBarray * rbheadnode);
RBarray * clearrbqueue(char * queuename, RBarray * rbheadnode);



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
		printf("a. Create a Linked List Queue\nb. Make an entry into a queue\nc. Dequeue highest priority element\nd. Highest priority element\ne. Check whether queue is empty\nf. Size of queue\ng. Merge two queue's\nh. Clear queue of contents\ni. List existing queues\nj. Store existing queue to file\nk. Load queue from file\n");
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
					queuename = getstring();


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

					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("Size of queue is %d\n",size(accessllqueue(queuename, llheadnode)->ll));

					goto BEGINNING;
				}
				case 'g':
				{
					printf("\nName of Linked List 1:\n");
					char queuename1[20];
					strncpy(queuename1, getstring(),20);


					printf("\nName of Linked List 2:\n");
					char queuename2[20];
					strncpy(queuename2, getstring(),20);

					if((accessllqueue(queuename1, llheadnode) == NULL) || (accessllqueue(queuename2, llheadnode) == NULL))
						printf("\nSelection does not exist\n");
					else
					{
						printf("\nName of new Linked List:\n");
						char queuename3[20];
						strncpy(queuename3, getstring(),20);

						appendllqueue(merge(accessllqueue(queuename1, llheadnode)->ll, accessllqueue(queuename2, llheadnode)->ll), queuename3, llheadnode);
						clear(accessllqueue(queuename1, llheadnode)->ll);
						llheadnode = clearllqueue(queuename1, llheadnode);

						clear(accessllqueue(queuename2, llheadnode)->ll);
						llheadnode = clearllqueue(queuename2, llheadnode);

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
						llheadnode = clearllqueue(queuename, llheadnode);
					}

					goto BEGINNING;
				}
				case 'i':
				{
					printqueuesll(llheadnode);
					goto BEGINNING;
				}

				case 'j':
				{
					printf("\nName of Linked List:\n");

					queuename = getstring();
					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						store(accessllqueue(queuename, llheadnode)->ll, queuename);

					goto BEGINNING;


				}
				case 'k':
				{
					printf("\nName of Linked List:\n");
					queuename = getstring();
					
					appendllqueue(load(queuename), queuename, llheadnode);


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
		printf("a. Create a RingBuffer Queue\nb. Make an entry into a queue\nc. Dequeue highest priority element\nd. Highest priority element\ne. Check whether queue is empty\nf. Size of queue\ng. Merge two queue's\nh. Clear queue of contents\ni. List existing queues\nj. Store existing queue to file\nk. Load queue from file\n");
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




					appendrbqueue(create_qR(max_size), queuename, rbheadnode);


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
					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else					
						enqueueR(accessrbqueue(queuename, rbheadnode)->RB, element, priority);

					goto BEGINNING;
				}

				case 'c':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						dequeueR(accessrbqueue(queuename, rbheadnode)->RB);

					goto BEGINNING;
				}

				case 'd':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("\nHighest priority element is: %d\nwith a priority of: %d", peekR(accessrbqueue(queuename, rbheadnode)->RB).elem, peekR(accessrbqueue(queuename, rbheadnode)->RB).priority);

					goto BEGINNING;
				}

				case 'e':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
					{
						if(is_emptyR(accessrbqueue(queuename, rbheadnode)->RB))
							printf("Queue is empty\n");
						else
							printf("Queue is not empty\n");
					}			printf("\nName of Ring Buffer:\n");

					queuename = getstring();

					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						storeR(accessrbqueue(queuename, rbheadnode)->RB, queuename);
				

					goto BEGINNING;
				}

				case 'f':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("Size of queue is %d\n",sizeR(accessrbqueue(queuename, rbheadnode)->RB));

					goto BEGINNING;
				}
				case 'g':
				{
					//Takes 3 string inputs, deletes 2 input queues, creates one merged queues
					printf("\nName of Ring Buffer 1:\n");
					char queuename1[20];
					strncpy(queuename1, getstring(), 20);


					printf("\nName of Ring Buffer 2:\n");
					char queuename2[20];
					strncpy(queuename2, getstring(), 20);

					if(accessrbqueue(queuename1, rbheadnode) == NULL || accessrbqueue(queuename2, rbheadnode) == NULL)
						printf("\nSelection does not exist\n");
					else
					{
						printf("\nName of new Ring Buffer:\n");
						char queuename3[20];
						strncpy(queuename3, getstring(), 20);
					

					
					appendrbqueue(mergeR(accessrbqueue(queuename1, rbheadnode)->RB, accessrbqueue(queuename2, rbheadnode)->RB), queuename3, rbheadnode);
						//clearing input queues
						clearR(accessrbqueue(queuename1, rbheadnode)->RB);
						rbheadnode = clearrbqueue(queuename1, rbheadnode);

						clearR(accessrbqueue(queuename2, rbheadnode)->RB);
						rbheadnode = clearrbqueue(queuename2, rbheadnode);
					}

					goto BEGINNING;
				}
				case 'h':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
					{
						clearR(accessrbqueue(queuename, rbheadnode)->RB);
						rbheadnode = clearrbqueue(queuename, rbheadnode);
					}

					goto BEGINNING;
				}

				case 'i':
				{
					printqueuesrb(rbheadnode);
					goto BEGINNING;
				}
				case 'j':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();

					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						storeR(accessrbqueue(queuename, rbheadnode)->RB, queuename);
				

					goto BEGINNING;
				}
				case 'k':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();


					appendrbqueue(loadR(queuename), queuename, rbheadnode);


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

////////////////////////////////////////////////////////////////////////////////

void printqueuesll(LLarray * llheadnode)
{
	LLarray * current = llheadnode;// Queue array struct
	int i = 1; //Queue number

	while(current->name != NULL) //Iterate through queue struct array to print  one by one
	{
		printf("Queue:%d %s with %d elements \n", i, current->name, size(current->ll));
		current = current->next;
		i++;
	}
}
void printqueuesrb(RBarray * rbheadnode)
{
	RBarray * current = rbheadnode;// Queue array struct
	int i = 1; //Queue number

	while(current->name != NULL) //Iterate through queue struct array to print  one by one
	{
		printf("Queue:%d %s with %d elements \n", i, current->name, sizeR(current->RB));
		current = current->next;
		i++;
	}
}

char * getstring() 
{	
	char * string;	

	scanf("%s%*c", string2);


	return string;
}

////////////////////////////////////////////////////////////////////////////////

void appendllqueue(linkedlists * linkedlist, char * queuename, LLarray * llheadnode)
{
	if(accessllqueue(queuename, llheadnode) == NULL )
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
	else
		printf("\nThis name already exists");

		
}


LLarray * accessllqueue(char * queuename, LLarray * llheadnode)
{

	LLarray * current = llheadnode;
	while(current->next != NULL && strcmp(current->name, queuename) != 0)
		current = current->next;
	if(current->name == NULL && current->next == NULL)
		return NULL;
	else
		return current;
}

LLarray * clearllqueue(char * queuename, LLarray * llheadnode)
{
	LLarray * previous;
	LLarray * current = llheadnode;


	while(strcmp(current->name, queuename) != 0)
	{
		previous = current;
		current = current->next;
	}

	if(current == llheadnode)
	{
		llheadnode = current->next;
		if(llheadnode->next == NULL)
		{
			llheadnode->next = (LLarray *)malloc(sizeof(LLarray));
			llheadnode->next->name = NULL;
			llheadnode->next->ll = NULL;
			llheadnode->next->next = NULL;
		}
	
		free(current->name); // ll already freed and next should not be freed
		free(current); // free struct
		printf("\n%s cleared\n", queuename);
	}
	else
	{	
		previous->next = current->next;		
		free(current->name);
		free(current);
		printf("\n%s cleared\n", queuename);	
		
		
	}


	return llheadnode;
}
////////////////////////////////////////////////////////////////////////////////
	

void appendrbqueue(RingBuffer * RBqueue, char * queuename, RBarray * rbheadnode)
{
	if(accessrbqueue(queuename, rbheadnode)->name == NULL || strcmp(accessrbqueue(queuename, rbheadnode)->name, queuename) != 0)
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
	else
		printf("\nThis name already exists");

		
}


RBarray * accessrbqueue(char * queuename, RBarray * rbheadnode)
{
	RBarray * current = rbheadnode;
	while(current->next != NULL && strcmp(current->name, queuename) != 0)
		current = current->next;

	return current;
}

RBarray * clearrbqueue(char * queuename, RBarray * rbheadnode)
{
	RBarray * previous;
	RBarray * current = rbheadnode;


	while(strcmp(current->name, queuename) != 0)
	{
		previous = current;
		current = current->next;
	}

	if(current == rbheadnode)
	{
		rbheadnode = current->next;
		if(rbheadnode->next == NULL)
		{
			rbheadnode->next = (RBarray *)malloc(sizeof(RBarray));
			rbheadnode->next->name = NULL;
			rbheadnode->next->RB = NULL;
			rbheadnode->next->next = NULL;
		}
	
		free(current->name); // ll already freed and next should not be freed
		free(current); // free struct
		printf("\n%s cleared\n", queuename);
	}
	else
	{	
		previous->next = current->next;		
		free(current->name);
		free(current);
		printf("\n%s cleared\n", queuename);	
		
		
	}
	return rbheadnode;
}




	
