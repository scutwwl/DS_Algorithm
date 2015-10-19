#include "binary_heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

heap initialize (int max_elements)
{
	heap h=(heap)malloc(sizeof(struct heapstruct));
	h->elements=(int *)malloc(sizeof(int)*(max_elements+1));
	h->capacity=max_elements;
	h->size=0;
	h->elements[0]=INT_MIN;
	return h;
}

void insert (int x,heap h)
{
	int i;
	if (isfull(h))
	{
		printf("the heap is full.\n");
		return;
	}
	h->size++;
	for (i=h->size;i>1;i=i/2)
	{
		if (h->elements[i/2]>x)
			h->elements[i]=h->elements[i/2];
		else
			break;
	}
	h->elements[i]=x;
}

bool isfull (heap h)
{
	if (h->size==h->capacity)
		return true;
	else
		return false;
}

void print_heap (heap h)
{
	for (int i=1;i<=h->size;i++)
		printf("%d ",h->elements[i]);
	printf("\n");
}

int findmin (heap h)
{
	return h->elements[1];
}

int deletemin (heap h)
{
	int i;
	int child;
	int tmp=h->elements[h->size];
	int min=h->elements[1];
	h->size--;
	for (i=1;i*2<=h->size;i=child )
	{
		if ((2*i+1)<=h->size && h->elements[2*i]>h->elements[2*i+1])
			child=2*i+1;
		else
			child=2*i;
		if (h->elements[child]<=tmp)
			h->elements[i]=h->elements[child];
		else
			break;
	}
	h->elements[i]=tmp;
	return min;
}
			

