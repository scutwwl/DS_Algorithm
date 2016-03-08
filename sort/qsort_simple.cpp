#include <iostream>
using std::cout;
using std::endl;

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void qsort(int *arr, int lo, int hi)
{
	if (hi - lo <= 1)
		return;

	int mark = lo-1;
	for (int i = lo; i < hi; ++i)
	{
		if (arr[i] <= arr[hi-1])
			swap(arr[++mark], arr[i]);
	}
	qsort(arr, lo, mark);
	qsort(arr, mark+1, hi);
}

int main()
{
	int arr[5] = {3, 5, 7, 2 ,4};
	for (int i = 0; i < 5; ++i)
		cout << arr[i] << " ";
	cout << endl;

	qsort(arr, 0, 5);
	for (int i = 0; i < 5; ++i)
		cout << arr[i] << " ";
	cout << endl;
	return 0;
}
