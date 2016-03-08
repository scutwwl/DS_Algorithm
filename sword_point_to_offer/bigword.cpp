#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stable_sort;
using std::find_if;
using std::for_each;
using std::unique;
using std::sort;

void elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(), words.end(),
			[](const string &a, const string &b)
			{ return a.size() < b.size(); });
	auto wc = find_if(words.begin(), words.end(),
			[sz](const string &a)
			{ return a.size() >= sz; });

	auto count = words.end() - wc;
	cout << count << " element size bigger than sz" << endl;

	for_each(wc, words.end(),
			[](const string &a)
			{ cout << a << endl; });
	cout << endl;
}


int main ()
{
	vector<string> words = {"the", "quick", "red", "fox", "jumps",
		"over", "the", "slow", "red", "turtle"};
	int sz;
	cout << "sz = ";
	cin >> sz;
	biggies(words, sz);
	return 0;
}
