// 中缀换为后缀
// 在操作符栈中，当准备进入栈的元素比栈顶的元素的优先级小或相等时，就会一直pop出栈顶元素，直到准备入栈的元素的优先级比栈顶元素大或者是栈已空。
// 对于相等优先级就po出来是为了保证从左到右的结合律
// 只能处理单个字母作为一个数，例如infix a+b*c+d*e 转换为suffix abc*+de*+，不能处理具体实验的数字例子，因为是逐个字符遍历string的。

#include "stack.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;

map<char,int> operators = { {'+',0}, {'-',1}, {'*',2}, {'/',3} };
// 在全局区域中不能这样初始化。因为这样相当于再动态分配一个空间，不符合全局的静态初始化属性。
//operators_index['+'] = 0;
//operators['-'] = 1;
//operators['*'] = 2;
//operators['/'] = 3;

/*      +  -  * /
 *   +  t  t  t t
 *   -  t  t  t t
 *   *  f  f  t t
 *   /  f  f  t t
 *
 *   就是说 vector[x][y] = t 表示x优先级小于或等于y是true
 */

vector<bool> jia = {true, true, true, true};
vector<bool> jian = {true, true, true, true};
vector<bool> cheng = {false, false, true, true};
vector<bool> chu = {false, false, true, true};
vector<vector<bool>> priority = { jia, jian, cheng, chu };
// 与上面的map同理
//priority.push_back(jia);
//priority.push_back(jian);
//priority.push_back(cheng);
//priority.push_back(chu);

string &infix_to_suffix(const string &infix, string &suffix)
{
	Stack<char> operator_stack;
	for (auto c : infix)
	{
		if ( c=='+' || c=='-' || c=='*' || c=='/' )
		{
			while ( !operator_stack.is_empty() && operator_stack.top()!='(' && priority[operators[c]][operators[operator_stack.top()]] )  // 当栈不为空才能pop，而且只能pop到（处或空栈
			{
				suffix += operator_stack.top();
				operator_stack.pop();
			}
			operator_stack.push(c);
		}
		else if ( c == ')' )
		{
			while ( operator_stack.top() != '(' )
			{
				suffix += operator_stack.top();
				operator_stack.pop();
			}
			operator_stack.pop();  // 把‘(’pop出来
		}
		else if ( c == '(' )
			operator_stack.push(c);
		else  // c is a\b\c etc
			suffix += c;
	}
	while ( !operator_stack.is_empty() )
	{
		suffix += operator_stack.top();
		operator_stack.pop();
	}

	return suffix;
}

int main ()
{
	string infix, suffix;
	cout << "The infix is : ";
	cin >> infix;
	cout << "The suffix is : " << infix_to_suffix(infix, suffix) << endl;
	return 0;
}


