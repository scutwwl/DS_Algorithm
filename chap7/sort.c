// the implement of sort.h
// 从小到大排序

void InsertionSort(int *arr, int size)   // 思想：将某个待排序的元素插到已排序的序列中
{
	for (int i = 1; i < size; i++)
	{
		int j;
		for (j = i-1; j >= 0; j--)
		{
			if ( arr[j] > arr[i] )
				arr[j+1] = arr[j];
			else
				break;
		}
		arr[j+1] = arr[i];
	}
}


void BubbleSort(int *arr, int size)   //思想：每一次比较都要冒泡交换，直到末尾
{
	for (int i = 1; i < size; i++)
	{
		int flag = 1;
		for (int j = 0; j < size-i; j++)
		{
			if (arr[j] > arr[j+1])
			{
				flag = 0;
				int tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
		if (flag)
			break;
	}
}


void SelectionSort(int *arr, int size)   // 思想：遍历一遍找出最大的，再与末尾的元素交换
{
	for (int i = size-1; i > 0; i--)
	{
		int max = arr[0];
		int max_index = 0;
		for (int j = 1; j <= i; j++)
		{
			if ( max <= arr[j] )
			{
				max = arr[j];
				max_index = j;
			}
		}
		int tmp = arr[i];
		arr[i] = max;
		arr[max_index] = tmp;
	}
}


void ShellSort(int *arr, int size)
{
	for (int increment = size/2; increment > 0; increment /= 2)
	{
		for (int i = increment; i < size; i++)
		{
			int j;
			int value = arr[i];
			for (j = i - increment; j >= 0; j -= increment)
			{
				if (arr[j] > value)
					arr[j+increment] = arr[j];
				else
					break;
			}
			arr[j+increment] = value;
		}
	}
}


void HeapSort(int *arr, int size)
{
	// build the max heap
	for (int i = size/2 - 1; i >= 0; i--)
		percdown(arr, size, i);

	for (int i = size - 1; i > 0; i--)
	{
		// swap arr[0] and arr[i]
		int tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;
		// percdown the arr[0]
		percdown(arr, i, 0);
	}
}

void percdown(int *arr, int size, int position)
{
	int leftchild, maxchild;
	int value = arr[position];
	while ((leftchild = 2*position+1) < size)   // 存在左儿子
	{
		maxchild = leftchild;
		if (leftchild+1 < size && arr[leftchild] < arr[leftchild+1])   //存在右儿子且右儿子比左儿子大
			maxchild = leftchild + 1;
		if (value < arr[maxchild])
		{
			arr[positon] = arr[maxchild];
			position = maxchild;
		}
		else
			break;
	}
	arr[position] = value;
}


void MergeSort(int *arr, int lo, int hi)  // 左闭右开
{
	// 递归基
	if (lo + 2 == hi)   //只剩两个
	{
		if (arr[lo] > arr[lo+1])
		{
			int tmp = arr[lo];
			arr[lo] = arr[lo+1];
			arr[lo+1] = tmp;
		}
		return;
	}
	if (lo + 3 == hi)   //只剩三个
	{
		if (arr[lo] > arr[lo+1])
		{
			int tmp = arr[lo];
			arr[lo] = arr[lo+1];
			arr[lo+1] = tmp;
		}
		if (arr[lo+2] < arr[lo])
		{
			int tmp = arr[lo+2];
			arr[lo+2] = arr[lo+1];
			arr[lo+1] = arr[lo];
			arr[lo] = tmp;
		}
		else if (arr[lo+2] < arr[lo+1])
		{
			int tmp = arr[lo+2];
			arr[lo+2] = arr[lo+1];
			arr[lo+1] = tmp;
		}
		return;
	}

	int mi = (lo + hi) / 2;
	MergeSort(arr, lo, mi);
	MergeSort(arr, mi, hi);
	merge(arr, lo, mi, hi);
}

void merge(int *arr, int lo, int mi, int hi)
{
	int *A = new int[mi-lo];
	for (int i = 0; i < mi-lo; i++)
		A[i] = arr[lo+i];
	int *B = arr + mi;

	int A_index = 0, B_index = 0;
	for (int j = lo; j < hi; j++)
	{
		if (A_index < mi-lo && (B_index >= hi-mi || A[A_index] <= B[B_index]))
			arr[j] = A[A_index++];
		else
			arr[j] = B[B_index++];
	}
	delete[] A;
}


void QuickSort(int *arr, int size)
{
	qsort(arr, 0, size);
}

void qsort(int *arr, int lo, int hi)   // 左闭右开
{
	int cutoff = 5;
	if ( lo + cutoff >= hi )
	{
		InsertionSort(arr+lo, hi-lo);
		return;
	}

	//三数中值分割
	int mi = (lo + hi) / 2;
	if (arr[lo] > arr[mi])
	{
		int tmp = arr[mi];
		arr[mi] = arr[lo];
		arr[lo] = tmp;
	}
	if (arr[hi-1] < arr[lo])
	{
		int tmp = arr[hi-1];
		arr[hi-1] = arr[mi];
		arr[mi] = arr[lo];
		arr[lo] = tmp;
	}
	else if (arr[hi-1] < arr[mi])
	{
		int tmp = arr[hi-1];
		arr[hi-1] = arr[mi];
		arr[mi] = tmp;
	}

	//  交换mi和次尾元素
	int tmp1 = arr[mi];
	arr[mi] = arr[hi-2];
	arr[hi-2] = tmp1;

	int mi_value = arr[hi-2];
	int i = lo+1, j = hi-3;
	while (1)
	{
		while(arr[i] < mi_value) i++;
		while(arr[j] > mi_value) j++;
		if (i < j)
		{
			int tmp = arr[j];
			arr[j] = arr[i];
			arr[i] = tmp;
			i++;
			j++;
		}
		else
			break;
	}
	// swap i和hi-2元素
	int tmp2 = arr[hi-2];
	arr[hi-2] = arr[i];
	arr[i] = tmp2;

	qsort(arr, lo, i);
	qsort(arr, i+1, hi);
}
	










































