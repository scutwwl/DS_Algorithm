#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

bool incre_num(string &num)
{
	bool is_overflow = false;
	char carry = 1;
	int n = num.size() -1;
	while (carry)
	{
		if (n < 0)
		{
			is_overflow = true;
			break;
		}
		num[n] += carry;
		carry = 0;
		if (num[n] - '0' > 9)
		{
			carry = 1;
			num[n] = '0';
		}
		--n;
	}
	return is_overflow;
}

void print_num(string &num)
{
	int index = 0;
	while(num[index] == '0')
	{
		++index;
		continue;
	}
	while(index < num.size())
		cout << num[index++];
	cout << endl;
}

void print1tondigit(int n)
{
	if (n <= 0)
		return;
	string number(n, '0');
	while (!incre_num(number))
		print_num(number);
}

int main()
{
	print1tondigit(5);
	return 0;
}
