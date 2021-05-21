#include <iostream>
#include <string.h>

using namespace std;

// structure of the binary tree node
struct BTNode{
	string data;
	BTNode * left;
	BTNode * right;
};


// structure for BST node
struct Node{
	string data;
	int count;
	Node * left;
	Node * right;
	Node * parent;
};


