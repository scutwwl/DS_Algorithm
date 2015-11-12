#include "binary_tree.h"
#include <iostream>
using std::cout;
using std::cin;

template <typename T> using BSTree_Node = BTree_Node<T>;

template <typename T>
class BSTree : public BTree<T>
{
public:
	BSTree_Node<T> *insert_node(T data);  // return the root, overload function only differs in parameter list
	BSTree_Node<T> * delete_node(T data);  // return the root
	BSTree_Node<T> *insert_node(T data, BSTree_Node<T> *node);
	BSTree_Node<T> *delete_node(T data, BSTree_Node<T> *node);
	BSTree_Node<T> *find_Max(BSTree_Node<T> *node);
	BSTree_Node<T> *find_Min(BSTree_Node<T> *node);
	BSTree_Node<T> *find(T data);
};

template <typename T>
BSTree_Node<T> *BSTree<T>::insert_node(T data, BSTree_Node<T> *node)  // 返回的已插入新元素的新树的root
{
	if ( node == NULL )
	{
		node = new BSTree_Node<T>;
		node->data = data;
		node->left = NULL;
		node->right = NULL;
	}
	else if ( data < node->data )
		node->left = insert_node(data, node->left);
	else if ( node->data < data )
		node->right = insert_node(data, node->right);

	return node;
}


template <typename T>
BSTree_Node<T> *BSTree<T>::insert_node(T data)    // 有两种实现方法，一是不用递归，如下，二是用递归
{
	BSTree_Node<T> *new_node = new BSTree_Node<T>;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;

	if ( root == NULL )    //空树
	{
		root = new_node;
		return root;
	}

	BSTree_Node<T> *tmp = root;
	while ( tmp != NULL )
	{
		if ( data < tmp->data )
		{
			if ( tmp->left == NULL )
			{
				tmp->left = new_node;
				break;
			}
			tmp = tmp->left;
		}
		else if ( tmp->data < data )
		{
			if ( tmp->right == NULL )
			{
				tmp->right = new_node;
				break;
			}
			tmp = tmp->right;
		}
	}

	return root;
}


template <typename T>
BSTree_Node<T> *BSTree<T>::delete_node(T data, BSTree_Node<T> *node)  // 返回已经delete了元素的新树的root
{
	if ( node == NULL )
		cout << "no this node, can not delete." << endl;
	else if ( data < node->data )
		node->left = delete_node(data, node->left);
	else if ( node->data < data )
		node->right = delete_node(data, node->right);
	else    // found the node
	{
		if ( node->left && node->right )  // node has two children
		{
			BTree_Node<T> *p = find_Min(node->right);
			node->data = p->data;
			node->right = delete_node(node->data, node->right);
		}
		else  // only one or zero child
		{
			BTree_Node<T> *tmp = node;
			if ( node->left == NULL )
				node = node->right;
			else if ( node->right == NULL )
				node = node->left;
			delete(tmp);
			tmp = NULL;
		}
	}

	return node;
}



template <typename T>
BSTree_Node<T> *BSTree<T>::delete_node(T data)
{
	return delete_node(data, root);
}


template <typename T>
BSTree_Node<T> *BSTree<T>::find(T data)
{
	BSTree_Node<T> *p = root;
	while ( p != NULL )
	{
		if ( data == p->data )
			break;
		else if ( data < p->data )
			p = p->left;
		else  // p->data < data
			p = p->right;
	}
	return p;
}


template <typename T>
BSTree_Node<T> *BSTree<T>::find_Max(BSTree_Node<T> *node)   // 默认node不为NULL
{
	BSTree_Node<T> *p = node;
	while ( p->right != NULL )
		p = p->right;
	return p;
}


template <typename T>
BSTree_Node<T> *BSTree<T>::find_Min(BSTree_Node<T> *node)
{
	BSTree_Node<T> *p = node;
	while ( p->left != NULL )
		p = p->left;
	return p;
}

