#include <stdio.h>
#include <stdlib.h>
#include "LINKEDLIST.h"
#include "RINGBUFFER.h"

int Lcounter = 0; //a counter of number of existing queues
int Rcounter = 0;


typedef struct
{
	char * name;
	linkedlists * ll;
}LLarray;




void appendllqueue(linkedlists * linkedlist, char * queuename, LLarray * Llist);
int accessllqueue(char * queuename, LLarray * Llist);

int main()
{


	char ch;
	
	printf("Welcome to the queueing application\n\n");

	BEGINNING:
	printf("1. Linked List\n2. Ring Buffer\n\n");
	printf("Please make a selection (1 or 2 or enter 'q' to cancel):\n\n");

	while((ch = getchar()))
	{
		if('q' == ch)
			return 0;

		switch(ch)
		{
			case '1':
				goto CASE1;

			case '2':
				return 0;//goto CASE2;
		
			default:
				printf("\nThat is not a valid choice\n");
		}
	}

	CASE1:
	{
		
	LLarray * Llist = calloc(1, sizeof(LLarray));
	char * queuename;


		printf("Actions:\n\n");
		printf("1. Create a Linked List Queue\n2. Make an entry into a queue\n3. Dequeue highest priority element\n4. Highest priority element\n5. Check whether queue is empty\n6. Size of queue\n7. Merge two queue's\n8. Clear queue of contents\n9. Store existing queue to file\n10. Load queue from file\n");
		printf("Please make a selection (enter 'q' to cancel):\n\n");

		while((ch = getchar()))
		{
			if('q' == ch)
				goto BEGINNING;

			switch(ch)
			{
				case '1':
					printf("Maximum size of Linked List:\n");
					int max_size;
					scanf("%d", &max_size);

					printf("Name of Linked List:\n");
					fgets(queuename, 15, stdin);

					appendllqueue(create_q(max_size), queuename, Llist);
					Lcounter++;

					goto BEGINNING;

				case '2':
					printf("Enter the queue name:\n");
					fgets(queuename, 15, stdin);

					printf("Enter an integer element:\n");
					int element;
					scanf("%d", &element);
				
					printf("Enter an integer priority:\n");
					int priority;
					scanf("%d", &priority);

					enqueue(Llist[accessllqueue(queuename, Llist)].ll, element, priority);
				
					goto BEGINNING;

				case '3':
					printf("Name of Linked List:\n");

					fgets(queuename, 15, stdin);
					dequeue(Llist[accessllqueue(queuename, Llist)].ll);

					goto BEGINNING;

				case '4':
					printf("Name of Linked List:\n");

					fgets(queuename, 15, stdin);
					peek(Llist[accessllqueue(queuename, Llist)].ll);

					goto BEGINNING;

				case '5':
					printf("Name of Linked List:\n");

					fgets(queuename, 15, stdin);
					if(is_empty(Llist[accessllqueue(queuename, Llist)].ll))
						printf("Queue is empty\n");
					else
						printf("Queue is not empty\n");
				
					goto BEGINNING;

				case '6':
					printf("Name of Linked List:\n");

					fgets(queuename, 15, stdin);
					printf("Size of queue is %d\n",size(Llist[accessllqueue(queuename, Llist)].ll));

					goto BEGINNING;

				case '7':
					printf("Name of Linked List 1:\n");
					char * queuename1;
					fgets(queuename, 15, stdin);

					printf("Name of Linked List 2:\n");
					char * queuename2;
					fgets(queuename, 15, stdin);

					merge(Llist[accessllqueue(queuename1, Llist)].ll, Llist[accessllqueue(queuename2, Llist)].ll);

					goto BEGINNING;

				case '8':
					printf("Name of Linked List:\n");

					fgets(queuename, 15, stdin);
					clear(Llist[accessllqueue(queuename, Llist)].ll);
				

					goto BEGINNING;

				case '9':
					printf("Name of Linked List:\n");

					fgets(queuename, 15, stdin);
					store(Llist[accessllqueue(queuename, Llist)].ll, queuename);
				

					goto BEGINNING;

				case '0':
					printf("Name of Linked List:\n");

					fgets(queuename, 15, stdin);

					appendllqueue(load(queuename), queuename, Llist);
					Lcounter++;
				

					goto BEGINNING;
		
				default:
					printf("\nThat is not a valid choice\n");
			}



		return 0;
		}
	}
}


void appendllqueue(linkedlists * linkedlist, char * queuename, LLarray * Llist)
{
	LLarray * tmp;
	tmp = realloc(Llist, (Lcounter+1) * sizeof(LLarray));
	//Llist = (LLarray *)realloc(sizeof(LLarray),Lcounter+1);
	if(NULL != tmp)
		Llist = tmp;
	
	Llist[Lcounter].name = queuename;
	Llist[Lcounter].ll = linkedlist;
}


int accessllqueue(char * queuename, LLarray * Llist)
{
	int accesscount=0;
	while(accesscount != Lcounter)
	{
		if(Llist[accesscount].name = queuename)
			return accesscount;
	}
	
	return 0;
}



	
