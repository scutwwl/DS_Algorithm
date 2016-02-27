#ifndef __SLIST_H__
#define __SLIST_H__

#include <iostream>

template <typename T>
class List_Node
{
public:
	T data;
	List_Node<T> *next;
};

template <typename T>
class SList
{
public:
	SList() : head(nullptr), n_count(0) { }
	~SList();

	void insert_first(T data);
	void insert_last(T data);
	void insert(T data, List_Node<T> *pos);   //在pos后面插入data
	void remove_first();
	void remove_last();
	void remove(List_Node<T> *pos);     //删除pos处的node
	void remove_all();
	void update(List_Node<T> *pos, T newdata);
	List_Node<T> *find(T data);
	void display();
	
public:
	List_Node<T> *head;
	int n_count;
};


template <typename T>
SList<T>::~SList()
{
	remove_all();
}


template <typename T>
void SList<T>::insert_first(T data)
{
	List_Node<T> *new_node = new List_Node<T>;
	new_node->data = data;

	new_node->next = head;
	head = new_node;
	++n_count;
}


template <typename T>
void SList<T>::insert_last(T data)
{
	List_Node<T> *new_node = new List_Node<T>;
	new_node->data = data;
	new_node->next = nullptr;

	//处理空链表的情况
	if (head == nullptr)
		head = new_node;
	else
	{
		List_Node<T> *tmp = head;
		while (tmp->next != nullptr)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	++n_count;
}


template <typename T>
void SList<T>::insert(T data, List_Node<T> *pos)   //在pos后面插入data
{
	List_Node<T> *new_node = new List_Node<T>;
	new_node->data = data;

	List_Node<T> *tmp = pos->next;
	pos->next = new_node;
	new_node->next = tmp;
	++n_count;
}


template <typename T>
void SList<T>::remove_first()
{
	if (head == nullptr)
		return;

	List_Node<T> *remove_node = head;
	head = head->next;
	delete remove_node;
	remove_node = nullptr;
	--n_count;
}


template <typename T>
void SList<T>::remove_last()
{
	if (head == nullptr)
		return;
	if (n_count == 1)
	{
		delete head;
		head = nullptr;
		--n_count;
		return;
	}

	List_Node<T> *prev_node;
	List_Node<T> *last_node = head;
	while (last_node->next != nullptr)
	{
		prev_node = last_node;
		last_node = last_node->next;
	}
	prev_node->next = nullptr;
	delete last_node;
	last_node = nullptr;
	--n_count;
}


template <typename T>
void SList<T>::remove(List_Node<T> *pos)    //删除pos处的node
{
	if (pos == head)
		remove_first();
	else
	{
		List_Node<T> *prev_node;
		List_Node<T> *tmp = head;
		while (tmp != pos)
		{
			prev_node = tmp;
			tmp = tmp->next;
		}
		List_Node<T> *next_node = tmp->next;
		prev_node->next = next_node;
		delete tmp;
		tmp = nullptr;
		pos = nullptr;
		--n_count;
	}
}


template <typename T>
void SList<T>::remove_all()
{
	while (n_count != 0)
		remove_first();
}

template <typename T>
void SList<T>::update(List_Node<T> *pos, T newdata)
{
	pos->data = newdata;
}


template <typename T>
List_Node<T> *SList<T>::find(T data)   //找到就返回位置指针，没找到就返回nullptr
{
	List_Node<T> *found_node = head;
	while (found_node != nullptr)
	{
		if (found_node->data == data)
			break;
		else
			found_node = found_node->next;
	}
	return found_node;
}


template <typename T>
void SList<T>::display()
{
	List_Node<T> *tmp = head;
	while (tmp != nullptr)
	{
		std::cout << tmp->data << " ";
		tmp = tmp->next;
	}
	std::cout << std::endl;
}



#endif
