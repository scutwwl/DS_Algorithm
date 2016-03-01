#include <iostream>
#include "slist.h"

using std::cout;
using std::endl;

template <typename T>
void overturn_slist(SList<T> &sl)
{
	List_Node<T> *current = sl.head;
	List_Node<T> *prev_node = nullptr;
	while (current != nullptr)
	{
		List_Node<T> *pro_node = current->next;
		current->next = prev_node;
		prev_node = current;
		current = pro_node;
	}
	sl.head = prev_node;
}


template <typename T>
void overturn_slist_recur(List_Node<T> *node, SList<T> &sl)
{
	if (node == nullptr)
		return;
	if (node->next == nullptr)
	{
		sl.head = node;
		return;
	}

	overturn_slist_recur(node->next, sl);
	node->next->next = node;
	node->next = nullptr;
}


int main()
{
	SList<int> sl;
	sl.insert_last(1);
	//sl.insert_last(2);
	//sl.insert_last(3);
	//sl.insert_last(4);
	//sl.insert_last(5);
	sl.display();

	overturn_slist(sl);
	//overturn_slist_recur(sl.head, sl);
	sl.display();

	return 0;
}


