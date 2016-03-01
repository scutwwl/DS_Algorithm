#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "../list/slist.h"

template <typename T>
class Hash_Table_v1                   // v1用于分离链表法
{
public:
	Hash_Table_v1(int size);
	~Hash_Table_v1();

	List_Node<T> *find(T data);
	void insert_data(T data);
	void delete_data(T data);

private:
	SList<T> **listarray;
	int count;
	int table_size;

	int Hash(T data);
};

template <typename T>
Hash_Table_v1<T>::Hash_Table_v1(int size) : listarray(nullptr), count(0), table_size(size)
{
	listarray = new SList<T> *[table_size];
	for (int i = 0; i < table_size; i++)
		listarray[i] = nullptr;
}

template <typename T>
Hash_Table_v1<T>::~Hash_Table_v1()
{
	for (int i = 0; i < table_size; i++)
	{
		if (listarray[i] != nullptr)
		{
			delete listarray[i];   //会调用链表类的析构函数
			listarray[i] = nullptr;
		}
	}
	delete []listarray;
	listarray = nullptr;
	count = 0;
	table_size = 0;
}

template <typename T>
int Hash_Table_v1<T>::Hash(T data)
{
	return (data % table_size);

template <typename T >
void Hash_Table_v1<T>::insert_data(T data)
{
	int index = Hash(data);
	if (listarray[index] == nullptr)
		listarray[index] = new SList<T>;
	listarray[index]->insert_first(data);
	++count;
}

template <typename T>
void Hash_Table_v1<T>::delete_data(T data)
{
	int index = Hash(data);
	if (listarray[index] != nullptr)
	{
		listarray[index]->remove_data(data);
		--count;
	}
}

template <typename T>
List_Node<T> *Hash_Table_v1<T>::find(T data)
{
	int index = Hash(data);
	if (listarray[index] != nullptr)
		return listarray[index]->find(data);
	else
		return nullptr;
}


















#endif
