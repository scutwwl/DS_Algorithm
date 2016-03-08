void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void BubbleSort(int *arr, int size)
{
	for (int i = 1; i < size; i++)
	{
		bool flag = 1;
		for (int j = 0; j < size-i; j++)
		{
			if (arr[j] > arr[j+1])
			{
				swap(arr[j], arr[j+1]);
				flag = 0;
			}
		}
		if (flag)
			break;
	}
}

void InsertionSort(int *arr, int size)
{
	for (int i = 1; i < size; i++)
	{
		int tmp = arr[i];
		int j;
		for (j = i-1; j >=0; j--)
		{
			if (tmp < arr[j])
				arr[j+1] = arr[j];
			else
				break;
		}
		arr[j+1] = tmp;
	}
}

void SelectionSort(int *arr, int size)
{
	for (int i = size-1; i > 0; --i)
	{
		int max = arr[0];
		int max_index = 0;
		for (int j = 0; j <= i; ++j)
		{
			if (arr[j] > max)
			{
				max = arr[j];
				max_index = j;
			}
		}
		swap(arr[max_index], arr[i]);
	}
}

void ShellSort(int *arr, int size)  //一共三个循环，第一个是增量的变化，第二个从第increment个开始的每个元素，第三个是二中元素的前面每隔increment的元素
{
	for (int increment = size/2; increment > 0; increment /= 2)
	{
		for (int i = increment; i < size; ++i)
		{
			int tmp = arr[i];
			int j;
			for (j = i-increment; j >= 0; j -= increment)
			{
				if (tmp < arr[j])
					arr[j+increment] = arr[j];
				else
					break;
			}
			arr[j+increment] = tmp;
		}
	}
}

void PercDown(int *arr, int size, int pos)
{
	// 建的是最大堆
	int tmp_data = arr[pos];
	while (2 * pos + 1 < size)
	{
		int max_child = 2 * pos + 1;
		if (2 * pos + 2 < size && arr[2*pos+1] < arr[2*pos+2])
			max_child = 2 * pos + 2;
		if (tmp_data < arr[max_child])
		{
			arr[pos] = arr[max_child];
			pos = max_child;
		}
		else
			break;
	}
	arr[pos] = tmp_data;
}

void HeapSort(int *arr, int size)   // 由于这里的arr是从0开始的，所以对于某个点i而言，其父节点是(i-1)/2，是这样得出来的：(i+1)/2 - 1 = (i-1)/2
{
	// build the heap, 注意 heapsort建的是最大堆
	for (int i = (size/2 - 1); i >= 0; --i)
		PercDown(arr, size, i);
	// 排序
	for (int j = size-1; j > 0; --j)
	{
		swap(arr[j], arr[0]);
		PercDown(arr, j, 0);
	}
}

void merge(int *arr, int lo, int mi, int hi)
{
	int *A = new int [mi-lo];
	for (int i = 0; i < mi-lo; ++i)
		A[i] = arr[lo+i];
	int *B = arr + mi;
	int A_index = 0, B_index = 0;
	for (int i = lo; i < hi; ++i)
	{
		if (B_index >= hi-mi || (A_index < mi-lo && A[A_index] < B[B_index]))
			arr[i] = A[A_index++];
		else
			arr[i] = B[B_index++];
	}
}

void mergesort(int *arr, int lo, int hi)   // arr[lo,hi) 左闭右开
{
	if (hi - lo == 1)
		return;
	if (hi - lo == 2)
	{
		if (arr[lo] > arr[lo+1])
			swap(arr[lo], arr[lo+1]);
		return;
	}

	int mi = (lo + hi) / 2;
	mergesort(arr, lo, mi);
	mergesort(arr, mi, hi);
	merge(arr, lo, mi, hi);
}

void MergeSort(int *arr, int size)
{
	mergesort(arr, 0, size);
}

int three_seg_change_pos(int *arr, int lo, int hi)
{
	int mi = (lo + hi) / 2;
	if (arr[lo] > arr[mi])
		swap(arr[lo], arr[mi]);
	if (arr[mi] > arr[hi-1])
		swap(arr[mi], arr[hi-1]);
	if (arr[lo] > arr[mi])
		swap(arr[lo], arr[mi]);
	swap(arr[hi-2], arr[hi-1]);
	swap(arr[mi], arr[hi-1]);
	return arr[hi-1];
}

void qsort(int *arr, int lo, int hi)
{
	int pivot = three_seg_change_pos(arr, lo, hi);
	if (hi - lo <= 5)
	{
		mergesort(arr, lo, hi);
		return;
	}
	int i = lo, j = hi-2;
	while (1)
	{
		while(arr[i++] < pivot) { }
		while(arr[j--] > pivot) { }
		if (i > j)
			break;
		else
			swap(arr[i], arr[j]);
	}
	swap(arr[i], arr[hi-1]);
	qsort(arr, lo, i);
	qsort(arr, i+1, hi);
}


void QuickSort(int *arr, int size)
{
	qsort(arr, 0, size);
}


