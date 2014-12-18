#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

	char str1[] = "hello ";
	char str2[] = "pal!";
	
	strncat(str1,str2,4);

	printf("%s", str1);

	return 0;

}
