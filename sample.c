#include <stdio.h>
#include <stdlib.h>

#define max_size 50

int main()
{
	struct priority_q 
	{
		int element[max_size];
		int priority[max_size];
	};

	struct priority_q lol;
	
		lol.element[0] = 2;
		lol.priority[0] = 2;
	

	printf("%lu %d", sizeof(lol.element[0]), lol.priority[0]);

	return 0;
}
