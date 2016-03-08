#include <string>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
using std::string;

string zigzag(string s, int numRows)
{
	vector<vector<char>> result;
	int push_count = 0, numCols = 0;
	while (push_count < s.size())
	{
		vector<char> s_col(numRows, '0');
		//判断偶数列还是奇数列
		if (++numCols % 2 == 0)
		{
			for (int i = numRows-2; i >= 1; --i)
			{
				if (push_count == s.size())
				{
					result.push_back(s_col);
					break;
				}
				else
					s_col[i] = s[push_count++];
			}
		}
		else
		{
			for (int i = 0; i < numRows; ++i)
			{
				if (push_count == s.size())
				{
					result.push_back(s_col);
					break;
				}
				else
					s_col[i] = s[push_count++];
			}
		}
		result.push_back(s_col);
	}

	string r_string;
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			cout << result[j][i] << " ";
			if (result[j][i] != '0')
				r_string += result[j][i];
		}
		cout << endl;
	}

	return r_string;
}

int main ()
{
	zigzag("PAYPALISHIRING", 3);
	return 0;
}
