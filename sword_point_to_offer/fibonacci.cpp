#include <iostream>
using std::cout;
using std::endl;

int fibonnaci(int n)
{
	if (n == 0 || n == 1)
		return n;
	int a = 0, b = 1;
	for (int i = 2; i <= n; ++i)
	{
		b = a + b;
		a = b - a;
	}
	return b;
}

int main()
{
	int n = 10;
	while (n >= 0)
	{
		cout << "f(" << n << ") = " << fibonnaci(n) << endl;
		--n;
	}
	cout << "f(40) = " << fibonnaci(40) << endl;
	return 0;
}
