#include "list.h"

int main ()
{
	List<int> list;
	list.insert_last(1);
	list.insert_last(2);
	list.insert_last(3);
	list.print();
	return 0;
}

