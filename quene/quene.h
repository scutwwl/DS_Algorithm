#ifndef __QUENE_H__
#define __QUENE_H__

#include <cstdlib>
#include <iostream>
#include "../list/slist.h"

template <typename T> using Quene_Node = List_Node<T>;

template <typename T>
class Quene
{
public:
	Quene();
	~Quene();

	void enquene(T data);
	T dequene();
	void make_empty();
	bool is_empty();
	void display();

private:
	Quene_Node<T> *front;
	Quene_Node<T> *rear;
	int n_count;
};


template <typename T>
Quene<T>::Quene() : front(nullptr), rear(nullptr), n_count(0) { }

template <typename T>
Quene<T>::~Quene()
{
	make_empty();
}


template <typename T>
void Quene<T>::enquene(T newdata)
{
	Quene_Node<T> *tmp = new Quene_Node<T>;
	tmp->data = newdata;

	if (is_empty())
	{
		tmp->next = nullptr;
		front = tmp;
		rear = tmp;
	}
	else
	{
		rear->next = tmp;
		rear = tmp;
	}
	++n_count;
}


template <typename T>
T Quene<T>::dequene()
{
	if (is_empty())
	{
		std::cout << "the quene is empty, cannot dequene." << std::endl;
		exit(1);
	}
	else if (front == rear)
	{
		T de_data = front->data;
		delete front;
		front = rear = nullptr;
		--n_count;
		return de_data;
	}
	else
	{
		Quene_Node<T> *tmp = front;
		T de_data = front->data;
		front = front->next;
		delete tmp;
		tmp = nullptr;
		--n_count;
		return de_data;
	}
}


template <typename T>
void Quene<T>::make_empty()
{
	while (!is_empty())
		dequene();
}


template <typename T>
bool Quene<T>::is_empty()
{
	return (n_count ? false : true);
}


template <typename T>
void Quene<T>::display()
{
	Quene_Node<T> *tmp = front;
	while (tmp != nullptr)
	{
		std::cout << tmp->data << " ";
		tmp = tmp->next;
	}
	std::cout << std::endl;
}


#endif
