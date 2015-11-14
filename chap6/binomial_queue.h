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
	BinomialTree<T> *tree1 = NULL, *tree2 = NULL;  //carry表示要进位的树
	BinomialTree<T> *carry = new BinomialTree<T>;
	carry->root = NULL;
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
		switch( !!tree1 + 2 * !!tree2 + 4 * !!carry->root )    // 3位bit来表示这些树是否NULL
		{
		case 0:
		case 1:
			break;
		case 2:
			tree_arr[i] = new BinomialTree<T>;
			tree_arr[i]->root = tree2->root;
			tree2->root = NULL;
			break;
		case 4:
			tree_arr[i] = new BinomialTree<T>;
			tree_arr[i]->root = carry->root;
			carry->root = NULL;
			break;
		case 3:
			tree1->merge(tree2);  //里面已经将tree2->root置为NULL
			carry->root = tree1->root;
			//清楚tree_arr[i]位置上的树
			tree_arr[i] = NULL;
			tree1->root = NULL;
			delete tree1;
			tree1 = NULL;
			break;
		case 5:
			tree1->merge(carry);  //已经将carry->root置NULL
			//类似于case 3
			carry->root = tree1->root;
			tree_arr[i] = NULL;
			tree1->root = NULL;
			delete tree1;
			tree1 = NULL;
			break;
		case 6:
			tree2->merge(carry);
			carry->root = tree2->root;
			tree2->root = NULL;
			break;
		case 7:
			tree1->merge(tree2);
			BinomialTree_Node<T> *tmp = tree1->root;
			tree1->root = carry->root;
			carry->root = tmp;
		}
	}
	//清空bq
	for (int i=0, j=1; j<=bq.current_size; i++, j*=2)
	{
		bq.tree_arr[i]->remove_tree(bq.tree_arr[i]->root);
		BinomialTree<T> *p = bq.tree_arr[i];
		delete p;
		bq.tree_arr[i] = NULL;
	}
	bq.current_size = 0;
	//删除carry树
	delete carry;
	
}

template <typename T>
void Binomial_Quene<T>::insert_data(T data)
{
	Binomial_Quene<T> *bq_ptr = new Binomial_Quene<T>;
	bq_ptr->tree_arr[0] = new BinomialTree<T>;
	BinomialTree_Node<T> *node_p = new BinomialTree_Node<T>;
	node_p->data = data;
	node_p->next = NULL;
	node_p->sibling = NULL;
	bq_ptr->tree_arr[0]->root = node_p;
	merge(*bq_ptr);
}

template <typename T>
T Binomial_Quene<T>::delete_min()
{
	T min_data = tree_arr[0]->root->data;
	int min_index = 0;
	for (int i=1, j=2; j<=current_size; i++, j*=2)
	{
		if ( tree_arr[i]->root->data < min_data )
		{
			min_data = tree_arr[i]->root->data;
			min_index = i;
		}
	}
	// construct H''
	Binomial_Quene<T> bq;
	bq.current_size = (1 << min_index) - 1;  // 减1是减去根节点
	BinomialTree_Node<T> *tmp = tree_arr[i]->root->next;
	for (int i=min_index-1; i>=0; i--)
	{
		BinomialTree<T> *new_tree = new BinomialTree<T>;
		new_tree->root = tmp;
		bq.tree_arr[i] = new_tree;
		tmp = tmp->sibling;
	}
	//删除min_index处树的根节点
	BinomialTree_Node<T> *deleted_node = tree_arr[i]->root;
	tree_arr[i]->root = NULL;
	delete tree_arr[i];
	tree_arr[i] = NULL;
	//合并
	merge(bq);

	return min_data;
}

#endif
