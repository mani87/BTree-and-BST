#include <bits/stdc++.h>
#include "NodeType.h"

using namespace std;

// Creates a tree node with given parent and data
BTNode* createTreeNode(string data) {
	
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return node;
}


// Create whole binary tree using given list of words
BTNode* CreateBTree(vector<string> words, BTNode* root, int i, int n) {
	if(i<n) {
		BTNode* node = createTreeNode(words[i]);
		root = node;
		root->left = CreateBTree(words, root->left, 2*i+1, n);
		root->right = CreateBTree(words, root->right, 2*i+2, n);
	}
	return root;
}


// Find height of the tree
int height(BTNode* node) {
	if(!node) return 0;
	return max(height(node->left), height(node->right))+1;
}


void inOrder(BTNode* root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        cout << root->data <<" ";
        inOrder(root->right);
    }
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

	BTNode* root = CreateBTree(words, root, 0, words.size());
	cout<<"Height is: "<<height(root)<<endl;
	inOrder(root);
	return 0;
}