#ifndef __BINARY_HEAP_H__
#define __BINARY_HEAP_H__

#include <iostream>
using std::cout;

template <typename T>
class Binary_Heap
{
public:
	Binary_Heap(int n);
	~Binary_Heap();

	void insert(T data);
	T delete_min();
	T delete_data(int position);
	bool is_full();
	int decrease_key(int position, T decrement);   // return new position
	int increase_key(int position, T increment);   // return new position

	int capacity;
	int size;
	T *elements_arr;
};

template <typename T>
Binary_Heap<T>::Binary_Heap(int n) : capacity(n), size(0), elements_arr(new T[n+1])
{
}

template <typename T>
Binary_Heap<T>::~Binary_Heap()
{
	delete[] elements_arr;
}

template <typename T>
bool Binary_Heap<T>::is_full()
{
	return (capacity == size);
}

template <typename T>
void Binary_Heap<T>::insert(T data)
{
	if (is_full())
	{
		cout << "the heap is full.\n";
		return;
	}
	int index = size + 1;
	while ( index > 1 )
	{
		if ( data <= elements_arr[index/2] )
			break;
		else
			elements_arr[index] = elements_arr[index/2];
		index /= 2;
	}
	elements_arr[index] = data;
	size++;
}

template <typename T>
T Binary_Heap<T>::delete_min()
{
	int index = 1;
	T min_data = elements_arr[1];
	T adjust_data = elements_arr[size];
	while ( 2 * index <= size )
	{
		//先找出最小儿子
		int min_child;
		if ( 2*index+1 > size || elements_arr[2*index] <= elements_arr[2*index+1] )
			min_child = 2 * index;
		else
			min_child = 2 * index + 1;
		//比较最小儿子和adjust_data
		if ( adjust_data < elements_arr[min_child] )
			break;
		else
		{
			elements_arr[index] = elements_arr[min_child];
			index = min_child;
		}
	}
	elements_arr[index] = adjust_data;
	size--;
}

template <typename T>
int Binary_Heap<T>::decrease_key(int position, T decrement)
{
	T new_data = elements_arr[position] - decrement;
	int new_position = position;
	while ( new_position > 1 )
	{
		if ( new_data >= elements_arr[new_position / 2] )
			break;
		else
		{
			elements_arr[new_position] = elements_arr[new_position / 2];
			new_position /= 2;
		}
	}
	elements_arr[new_position] = new_data;
	return new_position;
}

template <typename T>
int Binary_Heap<T>::increase_key(int position, T increment)
{
	T new_data = elements_arr[position] + increment;
	int new_position = position;
	while ( 2 * new_position <= size )
	{
		//找出最小儿子
		int min_child;
		if ( 2 * new_position + 1 > size || elements_arr[2*new_position] <= elements_arr[2*new_position+1] )
			min_child = 2 * new_position;
		else
			min_child = 2 * new_position + 1;
		//比较当前元素和最小儿子
		if ( new_data <= elements_arr[min_child] )
			break;
		else
		{
			elements_arr[new_position] = elements_arr[min_child];
			new_position = min_child;
		}
	}
	elements_arr[new_position] = new_data;
	return new_position;
}

template <typename T>
T Binary_Heap<T>::delete_data(int position)
{
	T data = elements_arr[position];
	//将该位置元素提到根处，作用如 decrease_key(position,无穷大)
	while ( position > 1 )
	{
		elements_arr[position] = elements_arr[position / 2];
		position /= 2;
	}
	elements_arr[position] = data;
	
	delete_min();
	
	return data;
}

#endif
