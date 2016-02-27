#include <iostream>
#include "binary_search_tree.h"


using std::cout;
using std::endl;

int main()
{
	cout << "ok" << endl;
	BSTree<int> bst;
	/* build the binary search tree              
	 *        6                                 
	 *       / \
	 *      2   8                                   
	 *     / \
	 *     1  4
	 *        /
	 *       3
	 */                                  
	bst.insert_node(6);
	bst.insert_node(2);
	bst.insert_node(8);
	bst.insert_node(1);
	bst.insert_node(4);
	bst.insert_node(3);

	cout << "the min data is " << bst.findMin(bst.find(6)) <<  " the max is " << bst.findMax(bst.find(6)) << endl;   // output 1 8
	cout << "6 left child is " << bst.find(6)->left->data << " the right child is " << bst.find(6)->right->data << endl;  // output 2 8
	cout << "2 left child is " << bst.find(2)->left->data << " the right child is " << bst.find(2)->right->data << endl;  // output 1 4
	cout << "4 left child is " << bst.find(4)->left->data << endl;   // output 3

	bst.delete_node(2);

	cout << "6 left child is " << bst.find(6)->left->data << " the right child is " << bst.find(6)->right->data << endl;  // output 3 8
	cout << "3 left child is " << bst.find(3)->left->data << " the right child is " << bst.find(3)->right->data << endl;  // output 1 4
	cout << "4 left is " << bst.find(4)->left << endl;    // output 0

	bst.remove_tree(bst.find(6));
	cout << "the root is " << bst.find(6) << endl;     // output 0  

	return 0;
}
