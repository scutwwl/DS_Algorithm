#include <iostream>
using std::endl;
using std::cout;

double power(double base, int exponent)
{
	if (base - 0 > -0.0000001 && base - 0 < 0.0000001)
		return 0;

	if (exponent == 0)
		return 1;
	else if (exponent == 1)
		return base;
	else if (exponent == -1)
		return 1 / base;
	else if (exponent % 2 == 0)
		return power(base * base, exponent / 2);
	else
		return power(base * base, (exponent-1) / 2) * base;
}

int main ()
{
	cout << power(3, -3) << endl;
	cout << power(0, 0) << endl;
	cout << -3/2 << " " << -3%2 << " " << -3/-2 << " " << -3%-2 << " " << 3/-2 << " " << 3%-2 << endl;
	return 0;
}
