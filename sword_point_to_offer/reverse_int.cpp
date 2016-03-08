#include <climits>
#include <iostream>
#include <cstdlib>
using std::cout;
using std::endl;

int reverse_int(int x) 
{
	long result = 0;
	while( x)
	{
		result = result * 10 + x % 10;
		x /= 10;
	}
	//if (x < 0)
	//	result *= -1;
	if (result < INT_MIN || result > INT_MAX)
		result = 0;
	return result;
}

int main ()
{
	int a = 1534236469;
	int b = -456;
	cout << reverse_int(a) << " " << reverse_int(b) << endl;
	return 0;
}

