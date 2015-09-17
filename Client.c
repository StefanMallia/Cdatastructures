#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LINKEDLIST.h"
#include "RINGBUFFER.h"

//A node for a linked list of linked list priority queues
typedef struct LLarray
{
	linkedlists * ll;
	char * name;
	struct LLarray * next;	
}LLarray;

//A node for a linked list of ringbuffer priority queues
typedef struct RBarray
{
	RingBuffer * rb;
	char * name;
	struct RBarray * next;
}RBarray;

//ll linkedlist
//rb ringbuffer

void printqueuesll(LLarray * llheadnode); //will print existing ll queues to console
void printqueuesrb(RBarray * rbheadnode); //will print existing rb queues to console
char * getstring(); //a function for user string input
void appendllqueue(linkedlists * linkedlist, char * queuename, LLarray * llheadnode);//adding an element to the ll for ll priority queues
LLarray * accessllqueue(char * queuename, LLarray * llheadnode);//accessing a particular node of the ll for the ll priority queues
LLarray * clearllqueue(char * queuename, LLarray * llheadnode);//clearing a particular node after having cleared its contained ll
void appendrbqueue(RingBuffer * RBqueue, char * queuename, RBarray * rbheadnode);//adding an element to the ll for rb priority queues
RBarray * accessrbqueue(char * queuename, RBarray * rbheadnode);//accessing a particular node of the ll for the rb priority queues
RBarray * clearrbqueue(char * queuename, RBarray * rbheadnode);//clearing a particular node after having cleared its contained rb



int main()
{
	//malloc on the first node of the ll containing the ll priority queues
	//everything is set to NULL to be set on the first create_q() function call
	LLarray * llheadnode = (LLarray *) malloc(sizeof(LLarray));
	llheadnode->ll = NULL;
	llheadnode->name = NULL;
	llheadnode->next = NULL;

	//malloc on the first node of the ll containing the rb priority queues
	//everything is set to NULL to be set on the first create_q() function call
	RBarray * rbheadnode = (RBarray *) malloc(sizeof(RBarray));
	rbheadnode->rb = NULL;
	rbheadnode->name = NULL;
	rbheadnode->next = NULL;

	char ch;//to be used to switch statements
	
	printf("\nWelcome to the queueing application");

while (true)
{
	printf("\n\na. Linked List\nb. Ring Buffer\n\n");
	printf("Please make a selection (a or b or enter 'q' to quit):\n\n");
	
	
	scanf("%c%*c", &ch);//%*c is used to exclude newline
	{

		if('q' == ch)
			return 0;

		switch(ch)
		{
			case 'a':
				{
		char * queuename;
		char ch2 = NULL;

		printf("\n\nActions:\n\n");
		printf("a. Create a Linked List Queue\nb. Make an entry into a queue\nc. Dequeue highest priority element\nd. Highest priority element\ne. Check whether queue is empty\nf. Size of queue\ng. Merge two queue's\nh. Clear queue of contents\ni. List existing queues\nj. Store existing queue to file\nk. Load queue from file\n");
		printf("Please make a selection (enter 'q' to return to main menu):\n\n");

		scanf("%c%*c", &ch2);
		{
			
			if('q' == ch2)
				continue;

			switch(ch2)
			{
				case 'a': //ll menu
				{//create a new ll
					printf("\nName of Linked List:\n");
					queuename = getstring();

					printf("\nMaximum size of Linked List:\n");
					int max_size;
					scanf("%d%*c", &max_size);

					appendllqueue(create_q(max_size), queuename, llheadnode);

					continue;
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

					if(accessllqueue(queuename, llheadnode) == NULL)//accessllqueue returns a NULL if it does not find specified name
						printf("\nThis queue does not exist\n");
					else
						enqueue(accessllqueue(queuename, llheadnode)->ll, element, priority);
				
					continue;
				}

				case 'c':
				{
					printf("\nName of Linked List:\n");
					queuename = getstring();

					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						dequeue(accessllqueue(queuename, llheadnode)->ll);

					continue;
				}

				case 'd':
				{
					printf("\nName of Linked List:\n");
					queuename = getstring();

					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("\nHighest priority element is: %d\nwith a priority of: %d", peek(accessllqueue(queuename, llheadnode)->ll)->element, peek(accessllqueue(queuename, llheadnode)->ll)->priority);

					continue;
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

					continue;
				}

				case 'f':
				{
					printf("\nName of Linked List:\n");
					queuename = getstring();

					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("Size of queue is %d\n",size(accessllqueue(queuename, llheadnode)->ll));

					continue;
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
					{//also deletes the two input queues (queuename1 and queuename2)
						printf("\nName of new Linked List:\n");
						char queuename3[20];
						strncpy(queuename3, getstring(),20);

						appendllqueue(merge(accessllqueue(queuename1, llheadnode)->ll, accessllqueue(queuename2, llheadnode)->ll), queuename3, llheadnode);
						clear(accessllqueue(queuename1, llheadnode)->ll);
						llheadnode = clearllqueue(queuename1, llheadnode);

						clear(accessllqueue(queuename2, llheadnode)->ll);
						llheadnode = clearllqueue(queuename2, llheadnode);

					}

					continue;
				}

				case 'h':
				{
					char delete;
					printf("\nName of Linked List:\n");
					queuename = getstring();

					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
					{
						clear(accessllqueue(queuename, llheadnode)->ll);
						printf("\n%s cleared\n\n", queuename);
						printf("Delete? (y/n)");						
						scanf("%c%*c", &delete);						
						if(delete == 'y')						
							llheadnode = clearllqueue(queuename, llheadnode);
							//this function returns the a new headnode in the case it is chosen for deletion

					}

					continue;
				}

				case 'i':
				{
					printqueuesll(llheadnode);

					continue;
				}

				case 'j':
				{
					printf("\nName of Linked List:\n");
					queuename = getstring();

					if(accessllqueue(queuename, llheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						store(accessllqueue(queuename, llheadnode)->ll, queuename);

					continue;
				}

				case 'k':
				{
					printf("\nName of Linked List:\n");
					queuename = getstring();
					
					appendllqueue(load(queuename), queuename, llheadnode);

					continue;
				}

				default:
				{
					printf("\nThat is not a valid choice\n");

					continue;
				}
			}		
		}
	}

			case 'b':
				{
		char * queuename;
		char ch2 = NULL;

		printf("\n\nActions:\n\n");
		printf("a. Create a RingBuffer Queue\nb. Make an entry into a queue\nc. Dequeue highest priority element\nd. Highest priority element\ne. Check whether queue is empty\nf. Size of queue\ng. Merge two queue's\nh. Clear queue of contents\ni. List existing queues\nj. Store existing queue to file\nk. Load queue from file\n");
		printf("Please make a selection (enter 'q' to return to main menu):\n\n");

		scanf("%c%*c", &ch2);
		{			
			if('q' == ch2)
				continue;

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

					continue;
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
						enqueueR(accessrbqueue(queuename, rbheadnode)->rb, element, priority);

					continue;
				}

				case 'c':
				{
					printf("\nName of Ring Buffer:\n");
					queuename = getstring();

					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						dequeueR(accessrbqueue(queuename, rbheadnode)->rb);

					continue;
				}

				case 'd':
				{
					printf("\nName of Ring Buffer:\n");

					queuename = getstring();
					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("\nHighest priority element is: %d\nwith a priority of: %d", peekR(accessrbqueue(queuename, rbheadnode)->rb).elem, peekR(accessrbqueue(queuename, rbheadnode)->rb).priority);

					continue;
				}

				case 'e':
				{
					printf("\nName of Ring Buffer:\n");
					queuename = getstring();

					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
					{
						if(is_emptyR(accessrbqueue(queuename, rbheadnode)->rb))
							printf("Queue is empty\n");
						else
							printf("Queue is not empty\n");
					}

					continue;
				}

				case 'f':
				{
					printf("\nName of Ring Buffer:\n");
					queuename = getstring();

					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						printf("Size of queue is %d\n",sizeR(accessrbqueue(queuename, rbheadnode)->rb));

					continue;
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
					
						appendrbqueue(mergeR(accessrbqueue(queuename1, rbheadnode)->rb, accessrbqueue(queuename2, rbheadnode)->rb), queuename3, rbheadnode);
						//clearing input queues
						clearR(accessrbqueue(queuename1, rbheadnode)->rb);
						rbheadnode = clearrbqueue(queuename1, rbheadnode);

						clearR(accessrbqueue(queuename2, rbheadnode)->rb);
						rbheadnode = clearrbqueue(queuename2, rbheadnode);
					}

					continue;
				}

				case 'h':
				{
					char delete;
					printf("\nName of Ring Buffer:\n");
					queuename = getstring();

					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
					{
						clearR(accessrbqueue(queuename, rbheadnode)->rb);
						printf("\n%s cleared\n\n", queuename);
						printf("Delete? (y/n)");						
						scanf("%c%*c", &delete);						
						if(delete == 'y')						
							rbheadnode = clearrbqueue(queuename, rbheadnode);
					}

					continue;
				}

				case 'i':
				{
					printqueuesrb(rbheadnode);
					continue;
				}

				case 'j':
				{
					printf("\nName of Ring Buffer:\n");
					queuename = getstring();

					if(accessrbqueue(queuename, rbheadnode) == NULL)
						printf("\nThis queue does not exist\n");
					else
						storeR(accessrbqueue(queuename, rbheadnode)->rb, queuename);
				
					continue;
				}

				case 'k':
				{
					printf("\nName of Ring Buffer:\n");
					queuename = getstring();

					appendrbqueue(loadR(queuename), queuename, rbheadnode);

					continue;

				}

				default:
				{
					printf("\nThat is not a valid choice\n");

					continue;
				}
			}
		}
	}//rb menu
		
			default:
				printf("\nThat is not a valid choice\n");
				continue;
		}
	}

}
}



////////////////////////////////////////////////////////////////////////////////

void printqueuesll(LLarray * llheadnode)
{	//will print existing ll queues to console
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
{	//will print existing rb queues to console
	RBarray * current = rbheadnode;// Queue array struct
	int i = 1; //Queue number

	while(current->name != NULL) //Iterate through queue struct array to print  one by one
	{
		printf("Queue:%d %s with %d elements \n", i, current->name, sizeR(current->rb));
		current = current->next;
		i++;
	}
}

char * getstring() 
{	//a function for user string input
	char * string = malloc(sizeof(char)*20);

	scanf("%s%*c", string);

	return string;
}

////////////////////////////////////////////////////////////////////////////////

void appendllqueue(linkedlists * linkedlist, char * queuename, LLarray * llheadnode)
{	//adding an element to the ll for ll priority queues
	if(accessllqueue(queuename, llheadnode) == NULL)//if name not found in list of queues
	{
		LLarray * current  = llheadnode;
		
		while(current->next != NULL)
			current = current->next;

		current->name = (char *)calloc(strlen(queuename)+1, sizeof(char));
		strncpy(current->name, queuename, strlen(queuename));

		current->ll = linkedlist;

		printf("\nYour queue name is: %s", current->name);

		current->next = (LLarray*) malloc(sizeof(LLarray));
		current->next->ll = NULL;
		current->next->name = NULL;			
		current->next->next = NULL;

	}
	else
		printf("\nThis name already exists");

		
}


LLarray * accessllqueue(char * queuename, LLarray * llheadnode)
{	//accessing a particular node of the ll for the ll priority queues
	LLarray * current = llheadnode;//starting from first node

	while(current->next != NULL && strcmp(current->name, queuename) != 0)
	//if next node is unallocated and current node's name does not match user input
		current = current->next;

	if(current->name == NULL && current->next == NULL)
	//if this is true then whole list was iterated through with no results
		return NULL;
	else
	//this is true if result is found, current node is returned (list of linked lists)
		return current;
}

LLarray * clearllqueue(char * queuename, LLarray * llheadnode)
{	//clearing a particular node after having cleared its contained ll
	LLarray * previous;//used to fix previous node's pointer
	LLarray * current = llheadnode;

	while(strcmp(current->name, queuename) != 0)//iterates until match
	{
		previous = current;
		current = current->next;
	}

	if(current == llheadnode)//if current happens to be headnode
	{
		llheadnode = current->next;
		if(llheadnode->next == NULL)//if headnode is not followed by additional nodes, allocates new memory
		{
			llheadnode->next = (LLarray *)malloc(sizeof(LLarray));
			llheadnode->next->name = NULL;
			llheadnode->next->ll = NULL;
			llheadnode->next->next = NULL;
			
			llheadnode = llheadnode->next;

		}
	
		free(current->name); // ll already freed and next should not be freed
		free(current); // free what was previously headnode
		printf("\n%s deleted\n", queuename);
	}
	else//if headnode is not node to be cleared
	{	
		previous->next = current->next;		
		free(current->name);
		free(current);
		printf("\n%s deleted\n", queuename);	
		
		
	}


	return llheadnode;
}
////////////////////////////////////////////////////////////////////////////////
	

void appendrbqueue(RingBuffer * RBqueue, char * queuename, RBarray * rbheadnode)
{	//adding an element to the ll for ll priority queues
	if(accessrbqueue(queuename, rbheadnode) == NULL)//if name not found in list of queues
	{
		RBarray * current  = rbheadnode;
		
		while(current->next != NULL)
			current = current->next;

		current->name = (char *)calloc(strlen(queuename)+1, sizeof(char));
		strncpy(current->name, queuename, strlen(queuename));

		current->rb = RBqueue;

		printf("\nYour queue name is: %s", current->name);

		current->next = (RBarray*) malloc(sizeof(LLarray));
		current->next->rb = NULL;
		current->next->name = NULL;			
		current->next->next = NULL;

	}
	else
		printf("\nThis name already exists");




		
}


RBarray * accessrbqueue(char * queuename, RBarray * rbheadnode)
{	//accessing a particular node of the ll for the rb priority queues
	RBarray * current = rbheadnode;//starting from first node

	while(current->next != NULL && strcmp(current->name, queuename) != 0)
	//if next node is unallocated and current node's name does not match user input
		current = current->next;

	if(current->name == NULL && current->next == NULL)
	//if this is true then whole list was iterated through with no results
		return NULL;
	else
	//this is true if result is found, current node is returned (list of linked lists)
		return current;
}

RBarray * clearrbqueue(char * queuename, RBarray * rbheadnode)
{	//clearing a particular node after having cleared its contained rb
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
			rbheadnode->next->rb = NULL;
			rbheadnode->next->next = NULL;

			rbheadnode = rbheadnode->next;
		}
	
		free(current->name); // ll already freed and next should not be freed
		free(current); // free struct
		printf("\n%s deleted\n", queuename);
	}
	else
	{	
		previous->next = current->next;		
		free(current->name);
		free(current);
		printf("\n%s deleted\n", queuename);	
		
		
	}
	return rbheadnode;
}
