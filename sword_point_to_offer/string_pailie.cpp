#include <iostream>
#include <string>
using std::endl;
using std::cout;
using std::string;

void swap(char &a, char &b)
{
	char tmp = a;
	a = b;
	b = tmp;
}

void print_all_str(string &str, int index)
{
	if (index == str.size() - 1)
	{
		cout << str << endl;
		return;
	}
	for (int i = index; i < str.size(); ++i)
	{
		if (str[index] == str[i] && index != i)
			continue;
		swap(str[index], str[i]);
		print_all_str(str, index + 1);
		swap(str[index], str[i]);
	}
}

void print_all_digit(string &number, int n)
{
	if (n == number.size())
	{
		cout << number << endl;
		return;
	}

	for (int i = 0; i < 10; ++i)
	{
		number[n] = '0' + i;
		print_all_digit(number, n+1);
	}
}

int main()
{
	/*
	string str_test("abcde");
	print_all_str(str_test, 0);
	cout << str_test << endl;
	*/
	string number(3, '0');
	print_all_digit(number, 0);
	return 0;
}
