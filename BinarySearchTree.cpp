#include <bits/stdc++.h>
#include "NodeType.h"

using namespace std;


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


// Recursive Tree Search
Node* recTreeSearch(Node* node, string key) {
	if(!node) return NULL;

	if(key > node->data) {
		node = recTreeSearch(node->right, key);
	} else if(key < node->data) {
		node = recTreeSearch(node->left, key);
	} 
	return node;
}


// minimum element in tree
Node* treeMinimum(Node* root) {
	while(root->left) {
		root = root->left;
	}
	return root;
}


// max element in tree
Node* treeMaximum(Node* root) {
	while(root->right) {
		root = root->right;
	}
	return root;
}


// gives inorder successor of tree
Node* inOrderSuccessor(Node* node) {
	if(node->right) return treeMinimum(node->right);

	Node* p = node->parent;
    while (p != NULL && node == p->right) {
        node = p;
        p = p->parent;
    }
    return p;
}


// gives us inorder pred of the given node
Node* inOrderPred(Node* node) {
	if(node && node->left) return treeMaximum(node->left);
	return node->parent;
}


// smallest value greater than or equal to the key
Node* ceiling(Node* root, string key) {

}


int main() {
	
	string filename, word;
	unordered_map<string, int> mp;

	cin>>filename;

	// Read file - words.txt
	fstream file;
	file.open(filename);

	// store results into a map to use it later
	vector<string> words;
	while(file>>word) {
		words.push_back(word);
	}

	for(auto x: words) cout<<x<<" ";
	cout<<endl;

	Node* root = CreateBST(words);	
	Node* min_ = treeMinimum(root);
	Node* max_ = treeMaximum(root);

	cout<<"Min: "<<min_->data<<endl;
	cout<<"Max: "<<max_->data<<endl;
	cout<<"Parent of 2 is "<<(recTreeSearch(root, "2")->parent)->data<<endl;
	cout<<"InOrderSuccessor of 2 is "<<inOrderSuccessor(recTreeSearch(root, "2"))->data<<endl;
	cout<<"InOrderPredecessor of 4 is "<<inOrderPred(recTreeSearch(root, "4"))->data<<endl;

	return 0;
}