#ifndef __CIRCLE_LIST_H__
#define __CIRCLE_LIST_H__

#include "list.h"
template <typename T> using CList_Node = Node<T>;     // template type alias

#include <iostream>
using std::endl;
using std::cout;

template <typename T>
class CList
{
public:
	CList();
	~CList();

	void insert(CList_Node<T> *pos, T t);
	void insert_last(T t);
	void remove(T t);
	void remove_all();
	void remove_at(CList_Node<T> *pos);
	CList_Node<T> *move_next(CList_Node<T> *pos);
	void update(CList_Node<T> *pos, T t);
	CList_Node<T> *find(T t);   // 从头开始找到第一个t值
	CList_Node<T> *find_prev(CList_Node<T> *pos);
	T getdata(CList_Node<T> *pos);
	void print();

	CList<T> &operator=(const CList<T> &clist);

	CList_Node<T> *tail;       // 使用尾指针来代表一个循环链表，这样的话访问头和尾的时间都是O(1)
	int amount;
};

template <typename T>
CList<T>::CList() : tail(NULL), amount(0)
{
}

template <typename T>
CList<T>::~CList()
{
	remove_all();
}

template <typename T>
void CList<T>::insert(CList_Node<T> *pos, T t)
{
	CList_Node<T> *new_p = new CList_Node<T>;
	new_p->data = t;
	CList_Node<T> *tmp = pos->next;
	pos->next = new_p;
	new_p->next = tmp;
	if (pos == tail)
		tail = new_p;
	++amount;
}

template <typename T>
void CList<T>::insert_last(T t)
{
	CList_Node<T> *new_p = new CList_Node<T>;
	new_p->data = t;
	if ( amount == 0 )
	{
		tail = new_p;
		new_p->next = new_p;
	}
	else
	{
		CList_Node<T> *header = tail->next;
		tail->next = new_p;
		new_p->next = header;
		tail = new_p;
	}
	++amount;
}

template <typename T>
void CList<T>::remove(T t)    // 从头开始找到第一个t值，默认循环表不为空
{
	CList_Node<T> *p = tail->next;
	CList_Node<T> *prev_p = tail;
	//使用amount来循环
	int size = amount;
	for(int i=1; i<=size; i++)
	{
		if ( p->data == t )
		{
			if ( amount == 1)
			{
				delete(p);
				p = NULL;
				tail = NULL;
			}
			else
			{
				CList_Node<T> *next_p = p->next;
				if ( p == tail )
					tail = prev_p;
				delete(p);
				p = NULL;
				prev_p->next = next_p;
			}
			--amount;
			break;
		}
		prev_p = p;
		p = p->next;
	}
}

template <typename T>
void CList<T>::remove_all()
{
	if (amount == 0)
		return;
	CList_Node<T> *header = tail->next;
	int size = amount;
	for(int i=1; i<=size; i++)
	{
		if (amount == 1)
		{
			delete(tail);
			tail = NULL;
			--amount;
		}
		else
		{
			tail->next = header->next;
			delete(header);
			header = tail->next;
			--amount;
		}
	}
}

template <typename T>
void CList<T>::remove_at(CList_Node<T> *pos)
{
	if ( amount == 1 )
	{
		delete(tail);
		tail = NULL;
		--amount;
	}
	else
	{
		CList_Node<T> *prev_pos = find_prev(pos);
		CList_Node<T> *next_pos = pos->next;
		if (prev_pos == NULL) 
			cout << "prev NULL" << endl;
		prev_pos->next = next_pos;
		if ( pos == tail )
			tail = prev_pos;
		delete(pos);
		pos = NULL;
		--amount;
	}
}

template <typename T>
CList_Node<T> *CList<T>::move_next(CList_Node<T> *pos)   // 默认不是空表
{
	return pos->next;
}

template <typename T>
void CList<T>::update(CList_Node<T> *pos, T t)
{
	pos->data = t;
}


template <typename T>
CList_Node<T> *CList<T>::find_prev(CList_Node<T> *pos)
{
	CList_Node<T> *p = tail->next;
	for (int i=1; i<=amount; i++)
	{
		if ( p->next == pos )
			return p;
		p = p->next;
	}
	return NULL;
}


template <typename T>
CList_Node<T> *CList<T>::find(T t)      // 找出从头开始第一个t值
{
	CList_Node<T> *p = tail->next;
	for (int i=1; i<=amount; i++)
	{
		if ( p->data == t )
			return p;
		p = p->next;
	}
	return NULL;
}

template <typename T>
T CList<T>::getdata(CList_Node<T> *pos)
{
	return pos->data;
}

template <typename T>
void CList<T>::print()
{
	CList_Node<T> *p = tail->next;
	for (int i=1; i<=amount; i++)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

template <typename T>
CList<T> &CList<T>::operator=(const CList<T> &clist)
{
	this->remove_all();
	CList_Node<T> *p_clist = clist.tail->next;
	for (int i=1; i<=clist.amount; i++)
	{
		this->insert_last(p_clist->data);
		++this->amount;
		p_clist = p_clist->next;
	}
	return *this;
}




#endif
