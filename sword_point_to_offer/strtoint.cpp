/*
 * 要求：
 * 假如函数参数是指针的话，要检查是否空指针
 * 是否空字符串
 * 正数溢出返回最大值，负数溢出返回最小值
 * 假如最前面有空格，去掉前面的空格再处理
 * 假如中间有其他不是数字的字符，返回前面已经得到的数字， 如“214regdasg2dsg”返回214
 */



#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

bool is_valid;

int strtoint(string str)
{
	long long result = 0;
	is_valid = false;
	string::iterator it = str.begin();

	/*
	if (str == nullptr || *str == '\0')
		return 0;
	*/

	if (str.size() == 0)
		return 0;

	while (*it == ' ')
	{
		++it;
		if (it == str.end())
			return 0;
		continue;
	}

	bool is_minus = false;
	if (*it == '-')
	{
		is_minus = true;
		++it;
	}
	else if (*it == '+')
		++it;

	if (it == str.end())
		return 0;

	while (it != str.end())
	{
		if (*it >= '0' && *it <= '9')
		{
			result = result * 10 + (*it - '0');
			++it;

			if ((!is_minus && result > 0x7fffffff))
				return 0x7fffffff;
			else if (is_minus && (-1 * result) < (signed int)0x80000000)
				return (signed int)0x80000000;
		}
		else
			break;
	}

	is_valid = true;

	return (is_minus ? -1 * result : result);
}

int main()
{
	cout << strtoint("123456") << endl;
	cout << strtoint("") << endl;
	cout << strtoint("+") << endl;
	cout << strtoint("-") << endl;
	cout << strtoint("-123456") << endl;
	cout << strtoint("1234567890123") << endl;
	cout << strtoint("-1234567890123") << endl;
	cout << strtoint("12345e") << endl;
	cout << strtoint("-12345e") << endl;
	return 0;
}
