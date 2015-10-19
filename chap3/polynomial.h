#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include "list.h"
#include <string>
using std::string;

struct poly_node
{
	int coff;
	int exp;
};

typedef struct poly_node poly_node;


// 多项式初始化时必须是指数大的在前面
class Polynomial
{
	//  在考虑怎样重载运算符时，是这样想的：
	//  首先是返回类型，本来是使用&引用的，是为了减少复制的开销，但是这会导致加法的结果可以作为左值放在等号左边。而且这样要返回的必须是一个已存在的且被
	//  修改过的Polynomial对象，但是我们想要的是加号两边的对象在运算后都不变，只是生成新的结果对象。所以返回类型是Polynomial而不是引用。
	//  第二个是在选择member function还是friend的形式上，假如选择member function的话，在function里面要Polynomial new_object，运用到Polynomial本身类型，但
	//  由于该类类型还没完全定义好，所以不能这样写，只好使用friend了。
	friend Polynomial operator+(const Polynomial &p1, const Polynomial &p2);
	friend Polynomial operator*(const Polynomial &p1, const Polynomial &p2);
public:
	Polynomial();
	Polynomial(const string &expression);
	Polynomial & operator=(const Polynomial &p);
	void print();

public:
	List<poly_node> poly_list;
};

// 由于类中的friend声明不算是正式声明，所以在类外还有再声明一次
Polynomial operator+(const Polynomial &p1, const Polynomial &p2);
Polynomial operator*(const Polynomial &p1, const Polynomial &p2);

#endif
