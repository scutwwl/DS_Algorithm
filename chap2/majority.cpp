// 2.19 practice
// findmajority_v1 is the recursion version
// findmajority_v2 is the simple version

#include <iostream>
using std::cout;
using std::endl;

int findmajority_v1(int *arr, int size)
{
	// this is the base case, in recursion size will 0 or 1
	if (size <= 1)
		return arr[0];

	int len = 0;
	for (int i=0; i<size; i+=2)
	{
		// deal with the odd case
		if ( i == size-1 )
		{
			arr[len] = arr[i];
			++len;
			return findmajority_v1(arr, len);
		}

		if ( arr[i] == arr[i+1] )
			arr[len++] = arr[i];
		
		if ( i == size-2 )
			return findmajority_v1(arr, len);
	}
}

int findmajority_v2(const int *arr, int size)
{
	int majority;
	int occurence = 0;  // occurence represents the occurence of the current majority
	for (int i=0; i<size; i++)
	{
		if (occurence == 0)
		{
			majority = arr[i];
			++occurence;
		}
		else if ( majority == arr[i] )
			++occurence;
		else
			--occurence;
	}
	return majority;
}

void verified_majority(const int *arr, int size, int majority)
{
	int num = 0;
	for (int i=0; i<size; i++)
	{
		if (arr[i] == majority)
			++num;
	}
	if (num >= size/2)
		cout << "There is a majority : " << majority << endl;
	else
		cout << "There is not a majority. " << endl;
}

int main ()
{
	int arr[] = {3, 3, 4, 2, 4, 4, 2, 4, 4};
	const int brr[] = {3, 3, 4, 2, 4, 4, 2, 4, 4};  // 这是因为findmajority_v1改变了原来数组arr的元素，不能再用了。除非在findmajority_v1中使用swap调换元素，保持原来元素的数目。使统计主要元素的结果不会受到影响。
	cout << "The findmajority_v1: " << endl;
	verified_majority(brr, 9, findmajority_v1(arr, 9));
	cout << "The findmajority_v2: " << endl;
	verified_majority(brr, 9, findmajority_v2(brr, 9));
	return 0;
}
