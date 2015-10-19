#include "binary_tree.h"
#include "../chap3/stack.h"
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::cin;

void suffix_to_expression_tree(const string &suffix, BTree<char> &tree)
{
	Stack<BTree_Node<char> *> stack_tree;
	for ( auto c : suffix )
	{
		if ( c=='+' || c=='-' || c=='*' || c=='/' )
		{
			BTree_Node<char> *root_node = new BTree_Node<char>;
			root_node->data = c;
			BTree_Node<char> *p1 = stack_tree.top();
			stack_tree.pop();
			BTree_Node<char> *p2 = stack_tree.top();
			stack_tree.pop();
			root_node->left = p2;
			root_node->right = p1;
			stack_tree.push(root_node);
		}
		else
		{
			BTree_Node<char> *root_node = new BTree_Node<char>;
			root_node->data = c;
			root_node->left = NULL;
			root_node->right = NULL;
			stack_tree.push(root_node);
		}
	}
	tree.root = stack_tree.top();
}


int main ()
{
	string suffix;
	BTree<char> expression_tree;
	cout << "The suffix is : ";
	cin >> suffix;
	suffix_to_expression_tree(suffix, expression_tree);
	cout << "in order: ";
	expression_tree.in_order_tranverse();
	cout << endl;
	cout << "pre order: ";
	expression_tree.pre_order_tranverse();
	cout << endl;
	cout << "post order: ";
	expression_tree.post_order_tranverse();
	cout << endl;
	return 0;
}
