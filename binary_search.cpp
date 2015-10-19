#include <iostream>
using namespace std;

//binary_search()返回不大于e的最大数的位置
int binary_search(int *arr, int lo, int hi, int e)
{
	if ( lo+1 == hi )
	{
		if ( e >= arr[lo] )
			return lo;
		else
			return lo-1;
	}

	int mi = (lo + hi) >> 1;
	if ( e >= arr[mi] )
		binary_search(arr, mi, hi, e);
	else
		binary_search(arr, lo, mi, e);
}

int main ()
{
	int arr[] = {1, 2, 2, 2, 3, 3, 4, 4, 5, 5};
	int i;
	while (cin >> i)
		cout << binary_search(arr, 0, 10, i) << endl;
	return 0;
}
