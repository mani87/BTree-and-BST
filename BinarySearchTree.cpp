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
	Node* c = NULL;

	while(root) {
		if(root->data == key) {
			c = root;
			break;
		} 
		if(root->data > key) {
			//we move left
			c = root;
			root = root->left;
		} else if(root->data < key) {
			root = root->right;
		}
	}

	return c;
}


// greatest value smaller than or equal to the key
Node* floorVal(Node * root, string key) {
	Node* f = NULL;

	while(root) {
		if(root->data == key) {
			f = root;
			break;
		}

		if(root->data < key) {
			f = root;
			root = root->right;
		} else if(root->data > key) {
			root = root->left;
		}
	}
	return f;
}



Node* Delete(Node* root, string key) {

	if(!root) return NULL;

	if(root->data > key) root->left = Delete(root->left, key);
	else if(root->data < key) root->right = Delete(root->right, key);
	else {
		// we have found the node
		if(!root->left && !root->right) {
			// leaf node
			delete root;
			root = NULL;
		} else if(!root->left) {
			Node* node = root;
			root = root->right;
			delete node;
		} else if(!root->right) {
			Node* node = root;
			root = root->left;
			delete node;
		} else {
			Node* temp = treeMinimum(root->right);
			root->data = temp->data;
			root->right = Delete(root->right, temp->data);
		}
	}
	return root;
}


void preOrder(Node* root) {
	if(!root) return;

	stack<Node*> st;
	st.push(root);

	while(!st.empty()) {
		Node* temp = st.top();
		cout<<temp->data<<" ";

		st.pop();
		if(temp->right) st.push(temp->right);
		if(temp->left) st.push(temp->left);
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

	Node* root = CreateBST(words);	
	Node* min_ = treeMinimum(root);
	Node* max_ = treeMaximum(root);

	cout<<"Min: "<<min_->data<<endl;
	cout<<"Max: "<<max_->data<<endl;
	cout<<"Parent of 5 is "<<(recTreeSearch(root, "5")->parent)->data<<endl;
	cout<<"InOrderSuccessor of 3 is "<<inOrderSuccessor(recTreeSearch(root, "3"))->data<<endl;
	cout<<"InOrderPredecessor of 5 is "<<inOrderPred(recTreeSearch(root, "5"))->data<<endl;
	cout<<"Cieling value of 4 is "<<ceiling(root, "4")->data<<endl;
	cout<<"Floor value of 4 is "<<floorVal(root, "4")->data<<endl;
	preOrder(root);
	root = Delete(root, "5");
	cout<<endl;
	preOrder(root);
	cout<<endl;

	return 0;
}