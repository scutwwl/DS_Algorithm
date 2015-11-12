#ifndef __BINOMIAL_QUEUE_H__
#define __BINOMIAL_QUEUE_H__

#include <cmath>

#define MAX_TREE_NUM 10
#define CAPACITY pow(2.0, MAX_TREE_NUM)

template <typename T>
class BinomialTree_Node
{
public:
	T data;
	BinomialTree_Node<T> *left_child;
	BinomialTree_Node<T> *sibling;
};

template <typename T>
class Binomial_Quene
{
public:
	Binomial_Quene

#endif
