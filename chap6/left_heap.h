#ifndef __LEFT_HEAP_H__
#define __LEFT_HEAP_H__

#include <iostream>

template <typename T>
class LeftHeap_Node
{
public:
	T data;
	LeftHeap_Node<T> *left;
	LeftHeap_Node<T> *right;
	int npl;   // 该点的零路径长
};

template <typename T>
class Left_Heap
{
public:
	Left_Heap();
	~Left_Heap();

	void merge(LeftHeap_Node<T> *&h);  //返回新堆根指针，h堆根指针置为NULL
	void insert_node(T data);
	T delete_min();   // 默认删时堆不为空

	LeftHeap_Node<T> *root;

private:
	LeftHeap_Node<T> *merge(LeftHeap_Node<T> *&h1, LeftHeap_Node<T> *&h2);
	LeftHeap_Node<T> *merge1(LeftHeap_Node<T> *h1, LeftHeap_Node<T> *h2);
};


template <typename T>
Left_Heap<T>::Left_Heap() : root(NULL)
{
}

template <typename T>
Left_Heap<T>::~Left_Heap()   // 总时间是O(NlogN)
{
	while ( root != NULL )
		deletemin();
}

template <typename T>
void Left_Heap<T>::merge(LeftHeap_Node<T> *&h)    // 递归版本
{
	merge(root, h);
}

template <typename T>
LeftHeap_Node<T> *Left_Heap<T>::merge(LeftHeap_Node<T> *&h1, LeftHeap_Node<T> *&h2)  //这个函数的作用是把已经被并掉的旧堆置为NULL，返回新堆的指针，而不需要管究竟新堆是h1还是h2
{
	if ( h1 == NULL )
		return h2;
	if ( h2 == NULL )
		return h1;

	// h1, h2 both exist
	if ( h1->data <= h2->data )
	{
		LeftHeap_Node<T> *result = merge1(h1, h2);
		h2 = NULL;   // h2已经并到h1中去，要把h2置NULL，防止用h2来访问修改已经是h1的内容
	}
	else 
	{
		LeftHeap_Node<T> *result = merge1(h2, h1);
		h1 = NULL;
	}
	return result;
}

template <typename T>
LeftHeap_Node<T> *Left_Heap<T>::merge1(LeftHeap_Node<T> *h1, LeftHeap_Node<T> *h2)
{
	if ( h1->left == NULL )
		h1->left == h2;   // h1->npl为0，这在新建点h1时就已经是这样了。
	else
	{
		h1->right = merge(h1->right, h2);
		if ( h1->left->npl < h1->right->npl )
		{
			// swap left child and right child
			LeftHeap_Node<T> *tmp = h1->left;
			h1->left = h1->right;
			h1->right = tmp;
		}
		h1->npl = h1->right->npl + 1;
	}
	return h1;
}

template <typename T>
void Left_Heap<T>::insert_node(T data)
{
	LeafHeap_Node<T> *new_node = new LeafHeap_Node<T>;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->npl = 0;

	merge(new_node);
}

template <typename T>
T Left_Heap<T>::delete_min()   
{
	LeftHeap_Node<T> *p = root;
	T data = p->data;
	root = merge(root->left, root->right);
	delete p;
	p = NULL;
	return data;
}

	


#endif
