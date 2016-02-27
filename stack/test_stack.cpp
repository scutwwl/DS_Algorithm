#include <iostream>
#include "stack.h"

using std::cout;
using std::endl;

int main()
{
	Stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.display();

	cout << "the pop element is " << s.pop() << endl;
	cout << endl;
	s.display();

	cout << "the top element is " << s.top() << endl;
	cout << endl;

	s.make_empty();

	cout << "the bool is_empty() is " << s.is_empty() << endl;

	return 0;
}
