#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

void n_select_m(const string &str, vector<char> &str_vec, int n, int m)    //从n个字符中选m个出来，组合问题，n>m，并打印出来了
{
	if(m == 0)
	{
		for(auto ch : str_vec)
			cout << ch;
		cout << endl;
		return;
	}
	if(n == m)
	{
		for(int i = 0; i < n; ++i)
			cout << str[i];
		for(auto ch : str_vec)
			cout << ch;
		cout << endl;
		return;
	}
	//选中处于n-1处的元素
	str_vec.push_back(str[n-1]);
	n_select_m(str, str_vec, n-1, m-1);
	str_vec.pop_back();

	//没选中
	n_select_m(str, str_vec, n-1, m);
}

void print_nsm(const string &str, int n, int m)
{
	vector<char> str_vec;
	n_select_m(str, str_vec, n, m);
}

int main()
{
	string str_test("abcde");
	print_nsm(str_test, str_test.size(), 4);
	return 0;
}
