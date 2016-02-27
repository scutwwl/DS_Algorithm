#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include <cstdlib>
#include <iostream>

template <typename T>
class BSTree_Node
{
public:
	T data;
	BSTree_Node<T> *left;
	BSTree_Node<T> *right;
};


template <typename T>
class BSTree
{
public:
	BSTree();
	~BSTree();

	T findMin(BSTree_Node<T> *tree_node);
	T findMax(BSTree_Node<T> *tree_node);
	BSTree_Node<T> *find(T data);
	void remove_tree(BSTree_Node<T> *tree_node);
	void insert_node(T data);
	void delete_node(T data);

private:
	void insert_nonrecur(T data);     //插入的非递归版本
	BSTree_Node<T> *insert_recur(T data, BSTree_Node<T> *tree_node);   //插入的递归版本
	BSTree_Node<T> *delete_recur(T data, BSTree_Node<T> *tree_node);

public:
	BSTree_Node<T> *root;
};


template <typename T>
BSTree<T>::BSTree() : root(nullptr) {  }

template <typename T>
BSTree<T>::~BSTree()
{
	remove_tree(root);
}


template <typename T>
T BSTree<T>::findMin(BSTree_Node<T> *tree_node)
{
	if (tree_node == nullptr)
	{
		std::cout << "the tree_node is nullptr, cannot findMin." << std::endl;
		exit(1);
	}
	BSTree_Node<T> *tmp = tree_node;
	while (tmp->left != nullptr)
		tmp = tmp->left;
	return tmp->data;
}


template <typename T>
T BSTree<T>::findMax(BSTree_Node<T> *tree_node)
{
	if (tree_node == nullptr)
	{
		std::cout << "the root is nullptr, cannot findMax." << std::endl;
		exit(2);
	}
	BSTree_Node<T> *tmp = tree_node;
	while (tmp->right != nullptr)
		tmp = tmp->right;
	return tmp->data;
}


template <typename T>
BSTree_Node<T> *BSTree<T>::find(T data)
{
	BSTree_Node<T> *tmp = root;
	while (tmp != nullptr)
	{
		if (tmp->data == data)
			break;
		else if (data < tmp->data)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return tmp;
}


template <typename T>
void BSTree<T>::remove_tree(BSTree_Node<T> *tree_node)
{
	if (tree_node != nullptr)
	{
		remove_tree(tree_node->left);
		remove_tree(tree_node->right);
		delete tree_node;
		tree_node = nullptr;
	}
}


template <typename T>
void BSTree<T>::insert_node(T data)
{
	insert_nonrecur(data);
	//insert_recur(data, root);
}

template <typename T>
void BSTree<T>::insert_nonrecur(T data)
{
	BSTree_Node<T> *new_node = new BSTree_Node<T>;
	new_node->data = data;
	new_node->left = nullptr;
	new_node->right = nullptr;

	if (root == nullptr)
	{
		root = new_node;
		return;
	}

	BSTree_Node<T> *insert_parent;
	BSTree_Node<T> *son = root;
	while (son != nullptr)
	{
		insert_parent = son;
		if (data == son->data)
			return;
		else if (data < son->data)
			son = son->left;
		else
			son = son->right;
	}
	if (data < insert_parent->data)
		insert_parent->left = new_node;
	else
		insert_parent->right = new_node;
}

template <typename T>
BSTree_Node<T> *BSTree<T>::insert_recur(T data, BSTree_Node<T> *tree_node)  //插入某棵树tree_node，并返回该树的树根
{
	if (tree_node == nullptr)
	{
		BSTree_Node<T> *new_node = new BSTree_Node<T>;
		new_node->data = data;
		new_node->left = nullptr;
		new_node->right = nullptr;
		return new_node;
	}
	else if (data < tree_node->data)
		tree_node->left = insert_recur(data, tree_node->left);
	else if (data > tree_node->data)
		tree_node->right = insert_recur(data, tree_node->right);
	else
		return tree_node;
}


template <typename T>
void BSTree<T>::delete_node(T data)
{
	delete_recur(data, root);
}


template <typename T>
BSTree_Node<T> *BSTree<T>::delete_recur(T data, BSTree_Node<T> *tree_node)
{
	if (tree_node == nullptr)
		return tree_node;
	else if (data < tree_node->data)
		tree_node->left = delete_recur(data, tree_node->left);
	else if (data > tree_node->data)
		tree_node->right = delete_recur(data, tree_node->right);
	else  // 找到data的node了
	{
		if (tree_node->left && tree_node->right)     //左右儿子都存在
		{
			T min_data = findMin(tree_node->right);
			tree_node->data = min_data;
			tree_node->right = delete_recur(min_data, tree_node->right);
		}
		else
		{
			BSTree_Node<T> *tmp = tree_node;
			if (tree_node->left == nullptr)
				tree_node = tree_node->right;
			else
				tree_node = tree_node->left;
			delete tmp;
			tmp = nullptr;
		}
	}
	return tree_node;
}

#endif
