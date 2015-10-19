#include "polynomial.h"
#include <cctype>   // 使用isdigit(c)
#include <stack>
#include <iostream>
#include <map>
using std::cout;
using std::endl;
using std::map;
using std::stack;

int ctoi(char c)
{
	int dif = c - '0';
	return dif;
}

void fillin_coff_exp(stack<char> &expr_stack, List<poly_node> &expr_list)
{
	int count = 1;
	int number = 0;
	int coff, exp;
	char c;
	while ( !expr_stack.empty() )
	{
		if ( isdigit( c=expr_stack.top() ) )
		{
			number += ctoi(c) * count;
			count *= 10;
		}
		else if ( expr_stack.top() == 'x' )   // 当遇到x后，就开始计算coff，所以需要重置number和count
		{
			exp = number;
			number = 0;
			count = 1;
		}
		expr_stack.pop();
	}
	coff = number;

	poly_node *p = new poly_node;
	p->coff = coff;
	p->exp = exp;
	expr_list.insert_last(*p);
}

// 通过解析表达式来生成List， 表达式形式必须为3x^2
List<poly_node> &generate_list(const string &expression, List<poly_node> &expr_list)
{
	// 使用栈，不断push， 当遇到+或-时就开始不断pop直到栈空，才能继续push，相当于以+或-分隔，一部分一部分地处理
	stack<char> expr_stack;
	int size = expression.size();
	for (int i=0; i<size; i++)
	{
		char c = expression[i];

		if ( c!='+' && c!='-' )
		{
			// 在将某部分入栈时，需要添加一些东西以生成完整形式 ax^b
			if ( c=='x' )
			{
				if ( i==0 || !isdigit(expression[i-1]) )
					expr_stack.push('1');
				expr_stack.push('x');
				if ( i==size-1 || expression[i+1]!='^' )
				{
					expr_stack.push('^');
					expr_stack.push('1');
				}
			}
			else if ( isdigit(c) )
			{
				expr_stack.push(c);
				if ( i==size-1 || expression[i+1]=='+' || expression[i+1]=='-' )
				{
					expr_stack.push('x');
					expr_stack.push('^');
					expr_stack.push('0');
				}
			}
			else
				expr_stack.push(c);
		}
		else
		{
			fillin_coff_exp(expr_stack, expr_list);
		}
		
		if ( c == '-' )
			expr_stack.push(c);  // 用于下部分的负系数
	}
	// 处理剩下的栈元素
	fillin_coff_exp(expr_stack, expr_list);

	if ( !expr_stack.empty() )
		cout << "error in generate_list(), the remain stack isn't empty." << endl;

	return expr_list;
}

Polynomial::Polynomial(const string &expression) 
{
	generate_list(expression, this->poly_list);
}

Polynomial::Polynomial()
{
}

Polynomial operator+(const Polynomial &p1, const Polynomial &p2)
{
	Polynomial add_result;
	// 用于遍历表
	auto p1_node = p1.poly_list.header;
	auto p2_node = p2.poly_list.header;
	while ( p1_node!=NULL || p2_node!=NULL )
	{
		poly_node *p = new poly_node;
		if ( (p2_node==NULL && p1_node!=NULL) ||  p1_node->data.exp > p2_node->data.exp )
		{
			p->exp = p1_node->data.exp;
			p->coff = p1_node->data.coff;
			p1_node = p1_node->next;
		}
		else if ( (p1_node==NULL && p2_node!=NULL) ||  p2_node->data.exp > p1_node->data.exp )
		{
			p->exp = p2_node->data.exp;
			p->coff = p2_node->data.coff;
			p2_node = p2_node->next;
		}
		else  // p1_node->data.exp == p2_node->data.exp
		{
			p->exp = p1_node->data.exp;
			p->coff = p1_node->data.coff + p2_node->data.coff;
			p1_node = p1_node->next;
			p2_node = p2_node->next;
		}
		add_result.poly_list.insert_last(*p);
	}
	return add_result;
}

Polynomial operator*(const Polynomial &p1, const Polynomial &p2)
{
	Polynomial multi_result;
	// 使用map来统计乘法结果，exp作为key，coff作为value。
	map<int, int> exp_coff;
	auto p1_node = p1.poly_list.header;
	int p1_exp, p1_coff, p2_exp, p2_coff, new_exp, new_coff;
	while ( p1_node!=NULL )
	{
		p1_exp = p1_node->data.exp;
		p1_coff = p1_node->data.coff;
		auto p2_node = p2.poly_list.header;
		while ( p2_node!=NULL )
		{
			p2_exp = p2_node->data.exp;
			p2_coff = p2_node->data.coff;
			new_exp = p1_exp + p2_exp;
			new_coff = p1_coff * p2_coff;
			exp_coff[new_exp] += new_coff;
			p2_node = p2_node->next;
		}
		p1_node = p1_node->next;
	}

	// 倒序遍历map，因为map是按key从小到大排的，而我们的polynomial是从大到小的
	auto map_rit = exp_coff.crbegin();
	while ( map_rit != exp_coff.crend() )
	{
		poly_node *p = new poly_node;
		p->exp = map_rit->first;
		p->coff = map_rit->second;
		multi_result.poly_list.insert_last(*p);
		++map_rit;
	}
	
	return multi_result;
}

Polynomial & Polynomial::operator=(const Polynomial &p)
{
	this->poly_list = p.poly_list;
	return *this;
}

void Polynomial::print()
{
	auto p = poly_list.header;
	while ( p != NULL )
	{
		if ( p->data.coff != 1 || (p->data.coff == 1 && p->data.exp == 0) )
			cout << p->data.coff;

		if ( (p->data.exp > 1) || (p->data.exp < 0) )
			cout << "x^" << p->data.exp;
		else if ( p->data.exp == 1 )
			cout << 'x';

		if ( (p->next != NULL)  &&  (p->next->data.coff > 0) )
			cout << '+';

		p = p->next;
	}
}
	























		


















