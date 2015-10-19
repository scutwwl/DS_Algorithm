#include "binary_heap.h"
#include <stdio.h>
#include <stdlib.h>


int main (void)
{
	heap h;
	h=initialize(12);
	int x;
	while (scanf("%d",&x)!=EOF)
		insert(x,h);
	printf("the heap is :\n");
	print_heap(h);
	printf("after one deletemin :\n");
	deletemin(h);
	print_heap(h);
	return 0;
}

