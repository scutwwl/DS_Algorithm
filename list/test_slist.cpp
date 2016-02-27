#include <iostream>
#include "slist.h"

using std::cout;
using std::endl;

int main()
{
	SList<int> sl;

	sl.insert_first(1);
	sl.display();

	sl.insert_last(2);
	sl.display();

	sl.insert_last(3);
	sl.display();

	sl.remove_last();
	sl.display();

	sl.remove_first();
	sl.display();

	cout << sl.find(2) << endl;
	
	sl.insert(4, sl.find(2));
	sl.display();

	sl.remove(sl.find(4));
	sl.display();

	sl.remove_all();

	return 0;
}
