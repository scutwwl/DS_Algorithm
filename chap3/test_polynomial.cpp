#include "polynomial.h"
#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;

int main ()
{
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	Polynomial p1(s1);
	Polynomial p2(s2);
	Polynomial p3;
	cout << "Polynomial 1 : ";
	p1.print();
	cout << endl;
	cout << "Polynomial 2 : ";
	p2.print();
	cout << endl;
	//p3 = p1 + p2;
	//cout << "the add_result : ";
	//p3.print();
	//cout << endl;
	p3 = p1 * p2;
	cout << "the multiply result : ";
	p3.print();
	cout << endl;
	return 0;
}
