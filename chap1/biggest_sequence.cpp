// 求最大子序列和，测例：-2，11,-4,13,-5,-2，输出20,子序列：11,-4,13
// 思路：维护一些值，当sum加上当前元素大于等于0时就继续加;
// 当遇到正数时更新相关值。当sum加上当前元素小于0时重置相关值。


#include <iostream>
using std::cout;
using std::endl;


int biggest_sequence_simple(int *arr, int size)   //这个简单版本是返回最大的子序列和，但不标记那个序列的起始和终止位置
{
	int thissum = 0, maxsum = 0;
	for (int i = 0; i < size; i++)
	{
		thissum += arr[i];
		if (thissum > maxsum)
			maxsum = thissum;
		else if (thissum < 0)
			thissum = 0;
	}
	return maxsum;
}


void biggest_sequence(int *arr, int size)
{
	int head = -1, tail = -1, sum = 0, max = 0;
	int max_h = head, max_e = tail;
	for (int i=0; i<size; i++)
	{
		if (sum + arr[i] >= 0)
		{
			sum += arr[i];
			if (arr[i] >= 0)
			{
				if (sum >= max)
				{
					max = sum;
					if (head == -1)
						head = i;
					tail = i;
					max_h = head;
					max_e = tail;
				}
			}
		}
		else
		{
			sum = 0;
			head = -1;
			tail = -1;
		}
	}
	if (max_h == -1 || max_e == -1)
		cout << "No biggest sequence, because all numbers are negative." << endl;
	else
	{
		cout << "The biggest sequence is :" << endl;
		for (int j=max_h; j<=max_e; j++)
			cout << arr[j] << " ";
		cout << endl;
		cout << "The max sum is " << max << endl;
	}
	
}

int main ()
{
	int arr[] = {-2,11,-4,13,-5,-2,20,-100,30,1,-1};
	biggest_sequence(arr, 11);
	cout << "the simple version of getting biggest sequence sum is " << biggest_sequence_simple(arr, 11) << endl;
	return 0;
}
