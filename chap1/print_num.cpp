#include <iostream>
using namespace std;

void print_digit(int digit)
{
	cout << digit;
}

void print(int num)
{
	if (num >= 10)
		print(num / 10);
	print_digit(num % 10);
}

int main ()
{
	int num = 213342;
	print(num);
	cout << endl;
	return 0;
}
