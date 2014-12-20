/* Circular buffer example, keeps one slot open */
 
#include <stdio.h>
#include <stdlib.h>
 
 
int main(int argc, char **argv) {
	float a = -1;
	float b = 5;
	printf("-1 modulo 5 = %f\n", a-(a/b)*b);
	
    return 0;
} 
