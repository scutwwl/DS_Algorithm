#ifndef __STACK_H__
#define __STACK_H__

#include "list.h"

template <typename T>
class Stack : public List<T>    // List头作为栈顶
{
public:
	T top();
	void pop();
	void push(T data);
	int size();
	bool is_empty();
};

template <typename T>
T Stack<T>::top()
{
	return List<T>::header->data;
}

template <typename T>
void Stack<T>::pop()
{
	List<T>::remove_first();
}

template <typename T>
void Stack<T>::push(T data)
{
	List<T>::insert_first(data);
}

template <typename T>
int Stack<T>::size()
{
	return List<T>::amount;
}

template <typename T>
bool Stack<T>::is_empty()
{
	return ( List<T>::amount == 0 );
}


#endif
