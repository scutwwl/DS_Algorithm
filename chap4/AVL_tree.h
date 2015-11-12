#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

template <typename T>
class AVLTree_Node
{
public:
	T data;
	AVLTree_Node<T> *left;
	AVLTree_Node<T> *right;
	int height;
};

template <typename T>
class AVLTree
{
public:
	AVLTree_Node<T> *insert_node(T data);     // return the root
	AVLTree_Node<T> *insert_node(T data, AVLTree_Node<T> *node);
	AVLTree_Node<T> *delete_node(T data);     // return the root
	AVLTree_Node<T> *delete_node(T data, AVLTree_Node<T> *node);
	AVLTree_Node<T> *find(T data);
	AVLTree_Node<T> *find_Max(AVLTree_Node<T> *node);
	AVLTree_Node<T> *find_Min(AVLTree_Node<T> *node);
	
	AVLTree_Node<T> *root;

private:
	AVLTree_Node<T> *SingleRotateLeft(AVLTree_Node<T> *k2);
	AVLTree_Node<T> *SingleRotateRight(AVLTree_Node<T> *node);
	AVLTree_Node<T> *DoubleRotateLeft(AVLTree_Node<T> *k3);
	AVLTree_Node<T> *DoubleRotateRight(AVLTree_Node<T> *node);
	int Height(AVLTree_Node<T> *node);     // 不直接读取Node的height，是因为要处理node==NULL的情况
	int max(int &a, int &b);

};

template <typename T>
AVLTree_Node<T> *AVLTree<T>::insert_node(T data)
{
	return insert_node(data, root);
}

template <typename T>
AVLTree_Node<T> *AVLTree<T>::insert_node(T data, AVLTree_Node<T> *node)
{
	AVLTree_Node<T> *new_node = new AVLTree_Node<T>;
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->height = 0;
	if ( node == NULL )
		node = new_node;
	else if ( data < node->data )
	{
		node->left = insert_node(data, node->left);
		if ( Height(node->left) - Height(node->right) == 2 )
		{
			if ( data < node->left->data )
				node = SingleRotateLeft(node);
			else if ( data > node->left->data )
				node = DoubleRotateLeft(node);
		}
	}
	else if ( data > node->data )
	{
		node->right = insert_node(data, node->right);
		if ( Height(node->right) - Height(node->left) == 2 )
		{
			if ( data > node->right->data )
				node = SingleRotateRight(node);
			else if ( data < node->right->data )
				node = DoubleRotateRight(node);
		}
	}
}

template <typename T>
AVLTree_Node<T> *AVLTree<T>::SingleRotateLeft(AVLTree_Node<T> *k2)
{
	AVLTree_Node<T> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(Height(k2->left), k2->right->height) + 1;
	k1->height = max(k1->left->height, k2->height) + 1;
	return k1;
}

template <typename T>
AVLTree_Node<T> *AVLTree<T>::DoubleRotateLeft(AVLTree_Node<T> *k3)
{
	k3->left = SingleRotateRight(k3->left);
	AVLTree_Node<T> *k2 = SingleRotateLeft(k3);
	return k2;
}

template <typename T>
AVLTree_Node<T> *AVLTree<T>::SingleRotateRight(AVLTree_Node<T> *k1)
{
	AVLTree_Node<T> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(k1->left->height, Height(k1->right)) + 1;
	k2->height = max(k1->height, k2->right->height) + 1;
	return k2;
}

template <typename T>
AVLTree_Node<T> *AVLTree<T>::DoubleRotateRight(AVLTree_Node<T> *k1)
{
	k1->right = SingleRotateLeft(k1->left);
	return SingleRotateRight(k1);
}

template <typename T>
int AVLTree_Node<T>::Height(AVLTree<T> *node)
{
	if ( node == NULL )
		return -1;
	else
		return node->height;
}

template <typename T>
int AVLTree<T>::max(int &a, int &b)
{
	return ( a >= b ? a : b );
}

template <typename T>
AVLTree_Node<T> *AVLTree<T>::delete_node(T data)
{
	return NULL;
}

template <typename T>
AVLTree_Node<T> *AVLTree<T>::delete_node(T data, AVLTree_Node<T> *node)
{
	return NULL;
}

template <typename T>
AVLTree_Node<T> *AVLTree<T>::find(T data)
{
	AVLTree_Node<T> *tmp = root;
	while ( tmp != NULL )
	{
		if ( data == tmp->data )
			break;
		else if ( data < tmp->data )
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return tmp;
}

template <typename T>
AVLTree_Node<T> *AVLTree<T>::find_Max(AVLTree_Node<T> *node)
{
	while ( node->right != NULL )
		node = node->right;
	return node;
}

template <typename T>
AVLTree_Node<T> *AVLTree<T>::find_Min(AVLTree_Node<T> *node)
{
	while ( node->left != NULL )
		node = node->left;
	return node;
}



#endif
