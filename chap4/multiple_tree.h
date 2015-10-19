#include <iostream>

template <typename T>
class MTree_Node
{
public:
	T data;
	MTree_Node<T> *next;   // represent the son;
	MTree_Node<T> *sibling;  // represent the brother;
};

template <typename T>
class MTree
{
public:
	MTree();
	~MTree();

	void remove_tree(MTree_Node<T> *node);
	MTree_Node<T> *insert_node(T data, MTree_Node<T> *parent, MTree_Node<T> *prev_bro);   // 返回指针是因为方便使用时的操作

	MTree_Node<T> *root;
};


template <typename T>
MTree<T>::MTree() : root(NULL)
{
}


template <typename T>
MTree<T>::~MTree()
{
	remove_tree(root);
}


template <typename T>
void MTree<T>::remove_tree(MTree_Node<T> *node)       // 默认root不为NULL
{
	if (node->next != NULL)
	{
		MTree_Node<T> *son = node->next;
		while ( son != NULL )
		{
			node->next = son->sibling;
			remove_tree(son);
			son = node->next;
		}
	}
	delete(node);
	node = NULL;
}


template <typename T>
MTree_Node<T> * MTree<T>::insert_node(T data, MTree_Node<T> *parent, MTree_Node<T> *prev_bro)   // 在使用时，若parent NULL,prev_bro not NULL,则接到bro后面;若parent not NULL,prev_bro NULL,则插入的node是该parent的第一个儿子，而且没有其他儿子了。
{
	MTree_Node<T> *node = new MTree_Node<T>;
	node->data = data;
	if (parent==NULL && prev_bro==NULL)
		root = node;
	if (parent != NULL)
		parent->next = node;
	if (prev_bro != NULL)
		prev_bro->sibling = node;
	node->next = NULL;
	node->sibling = NULL;
	return node;
}
			
