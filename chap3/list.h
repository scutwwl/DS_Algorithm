#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
using std::cout;
using std::endl;

template<typename T>
class Node
{
public:
	T data;
	Node<T> *next;
};

template<typename T>
class List
{
public:
	List();
	~List();

	Node<T> *find(T t);  // 查，有则返回该节点指针，无则返回NULL
	void update(Node<T> *pos, T t);   // 改
	void remove(T t);   // 删除第一个t值
	void remove_all();
	void remove_first();
	void insert_first(T t);
	void insert(Node<T> *pos, T t);   // 在pos位置后面插入t值
	void insert_last(T t);   // 在list的最后insert
	T getdata(Node<T> *pos);
	void print();

	List<T> &operator=(const List<T> &list);

	Node<T> *header;
	int amount;
};

//之所以把function的定义放在头文件中，是因为template在实例化使用时需要见到function的具体定义，所以就要把它包含到头文件中。具体看C++ Primer p656 template compilation

template<typename T>
List<T>::List() : header(NULL), amount(0)
{
}

template <typename T> List<T>::~List()
{
	if (amount != 0)
	{
		while (header != NULL)
		{
			Node<T> *tmp = header->next;
			delete(header);
			header = tmp;
			amount--;
		}
	}
}

template <typename T> Node<T> * List<T>::find(T t)
{
	Node<T> *p = header;
	while (p != NULL)
	{
		if (p->data == t)
			return p;
		else
			p = p->next;
	}
	return NULL;
}

template <typename T> void List<T>::update(Node<T> *pos, T t)
{
	pos->data = t;
}

template <typename T> void List<T>::remove(T t)
{
	Node<T> *p = header;
	Node<T> *previous;
	while (p != NULL)
	{
		if ( p->data == t )
		{
			Node<T> *tmp = p->next;
			if (p == header)
			{
				delete(p);
				p = NULL;
				header = tmp;
			}
			else
			{
				delete(p);
				p=NULL;
				previous->next = tmp;
			}
			amount--;
			break;
		}
		previous = p;
		p = p->next;
	}
}

template <typename T>
void List<T>::remove_all()
{
	if (amount == 0)
		return;
	while ( header != NULL )
	{
		Node<T> *tmp = header->next;
		delete(header);
		header = tmp;
		--amount;
	}
}

template <typename T>
void List<T>::remove_first()
{
	if ( amount == 0 )
		return;
	Node<T> *p = header->next;
	delete(header);
	header = p;
	--amount;
}

template <typename T>
void List<T>::insert_first(T t)
{
	Node<T> *new_p = new Node<T>;
	new_p->data = t;
	new_p->next = header;
	header = new_p;
	++amount;
}

template <typename T>
void List<T>::insert(Node<T> *pos, T t)
{
	Node<T> *post = pos->next;
	Node<T> *p = new Node<T>;
	p->data = t;
	p->next = post;
	pos->next = p;

	amount++;
}

template <typename T> void List<T>::insert_last(T t)
{
	Node<T> *last = header;
	Node<T> *p = new Node<T>;
	p->data = t;
	p->next = NULL;
	// 处理空表的情况
	if (header == NULL)
	{
		header = p;
		amount++;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = p;

	amount++;
}


template <typename T> T List<T>::getdata(Node<T> *pos)
{
	return pos->data;
}

template <typename T> void List<T>::print()
{
	Node<T> *p = header;
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

template <typename T>
List<T> & List<T>::operator=(const List<T> &list)
{
	this->remove_all();
	this->amount = list.amount;
	Node<T> *p = list.header;
	while ( p != NULL )
	{
		T insert_data = p->data;
		this->insert_last(insert_data);
		p = p->next;
	}
	return *this;
}
		


#endif
