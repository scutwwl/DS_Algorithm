#include "multiple_tree.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

void pre_order_tranverse(const MTree_Node<string> *root, int depth = 0)
{
	for (int i=1; i<=depth; i++)
		cout << "\t";
	++depth;
	cout << root->data << endl;
	MTree_Node<string> *son = root->next;
	while ( son != NULL )
	{
		pre_order_tranverse(son, depth);
		son = son->sibling;
	}
}

void post_order_tranverse(const MTree_Node<string> *root, int depth = 0)
{
	++depth;
	MTree_Node<string> *son = root->next;
	while ( son != NULL )
	{
		post_order_tranverse(son, depth);
		son = son->sibling;
	}
	for (int i=1; i<=depth-1; i++)
		cout << "\t";
	cout << root->data << endl;
}


int main ()
{
	MTree<string> tree;
	// 初始化树，根据DS book file structure
	MTree_Node<string> *root = tree.insert_node("usr", NULL, NULL);
	MTree_Node<string> *mark = tree.insert_node("mark", root, NULL);
	MTree_Node<string> *alex = tree.insert_node("alex", NULL, mark);
	MTree_Node<string> *bill = tree.insert_node("bill", NULL, alex);
	MTree_Node<string> *book = tree.insert_node("book", mark, NULL);
	MTree_Node<string> *course = tree.insert_node("course", NULL, book);
	MTree_Node<string> *junk1 = tree.insert_node("junk.c", NULL, course);
	MTree_Node<string> *ch1 = tree.insert_node("ch1", book, NULL);
	MTree_Node<string> *ch2 = tree.insert_node("ch2", NULL, ch1);
	MTree_Node<string> *ch3 = tree.insert_node("ch3", NULL, ch2);
	MTree_Node<string> *cop3530 = tree.insert_node("cop3530", course, NULL);
	MTree_Node<string> *fall96 = tree.insert_node("fall96", cop3530, NULL);
	MTree_Node<string> *spr97 = tree.insert_node("spr97", NULL, fall96);
	MTree_Node<string> *sum97 = tree.insert_node("sum97", NULL, spr97);
	MTree_Node<string> *syr1 = tree.insert_node("syl.r", fall96, NULL);
	MTree_Node<string> *syr2 = tree.insert_node("syl.r", spr97, NULL);
	MTree_Node<string> *syr3 = tree.insert_node("syl.r", sum97, NULL);
	MTree_Node<string> *junk2 = tree.insert_node("junk.c", alex, NULL);
	MTree_Node<string> *work = tree.insert_node("work", bill, NULL);
	MTree_Node<string> *course2 = tree.insert_node("course", NULL, work);
	MTree_Node<string> *cop3212 = tree.insert_node("cop3212", course2, NULL);
	MTree_Node<string> *fall961 = tree.insert_node("fall96", cop3212, NULL);
	MTree_Node<string> *fall97 = tree.insert_node("fall97", NULL, fall961);
	MTree_Node<string> *grades1 = tree.insert_node("grades", fall961, NULL);
	MTree_Node<string> *prog11 = tree.insert_node("prog1.r", NULL, grades1);
	MTree_Node<string> *prog21 = tree.insert_node("prog2.r", NULL, prog11);
	MTree_Node<string> *prog22 = tree.insert_node("prog2.r", fall97, NULL);
	MTree_Node<string> *prog12 = tree.insert_node("prog1.r", NULL, prog22);
	MTree_Node<string> *grades2 = tree.insert_node("grades", NULL, prog12);

	pre_order_tranverse(tree.root);
	cout << "\n\n\n\n\n";
	post_order_tranverse(tree.root);

	return 0;
}
