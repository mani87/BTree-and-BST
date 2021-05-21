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


// To find if tree is empty
bool isEmpty(BTNode* root) {
	if(!root) return true;
	return false;
}


// Preorder non-recursive code
void preOrder(BTNode* root) {
	if(!root) return;

	stack<BTNode*> st;
	st.push(root);

	while(!st.empty()) {
		BTNode* temp = st.top();
		cout<<temp->data<<" ";

		st.pop();
		if(temp->right) st.push(temp->right);
		if(temp->left) st.push(temp->left);
	}
}


// Calculate weight - no of leaves in a tree
int weight(BTNode* root) {
	if(!root->left && !root->right) return 1;
	return weight(root->left) + weight(root->right);
}


// Return width - max no of nodes at a level
int width(BTNode* root) {
	if(!root) return 0;

	int ans = INT_MIN;
	queue<BTNode*> q;
	q.push(root);

	while(!q.empty()) {
		int n = q.size();
		ans = max(ans, n);

		while(n--) {
			BTNode* temp = q.front();
			q.pop();

			if(temp->left) q.push(temp->left);
			if(temp->right) q.push(temp->right);
		}
	}
	return ans;
}


// return moment of the binary tree
int moment(BTNode* root) {
	if(!root) return 0;
	return (1 + moment(root->left) + moment(root->right));
}


// inOrder: iterative version
void inOrder(BTNode* root) {
	if(!root) return;

	stack<BTNode*> st;
	st.push(root);

	BTNode* curr = root;

	while(curr || !st.empty()) {

		// push all the left element
		while(curr) {
			st.push(curr);
			curr = curr->left;
		}

		curr = st.top();
		st.pop();

		cout<<curr->data<<" ";

		// now we will move to right side
		curr = curr->right;
	}
}


void levelOrder(BTNode* root) {
	if(!root) return;

	queue<BTNode*> q;
	q.push(root);

	while(!q.empty()) {
		int n = q.size();

		while(n--) {
			BTNode* temp = q.front();
			q.pop();
			cout<<temp->data<<" ";
			if(temp->left) q.push(temp->left);
			if(temp->right) q.push(temp->right);
		}
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
	return 0;
}