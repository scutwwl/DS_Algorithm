#include <iostream>
using std::cout;
using std::endl;

bool isPalindrome(int x)
{
	if (x < 0)
		return false;
	if (x == 0)
		return true;
	int tmp = x;
	long result = 0;
	while (x > 0)
	{
		result = result * 10 + x % 10;
		x /= 10;
	}
	return (tmp == result);
}

int main()
{
	cout << isPalindrome(10) << endl;
	return 0;
}
