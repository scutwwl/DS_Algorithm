// 伪代码
#include <string>
#include "stack.h"
using std::string;

int get_result_suffix (const string &suffix)
{
	Stack<int> number;
	for ( 遍历suffix )
	{
		if ( 该元素是一个完整的数 )
			number.push(该数);
		else   // 相当于该元素是操作符
		{
			int right = number.pop();
			int left = number.pop();
			int result = left 操作符 right;
			number.push(result);
		}
	}

	// 现在栈的唯一元素就是该表达式的结果
	return number.top();
}
