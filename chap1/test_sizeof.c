#include <stdlib.h>
#include <stdio.h>
int main ()
{
	int i=0;
	int *arr = (int *)malloc(sizeof(int)*10);
	for ( ; i<10; i++)
		arr[i] = 0;
	long brr[] = {1,2,3,4,5,6,7};
	int crr[] = {1,2,3,4,5,6,7};
	int test;
	printf("%d\n", (int)sizeof(crr));
	return 0;
}
