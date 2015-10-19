#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
void bubblesort(int *arr, int size)
{
	int i, j, tmp;
	int sorted;
	for (i=1; i<size; i++)
	{
		sorted = 1; 
		for (j=size-1; j>=i; j--)
		{
			if (arr[j-1] < arr[j])
			{
				tmp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = tmp;
				sorted = 0;
			}
		}
		if (sorted == 1)
			break;
		
	}
}
		
int getkth_bubblesort(int k, int *arr,int size)
{
	bubblesort(arr, size);
	return arr[k-1];
}

void insert_arr(int *sarr, int size, int data)
{
	int i;
	for (i=size-2; i>=0; --i)
	{
		if (sarr[i] < data)
			sarr[i+1] = sarr[i];
		else
			break;
	}
	sarr[i+1] = data;
}

int getkth_ksort(int k, int *arr, int size)
{
	int i, j;
	bubblesort(arr, k);
	int *karr = (int *)malloc(sizeof(int) * k);
	for (j=0; j<k; j++)
		karr[j] = arr[j];
	for (i=k; i<size; i++)
	{
		if (karr[k-1] < arr[i])
			insert_arr(karr, k, arr[i]);
	}
	return karr[k-1];
}

int main ()
{
	int arr[SIZE] = {5, 3, 6, 7, 2, 9, 4, 10, 1, 8};
	int brr[SIZE] = {5, 3, 6, 7, 2, 9, 4, 10, 1, 8};
	int k = 4;
	printf("getkth_bubblesort: %d\n", getkth_bubblesort(k, arr, SIZE));
	printf("getkth_ksort: %d\n", getkth_ksort(k, brr, SIZE));
	return 0;
}
