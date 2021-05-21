#include <bits/stdc++.h>
#include "NodeType.h"

vector<string> getData(string filename) {
	// Read file 
	string word;
	fstream file;
	file.open(filename);

	// store results into a vector
	vector<string> words;
	while(file>>word) {
		words.push_back(word);
	}

	return words;
}


// Creates a tree node with given parent and data
Node* createTreeNode(string data, Node* parent) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->count = 1;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	return node;
}


// insert into BST
Node* insert(Node* node, string data, Node* parent) {
	if(!node) return createTreeNode(data, parent);

	if(data > node->data) {
		// right insert
		node->right = insert(node->right, data, node);
	} else if(data < node->data){
		// left insert
		node->left = insert(node->left, data, node);
	} else {
		// already present
		cout<<data<<" is already present, updating count to "<<(node->count+1)<<endl;
		(node->count)++;
	}
	return node;
}


// helps creating BST from the array of words
Node* CreateBST(vector<string> words) {
	Node* root = NULL;

	for(auto word: words) {
		root = insert(root, word, NULL);
	}
	return root;
}