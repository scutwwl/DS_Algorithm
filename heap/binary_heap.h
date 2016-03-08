#ifndef __HEAP_H__
#define __HEAP_H__

#include <iostream>

template <typename T>
class Heap
{
public:
	Heap(int c);
	~Heap();

	void insert_data(T data);
	T delete_min();
	bool is_full();
	bool is_empty();
private:
	int capacity;
	int size;
	T *arr;
};

template <typename T>
Heap<T>::Heap(int c) : capacity(c), size(0), arr(new T [capacity+1]) { }

template <typename T>
Heap<T>::~Heap()
{
	delete []arr;
	arr = nullptr;
	size = 0;
	capacity = 0;
}

template <typename T>
bool Heap<T>::is_full()
{
	return (size == capacity);
}

bool Heap<T>::is_empty()
{
	return size;
}

template <typename T>
void Heap<T>::insert_data(T data)
{
	if (is_full())
	{
		std::cout << "the heap is full, cannot insert." << std::endl;
		return;
	}

	int pos = ++size;
	while (pos != 1)
	{
		if (data < arr[pos/2])
		{
			arr[pos] = arr[pos/2];
			pos /= 2;
		}
		else
			break;
	}
	arr[pos] = data;
}

template <typename T>
T Heap<T>::delete_min()
{
	if (is_empty())
	{
		std::cout << "the heap is empty, cannot delete_min." << std::endl;
		return;
	}

	T return_data = arr[1];
	T tmp_data = arr[size--];
	int pos = 1;
	while (2*pos <= size)
	{
		int min_child = 2 *pos;
		if (2*pos+1 <= size && arr[2*pos+1] < arr[2*pos])
			min_child = 2 * pos + 1;
		if (tmp_data > arr[min_child])
		{
			arr[pos] = arr[min_child];
			pos = min_child;
		}
		else
			break;
	}
	arr[pos] = tmp_data;

	return return_data;
}

#endif
