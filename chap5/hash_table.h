#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "../chap3/list.h"
#include <iostream>

template <typename T>
class Hash_Table_v1         // 使用分离链表法
{
public:
	Hash_Table_v1(int size);
	~Hash_Table_v1();
	bool is_full_half();
	void insert_data(T data);
	void delete_data(T data);
	Node<T> *find(T data);

	int TableSize;
	int count;
	List<T> **list_array;    // array中存的是整个链表的指针

private:
	int Hash(T data);
};

template <typename T>
Hash_Table_v1<T>::Hash_Table_v1(int size) : TableSize(size), count(0), list_array(NULL)
{
	list_array = new List<T> *[TableSize];
	for (int i=0; i<TableSize; i++)
		list_array[i] = NULL;
}

template <typename T>
Hash_Table_v1<T>::~Hash_Table_v1()
{
	for (int i=0; i<TableSize; i++)
	{
		if (list_array[i] == NULL)
			continue;
		list_array[i]->remove_all();
	}
	delete[] list_array;
	list_array = NULL;
	TableSize = 0;
}

template <typename T>
bool Hash_Table_v1<T>::is_full_half()
{
	return (count / TableSize > 0.5);
}

template <typename T>
void Hash_Table_v1<T>::insert_data(T data)
{
	int i = Hash(data);
	if ( list_array[i] == NULL )
		list_array[i] = new List<T>;
	list_array[i]->insert_first(data);
	count++;
}

template <typename T>
void Hash_Table_v1<T>::delete_data(T data)
{
	int i = Hash(data);
	list_array[i]->remove(data);
	count--;
}

template <typename T>
int Hash_Table_v1<T>::Hash(T data)
{
	return (data % TableSize);
}

template <typename T>
Node<T> *Hash_Table_v1<T>::find(T data)
{
	int i = Hash(data);
	if ( list_array[i] != NULL )
		return list_array[i]->find(data);
	else
		return NULL;
}


/***************************************************/

template <typename T>
class Hash_Entry
{
public:
	T data;
	enum state {Empty, Used, Deleted};
};

template <typename T>
class Hash_Table_v2            // 使用开放定址法
{
public:
	Hash_Table_v2(int size);
	~Hash_Table_v2();
	bool is_full_half();
	void insert_data(T data);
	void delete_data(T data);    // 必须是懒惰删除，不能一般删除，因为如果一般删除后就无法find到与该删除点冲突的其他绕过的点
	Hash_Entry<T> *find(T data);
	void rehash();

	int TableSize;
	int count;
	Hash_Entry<T> *hash_entry_array;

private:
	int Hash(T data);
	int hash2(T data);     // used for doublehash,  hash2=R-data%R, R=7, R must be smaller than TableSize
	void insert_data_linear(T data);    //线性探测
	void insert_data_square(T data);    //平方探测
	void insert_data_doublehash(T data);  //双散列
	void delete_data_linear(T data);
	void delete_data_square(T data);
	void delete_data_doublehash(T data);
	Hash_Entry<T> *find_linear(T data);
	Hash_Entry<T> *find_square(T data);
	Hash_Entry<T> *find_doublehash(T data);
};


template <typename T>
Hash_Table_v2<T>::Hash_Table_v2(int size) : TableSize(size), count(0), hash_entry_array(new Hash_Entry[TableSize])
{
	for (int i=0; i<TableSize; i++)
		hash_entry_array[i].state = Empty;
}

template <typename T>
Hash_Table_v2<T>::~Hash_Table_v2()
{
	delete[] hash_entry_array;
}

template <typename T>
bool Hash_Table_v2<T>::is_full_half()
{
	return ( count / TableSize > 0.5 );
}

template <typename T>
void Hash_Table_v2<T>::insert_data(T data)
{
	insert_data_linear(data);
	//insert_data_square(data);
}

template <typename T>
void Hash_Table_v2<T>::insert_data_linear(T data)
{
	int index = Hash(data);
	while ( hash_entry_array[index].state != Empty )
	{
		if (++index >= TableSize)
		       index -= TableSize;
	}
	hash_entry_array[index].data = data;
	hash_entry_array[index].state = Used;
	count++;
}

template <typename T>
void Hash_Table_v2<T>::insert_data_square(T data)
{
	int i = 0;      //  f(i) = f(i-1) + 2i - 1
	int index = Hash(data);
	while ( hash_entry_array[index].state != Empty )
	{
		index += 2 * (++i) - 1;
		if ( index >= TableSize )
			index -= TableSize;
	}
	hash_entry_array[index].data = data;
	hash_entry_array[index].state = Used;
	count++;
}

template <typename T>
void Hash_Table_v2<T>::insert_data_doublehash(T data)
{
	int index = Hash(data);
	int h2 = hash2(data);
	while ( hash_entry_array[index].state != Empty )
	{
		index += h2;
		if ( index >= TableSize )
			index -= TableSize;
	}
	hash_entry_array[index].data = data;
	hash_entry_array[index].state = Used;
	count++;
}

template <typename T>
int Hash_Table_v2<T>::Hash(T data)
{
	return ( data % TableSize );
}

template <typename T>
int Hash_Table_v2<T>::hash2(T data)
{
	int R = 7;
	return ( R - data % R );
}

template <typename T>
Hash_Entry<T> *Hash_Table_v2<T>::find(T data)
{
	return find_linear(data);    // 必须与insert的方式对应
	//return find_square(data);
	//return find_doublehash(data);
}

template <typename T>
Hash_Entry<T> *Hash_Table_v2<T>::find_linear(T data)
{
	int index = Hash(data);
	while ( hash_entry_array[index].state != Empty )
	{
		if ( hash_entry_array[index].data == data )
			break;
		if ( ++index >= TableSize )
			index -= TableSize;
	}
	if ( hash_entry_array[index].state == Used )
		return &hash_entry_array[index];
	else
		return NULL;
}

template <typename T>
Hash_Entry<T> *Hash_Table_v2<T>::find_square(T data)
{
	int i = 0;
	int index = Hash(data);
	while ( hash_entry_array[index].state != Empty )
	{
		if ( hash_entry_array[index].data == data )
			break;
		index += 2 * (++i) - 1;
		if ( index >= TableSize )
			index -= TableSize;
	}
	if ( hash_entry_array[index].state == Used )
		return &hash_entry_array[index];
	else
		return NULL;
}

template <typename T>
Hash_Entry<T> *Hash_Table_v2<T>::find_doublehash(T data)
{
	int index = Hash(data);
	int h2 = hash2(data);
	while ( hash_entry_array[index].state != Empty )
	{
		if ( hash_entry_array[index].data == data )
			break;
		index += h2;
		if ( index >= TableSize )
			index -= TableSize;
	}
	if ( hash_entry_array[index].state == Used )
		return &hash_entry_array[index];
	else
		return NULL;
}

template <typename T>
void Hash_Table_v2<T>::delete_data(T data)
{
	delete_data_linear(data);
	//delete_data_square(data);
	//delete_data_doublehash(data);
}

template <typename T>
void Hash_Table_v2<T>::delete_data_linear(T data)   // 默认是存在且状态是Used
{
	Hash_Entry<T> *hp = find_linear(data);
	hp->state = Deleted;
	count--;
}

template <typename T>
void Hash_Table_v2<T>::delete_data_square(T data)
{
	Hash_Entry<T> *hp = find_square(data);
	hp->state = Deleted;
	count--;
}

template <typename T>
Hash_Entry<T> *Hash_Table_v2<T>::delete_data_doublehash(T data)
{
	Hash_Entry<T> *hp = find_doublehash(data);
	hp->state = Deleted;
	count--;
}

template <typename T>
void Hash_Table_v2<T>::rehash()
{
	int oldsize = TableSize;
	int oldarray = hash_entry_array;
	TableSize *= 2;
	Hash_Entry<T> *hp = new Hash_Entry<T>[TableSize];
	hash_entry_array = hp;
	count = 0;
	for (int i=0; i<oldsize; i++)
	{
		if (oldarray[i].state == Used)
			insert_data(oldarray[i].data);
	}
}


#endif
