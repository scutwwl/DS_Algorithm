#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define SIZE 100000
//int arr[SIZE]={1,11,2,12,3,13,4,14,5,15};

void shellsort (int *arr,int size);
void heapsort (int *arr, int size);
void percdown (int *arr, int i, int size);  //  used by heapsort
void swap (int *a, int *b);   // used by heapsort
void mergesort (int *arr, int size);
void msort (int *arr,int *tmp_arr,int left,int right);  // used by mergesort
void merge (int *arr,int *tmp_arr,int left,int mi,int right);
void quicksort (int *arr,int size);
int median3 (int *arr,int left,int right);        // used by quicksort
void q_sort (int *arr,int left,int right);         // used by quicksort
void insertionsort (int *arr,int size);

int main (void)
{
	struct timespec start,end;
	long time,starttime,endtime;
	
	int *arr=(int *)malloc(sizeof(int)*SIZE);   // sorted by shellsort
	int *brr=(int *)malloc(sizeof(int)*SIZE);   // sorted by heapsort
	int *crr=(int *)malloc(sizeof(int)*SIZE);   // sorted by mergesort
	int *drr=(int *)malloc(sizeof(int)*SIZE);   // sorted by quicksort
	int *err=(int *)malloc(sizeof(int)*SIZE);   // sorted by insertionsort

	srand(1);
	for (int i=0;i<SIZE;i++)
	{
		arr[i]=rand();
		brr[i]=arr[i];
		crr[i]=arr[i];
		drr[i]=arr[i];
		err[i]=arr[i];
		//printf("%d ",arr[i]);
	}
	//printf("\n");	
	// calculate the shellsort time
	clock_gettime(CLOCK_REALTIME,&start);
	shellsort(arr,SIZE);
	clock_gettime(CLOCK_REALTIME,&end);
	
	starttime=(long)start.tv_sec+start.tv_nsec/1000000000;
	endtime=(long)end.tv_sec+end.tv_nsec/1000000000;
	time=endtime-starttime;
	/*
	printf("after sort,the arr is: \n");
	for (int i=0;i<SIZE;i++)
		printf("%d ",arr[i]);
	printf("\n");
	*/
	printf("SHELLSORT : %ld s \n",time);
	
	// calculate the heapsort time
	clock_gettime(CLOCK_REALTIME,&start);
	heapsort(brr,SIZE);
	clock_gettime(CLOCK_REALTIME,&end);
	
	starttime=(long)start.tv_sec+start.tv_nsec/1000000000;
	endtime=(long)end.tv_sec+end.tv_nsec/1000000000;
	time=endtime-starttime;

	printf("HEAPSORT : %ld s \n",time);
	/*
	printf("after sort,the arr is: \n");
	for (int i=0;i<SIZE;i++)
		printf("%d ",arr[i]);
	printf("\n");
	*/

	// calculate the mergesort time
	clock_gettime(CLOCK_REALTIME,&start);
	mergesort(crr,SIZE);
	clock_gettime(CLOCK_REALTIME,&end);
	
	starttime=(long)start.tv_sec+start.tv_nsec/1000000000;
	endtime=(long)end.tv_sec+end.tv_nsec/1000000000;
	time=endtime-starttime;

	printf("MERGESORT : %ld s \n",time);
	/*	
	printf("after sort,the arr is: \n");
	for (int i=0;i<SIZE;i++)
		printf("%d ",arr[i]);
	printf("\n");
	*/
	// calculate the quicksort time
	clock_gettime(CLOCK_REALTIME,&start);
	quicksort(drr,SIZE);
	clock_gettime(CLOCK_REALTIME,&end);
	
	starttime=(long)start.tv_sec+start.tv_nsec/1000000000;
	endtime=(long)end.tv_sec+end.tv_nsec/1000000000;
	time=endtime-starttime;

	printf("QUICKSORT : %ld s \n",time);
	/*
	printf("after sort,the arr is: \n");
	for (int i=0;i<SIZE;i++)
		printf("%d ",arr[i]);
	printf("\n");
	*/

	// calculate the insertionsort time
	clock_gettime(CLOCK_REALTIME,&start);
	insertionsort(err,SIZE);
	clock_gettime(CLOCK_REALTIME,&end);
	
	starttime=(long)start.tv_sec+start.tv_nsec/1000000000;
	endtime=(long)end.tv_sec+end.tv_nsec/1000000000;
	time=endtime-starttime;

	printf("INSERTIONSORT : %ld s \n",time);
	/*	
	printf("after sort,the arr is: \n");
	for (int i=0;i<SIZE;i++)
		printf("%d ",arr[i]);
	printf("\n");
	*/

	exit(0);
}

void shellsort (int *arr,int size)
{
	int increment;
	for (increment=size/2;increment>0;increment/=2)
		for (int i=increment;i<size;i++)
		{
			int tmp=arr[i];
			int j;
			for (j=i;j>=increment;j-=increment)
			{
				if (tmp<arr[j-increment])
					arr[j]=arr[j-increment];
				else
					break;
			}
			arr[j]=tmp;
		}
}


void percdown (int *arr,int i,int size)
{
	int tmp;
	int child;
	for (tmp=arr[i];2*i+1<size;i=child)
	{
		if ( (2*i+1+1)<size && arr[2*i+1]<arr[2*i+1+1] )
			child=2*i+1+1; //choose the bigger child right child
		else
			child=2*i+1;    // left child
		if ( tmp<arr[child] )       // in order to build max heap
			arr[i]=arr[child];
		else
			break;
	}
	arr[i]=tmp;
}

void swap (int *a, int *b)
{
	int tmp=*a;
	*a=*b;
	*b=tmp;
}


void heapsort (int *arr,int size)
{
	for (int i=size/2;i>=0;i--)     // build max heap
		percdown(arr,i,size);
	
	for (int i=size-1;i>0;i--)
	{
		swap(&arr[0],&arr[i]);
		percdown(arr,0,i);
	}
	
}


void mergesort (int *arr, int size)
{
	int *tmp_arr=(int *)malloc(sizeof(int)*size);
	msort(arr,tmp_arr,0,size-1);
	free(tmp_arr);
}

void msort (int *arr,int *tmp_arr,int left,int right)
{
	int mi=(right+left)/2;
	if (left<right)
	{
		msort(arr,tmp_arr,left,mi);
		msort(arr,tmp_arr,mi+1,right);
		merge(arr,tmp_arr,left,mi,right);
	}
	/*
	else
		return;
	*/
	// it is a recursive base
}

void merge (int *arr,int *tmp_arr,int left,int mi,int right)
{
	int i=left,j=mi+1;
	for (int k=left;k<=right;k++)
	{
		if ( (j>right) || ( i<=mi && arr[i]<=arr[j] ) )
		{
			tmp_arr[k]=arr[i];
			i++;
		}
		else if ( (i>mi) || ( j<=right && arr[i]>arr[j] ) )
		{
			tmp_arr[k]=arr[j];
			j++;
		}
	}

	for (int k=left;k<=right;k++)
		arr[k]=tmp_arr[k];
}



void quicksort (int *arr, int size)
{
	q_sort(arr,0,size-1);
}

int median3 (int *arr,int left,int right)
{
	int mi=(left+right)/2;

	// sort the arr[left],arr[mi] and arr[right]
	if (arr[left]>arr[mi])
		swap(&arr[left],&arr[mi]);
	if (arr[left]>arr[right])
		swap(&arr[left],&arr[right]);
	if (arr[mi]>arr[right])
		swap(&arr[mi],&arr[right]);
	
	swap(&arr[mi],&arr[right-1]);
	return arr[right-1];
}

void q_sort (int *arr,int left,int right)
{
	int i,j;
	int pivot;
	if ( left+3<=right )
	{
		pivot=median3(arr,left,right);

		i=left;
		j=right-1;
		for ( ; ; )
		{
			while(arr[++i]<pivot) { }
			while(arr[--j]>pivot) { }
			if (i<j)
				swap(&arr[i],&arr[j]);
			else
				break;
		}
		swap(&arr[i],&arr[right-1]);

		q_sort(arr,left,i-1);
		q_sort(arr,i+1,right);
	}
	else                                                //  the else case is when the number of array elements is <=3 .
		insertionsort(arr+left,right-left+1);       //  use insertionsort method to sort the remain array
}

void insertionsort (int *arr,int size)
{
	int i,j;
	for (i=1;i<=size-1;i++)
	{
		int tmp=arr[i];
		for (j=i;j>=1;j--)
		{
			if (arr[j-1]>tmp)
				arr[j]=arr[j-1];
			else
				break;
		}
		arr[j]=tmp;
	}
}





















