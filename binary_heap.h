#ifndef _binary_heap_H
#define _binary_heap_H

#define bool int
#define true 1
#define false 0

struct heapstruct
{
	int capacity;
	int size;
	int *elements;   // now element type is int,and elements is array.
};

typedef struct heapstruct *heap;

heap initialize (int max_elements);
void insert (int x,heap h);
int deletemin (heap h);
int findmin (heap h);
bool isfull (heap h);
void print_heap (heap h);


#endif
