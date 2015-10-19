#ifndef __DLIST_H__
#define __DLIST_H__

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class DList_Node
{
public:
	T data;
	DList_Node<T> *prev;
	DList_Node<T> *next;
};

template <typename T>
class DList
{
public:
	DList();
	~DList();

	void insert(DList_Node<T> *pos, T t);   // 在pos后面插入
	void insert_last(T t);     // 在表尾insert
	void insert_first(T t);    // 在表头insert
	void remove(T t);  // 删除第一个t值
	void remove_all();
	void update(DList_Node<T> *pos, T t);
	DList_Node<T> *find(T t);
	T getdata(DList_Node<T> *pos);
	void print();

	DList<T> &operator=(const DList<T> &dlist);

	DList_Node<T> *header;
	DList_Node<T> *tail;   // 为了方便从后边遍历
	int amount;
};

template <typename T>
DList<T>::DList() : header(NULL), tail(NULL), amount(0)
{
}

template <typename T>
DList<T>::~DList()
{
	remove_all();
}

template <typename T>
void DList<T>::insert(DList_Node<T> *pos, T t)       // 默认pos是存在的，不是NULL
{
	DList_Node<T> *p = new DList_Node<T>;
	p->data = t;
	DList_Node<T> *tmp = pos->next;
	if ( tmp != NULL )
	{
		p->prev = pos;
		pos->next = p;
		p->next = tmp;
		tmp->prev = p;
	}
	else    //  tmp is NULL, and pos is the last node
	{
		p->prev = pos;
		pos->next = p;
		p->next = tmp;
		tail = p;      // 插入p后， tail is p
	}
	++amount;
}

template <typename T>
void DList<T>::insert_last(T t)
{
	DList_Node<T> *p = new DList_Node<T>;
	p->data = t;
	if ( amount == 0 )   //  空表情况
	{
		header = p;
		tail = p;
		p->prev = NULL;
		p->next = NULL;
	}
	else
	{
		tail->next = p;
		p->prev = tail;
		p->next = NULL;
		tail = p;
	}
	++amount;
}

template <typename T>
void DList<T>::insert_first(T t)
{
	DList_Node<T> *p = new DList_Node<T>;
	p->data = t;
	if ( amount == 0 )
	{
		header = p;
		tail = p;
		p->prev = NULL;
		p->next = NULL;
	}
	else
	{
		p->prev = NULL;
		p->next = header;
		header->prev = p;
		header = p;
	}
	++amount;
}

template <typename T>
void DList<T>::remove(T t)
{
	// 有四种情况：1.表只有一个元素时中；2.头中；3.尾中；4.中间中
	DList_Node<T> *p = header;
	while ( p != NULL )
	{
		if ( p->data == t )
		{
			if ( amount == 1)
			{
				delete(p);
				p = NULL;
				header = NULL;
				tail = NULL;
			}
			else if ( p = header )
			{
				DList_Node<T> *tmp = p->next;
				delete(p);
				p = NULL;
				tmp->prev = NULL;
				header = tmp;
			}
			else if ( p == tail )
			{
				DList_Node<T> *tmp = p->prev;
				delete(p);
				p = NULL;
				tmp->next = NULL;
				tail = tmp;
			}
			else
			{
				DList_Node<T> *prev_tmp = p->prev;
				DList_Node<T> *next_tmp = p->next;
				delete(p);
				p = NULL;
				prev_tmp->next = next_tmp;
				next_tmp->prev = prev_tmp;
			}
			--amount;
			break;
		}
		p = p->next;
	}
}

template <typename T>
void DList<T>::remove_all()
{
	DList_Node<T> *tmp;
	while ( header != NULL )
	{
		tmp = header->next;
		delete(header);
		header = tmp;
		header->prev = NULL;
		--amount;
	}
	tail = NULL;
}

template <typename T>
void DList<T>::update(DList_Node<T> *pos, T t)
{
	pos->data = t;
}

template <typename T>
DList_Node<T> * DList<T>::find(T t)   // 找出从头开始的第一个
{
	DList_Node<T> *p = header;
	while ( p != NULL )
	{
		if ( p->data == t )
			break;
		p = p->next;
	}
	return p;
}

template <typename T>
T DList<T>::getdata(DList_Node<T> *pos)
{
	return pos->data;
}

template <typename T>
void DList<T>::print()
{
	DList_Node<T> *p = header;
	while ( p != NULL )
		cout << p->data << " ";
	cout << endl;
}

template <typename T>
DList<T> &DList<T>::operator=(const DList<T> &dlist)
{
	this->remove_all();
	DList_Node<T> *p = dlist.header;
	while ( p != NULL )
	{
		T insert_data = p->data;
		this->insert_last(insert_data);
		p = p->next;
	}
	return *this;
}


#endif
