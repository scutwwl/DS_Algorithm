#include <iostream>
#include "quene.h"

using std::cout;
using std::endl;

int main()
{
	Quene<int> q;

	q.enquene(1);
	q.enquene(2);
	q.enquene(3);
	q.enquene(4);
	q.enquene(5);
	q.display();

	cout << "the dequene element is " << q.dequene() << endl;
	cout << "the dequene element is " << q.dequene() << endl;
	cout << endl;
	q.display();

	q.make_empty();
	cout << "the bool is_empty() is " << q.is_empty() << endl;

	return 0;
}
	
