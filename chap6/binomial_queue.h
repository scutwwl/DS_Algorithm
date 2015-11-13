#ifndef __BINOMIAL_QUEUE_H__
#define __BINOMIAL_QUEUE_H__

#include <cmath>
#include "../chap4/multiple_tree.h"         // 使用多叉树来实现，而不重新再造新的结构，二项队列是二项数（多叉树）的数组（或者链表实现）
#include <iostream>

using std::cout;
using std::endl;

template <typename T> using BinomialTree_Node = MTree_Node<T>;

#define MAX_TREE_NUM 10
#define CAPACITY pow(2.0, MAX_TREE_NUM)

template <typename T>
class BinomialTree : public MTree<T>
{
public:
	void merge(BinomialTree &bt);  // 两个大小相等的树合并
};

template <typename T>
void BinomialTree<T>::merge(BinomialTree &bt)  // 默认merge的两方都各自至少有一个节点，bt的root置null，本类的root更新为生成新树的root
{
	BinomialTree_Node<T> *tmp;
	if ( root->data <= bt.root->data )
	{
		tmp = root->next;
		root->next = bt.root;
		root->next->sibling = tmp;   // 递减地排列子树
	}
	else
	{
		tmp = bt.root->next;
		bt.root->next = root;
		bt.root->next->sibling = tmp;
		root = bt.root;     // 将弄好的root作为该类的root
	}
	bt.root = NULL;
}


template <typename T>
class Binomial_Quene
{
public:
	Binomial_Quene();
	~Binomial_Quene();

	void merge(Binomial_Quene<T> &bq);
	void insert_data(T data);
	T delete_min();

	int current_size;
	BinomialTree<T> *tree_arr;
};

template <typename T>
Binomial_Quene<T>::Binomial_Quene() : current_size(0), tree_arr(new BinomialTree<T> *[MAX_TREE_NUM])
{
	for (int i=0; i<MAX_TREE_NUM; i++)
		tree_arr[i] = NULL;
}

template <typename T>
Binomial_Quene<T>::~Binomial_Quene()
{
	if (current_size == 0)
		return;
	for (int i=0, j=1; j<=current_size; i++, j*=2)   // 本来循环可以是i<MAX_TREE_NUM的，但是引入j后可以减少循环的次数
	{
		if (tree_arr[i] != NULL)
			tree_arr[i]->remove_tree(tree_arr[i]->root);
	}
	current_size = 0;
	delete[] tree_arr;
	tree_arr = NULL;
}

template <typename T>
void Binomial_Quene<T>::merge(Binomial_Quene<T> &bq)
{
	BinomialTree<T> *tree1 = NULL, *tree2 = NULL, *carry = NULL;  //carry表示要进位的树
	current_size += bq.current_size;
	if (current_size > CAPACITY)
	{
		cout << "the current_size is big and lack of memory." << endl;
		return;
	}
	for (int i=0, j=1; j<=current_size; i++, j*=2)
	{
		tree1 = tree_arr[i];
		tree2 = bq.tree_arr[i];
		switch( !!tree1 + 2 * !!tree2 + 4 * !!carry )    // 3位bit来表示这些树是否NULL
		{
		case 0:
		case 1:
			break;
		case 2:
			root = tree2;

	


#endif
