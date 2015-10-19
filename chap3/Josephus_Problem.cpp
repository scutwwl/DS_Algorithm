#include <iostream>
#include "circle_list.h"
using std::cout;
using std::cin;
using std::endl;

int Josephus_compute(int size, int m)
{
	CList<int> clist;
	for (int i=1; i<=size; i++)
		clist.insert_last(i);

	CList_Node<int> *p_node = clist.tail;
	p_node = clist.move_next(p_node);  // 为了和下面配合

	CList_Node<int> *target_remove;
	while ( clist.amount != 1 )
	{
		for (int j=2; j<=m; j++)
			p_node = clist.move_next(p_node);
		target_remove = p_node;
		p_node = clist.move_next(p_node);   // 把这步放到remove之前是因为remove之后当前p_node会失效，无法move_next
		clist.remove_at(target_remove);
	}
	if ( p_node != clist.tail )
	{
		cout << "error in the last p_node!=clist.tail." << endl;
		return -1;
	}
	else
		return clist.tail->data;
}

int main ()
{
	int m, size;
	cout << "The circle size is : ";
	cin >> size;
	cout << "The number m is : ";
	cin >> m;
	cout << "The remainer is : " << Josephus_compute(size, m) << endl;
	return 0;
}
	
