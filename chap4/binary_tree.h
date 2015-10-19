#include <iostream>
using std::cout;

template <typename T>
class BTree_Node
{
public:
	T data;
	BTree_Node<T> *left;
	BTree_Node<T> *right;
};

template <typename T>
class BTree
{
public:
	BTree();
	~BTree();

	void remove_tree(BTree_Node<T> *node);
	
	void pre_order_tranverse(BTree_Node<T> *node);
	void post_order_tranverse(BTree_Node<T> *node);
	void in_order_tranverse(BTree_Node<T> *node);
	
	void pre_order_tranverse();
	void post_order_tranverse();
	void in_order_tranverse();

	BTree_Node<T> *root;
};


template <typename T>
BTree<T>::BTree() : root(NULL)
{
}


template <typename T>
BTree<T>::~BTree()
{
	remove_tree(root);
}


template <typename T>
void BTree<T>::remove_tree(BTree_Node<T> *node)
{
	BTree_Node<T> *node_left = node->left;
	BTree_Node<T> *node_right = node->right;
	if (node_left != NULL)
		remove_tree(node_left);
	if (node_right != NULL)
		remove_tree(node_right);
	delete(node);
	node = NULL;
}


template <typename T>
void BTree<T>::pre_order_tranverse(BTree_Node<T> *node)
{
	cout << node->data << " ";
	BTree_Node<T> *node_left = node->left;
	BTree_Node<T> *node_right = node->right;
	if (node_left != NULL)
		pre_order_tranverse(node_left);
	if (node_right != NULL)
		pre_order_tranverse(node_right);
}


template <typename T>
void BTree<T>::in_order_tranverse(BTree_Node<T> *node)
{
	BTree_Node<T> *node_left = node->left;
	BTree_Node<T> *node_right = node->right;
	if (node_left != NULL)
		in_order_tranverse(node_left);
	cout << node->data << " ";
	if (node_right != NULL)
		in_order_tranverse(node_right);
}


template <typename T>
void BTree<T>::post_order_tranverse(BTree_Node<T> *node)
{
	BTree_Node<T> *node_left = node->left;
	BTree_Node<T> *node_right = node->right;
	if (node_left != NULL)
		post_order_tranverse(node_left);
	if (node_right != NULL)
		post_order_tranverse(node_right);
	cout << node->data << " ";
}

template <typename T>
void BTree<T>::pre_order_tranverse()
{
	pre_order_tranverse(root);
}

template <typename T>
void BTree<T>::post_order_tranverse()
{
	post_order_tranverse(root);
}

template <typename T>
void BTree<T>::in_order_tranverse()
{
	in_order_tranverse(root);
}

