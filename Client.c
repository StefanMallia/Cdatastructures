#include <stdio.h>

int main()
{
	char ch;
	
	printf("Welcome to the queueing application\n\n");

	BEGINNING:
	printf("1. Linked List\n2. Ring Buffer\n\n");
	printf("Please make a selection (enter 'q' to cancel):\n\n");

	while((ch = getchar()))
	{
		if('q' == ch)
			goto BEGINNING;

		switch(ch)
		{
			case '1':
				goto CASE1;

			case '2':
				goto CASE2;
		
			default:
				printf("\nThat is not a valid choice\n");
		}

	CASE1:
	{
		printf("Actions:\n\n");
		printf("1. Create a Linked List Queue\n2. Make an entry into the queue\n3. Dequeue highest priority element\n4. Highest priority element\n5. Check whether queue is empty\n6. Size of queue\n7. Clear queue of contents\n8. Store existing queue to file\n9. Load queue from file\n")
		printf("Please make a selection (enter 'q' to cancel):\n\n");

	while((ch = getchar()))
	{
		if('q' == ch)
			goto BEGINNING;

		switch(ch)
		{
			case '1':
				printf("Maximum size of Linked List:");
				
				int max_size = atoi(getchar());
				create_q(max_size);
				break;

			case '2':
				printf("

			case '3':
				goto CASE3;

			case '4':
				goto CASE4;

			case '5':
				goto CASE5;

			case '6':
				goto CASE6;

			case '7':
				goto CASE7;

			case '8':
				goto CASE8;


		
			default:
				printf("\nThat is not a valid choice\n");
		}



	return 0;
}
	
