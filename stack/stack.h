#ifndef _STACK_H__
#define _STACK_H__

#include <cstdlib>
#include <iostream>
#include "../list/slist.h"

template <typename T> using Stack_Node = List_Node<T>;

template <typename T>
class Stack
{
public:
	Stack();
	~Stack();

	T top();  // 返回栈顶元素的数据内容
	T pop();  // 从栈顶删除元素并返回该元素的数据内容
	void push(T newdata);
	void make_empty();
	bool is_empty();
	void display();

private:
	Stack_Node<T> *stack_top;
	int n_count;
};


template <typename T>
Stack<T>::Stack() : stack_top(nullptr), n_count(0) {  }


template <typename T>
Stack<T>::~Stack()
{
	make_empty();
}


template <typename T>
T Stack<T>::top()
{
	if (is_empty())
	{
		std::cout << "the stack is empty, cannot return top." << std::endl;
		exit(1);
	}

	return stack_top->data;
}


template <typename T>
T Stack<T>::pop()
{
	if (is_empty())
	{
		std::cout << "the stack is empty, cannot pop()." << std::endl;
		exit(2);
	}

	Stack_Node<T> *tmp = stack_top;
	T tmp_data = tmp->data;
	stack_top = stack_top->next;
	delete tmp;
	tmp = nullptr;
	--n_count;

	return tmp_data;
}

	
template <typename T>
void Stack<T>::push(T newdata)
{
	Stack_Node<T> *new_node = new Stack_Node<T>;
	new_node->data = newdata;
	new_node->next = stack_top;
	stack_top = new_node;
	++n_count;
}


template <typename T>
void Stack<T>::make_empty()
{
	while (!is_empty())
		pop();
}


template <typename T>
bool Stack<T>::is_empty()
{
	return (n_count ? false : true);
}


template <typename T>
void Stack<T>::display()
{
	Stack_Node<T> *tmp = stack_top;
	while (tmp != nullptr)
	{
		std::cout << tmp->data << std::endl;
		tmp = tmp->next;
	}
	std::cout << std::endl;
}


#endif
