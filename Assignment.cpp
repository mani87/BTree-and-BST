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


// delete node from the tree
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


// Level order traversal of tree
void levelOrder(Node* root) {
	if(!root) return;

	queue<Node*> q;
	q.push(root);

	while(!q.empty()) {
		int n = q.size();

		while(n--) {
			Node* temp = q.front();
			q.pop();
			cout<<temp->data<<" ";
			if(temp->left) q.push(temp->left);
			if(temp->right) q.push(temp->right);
		}
	}
}


// pre-order traversal
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


// inOrder: iterative version
void inOrder(Node* root) {
	if(!root) return;

	inOrder(root->left);
	cout<<root->data<<" ";
	inOrder(root->right);
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


// tells us if two trees are same
bool areSame(Node* one, Node* two) {
	if(!one && !two) return true;
	return (one && two) && (one->data == two->data) && (areSame(one->left, two->left) && areSame(one->right, two->right));
}


// calculate height of the tree
int height(Node* node) {
	if(!node) return 0;

	return max(height(node->left), height(node->right)) + 1;
}


// number of node in the tree
int numberOfNodes(Node* node) {
	if(!node) return 0;

	return numberOfNodes(node->left) + numberOfNodes(node->right) + 1;
}


// Return width - max no of nodes at a level
int width(Node* root) {
	if(!root) return 0;

	int ans = INT_MIN;
	queue<Node*> q;
	q.push(root);

	while(!q.empty()) {
		int n = q.size();
		ans = max(ans, n);

		while(n--) {
			Node* temp = q.front();
			q.pop();

			if(temp->left) q.push(temp->left);
			if(temp->right) q.push(temp->right);
		}
	}
	return ans;
}


// find the weight of the tree
int weight(Node* node) {
	if(!node) return 0;

	if(!node->left && !node->right) return node->count;

	return node->count + weight(node->left) + weight(node->right);
}


void printMenu() {
	cout<<"Binary Search Tree (BST)"<<endl;
	cout<<"-----------------------------------"<<endl;
	cout<<"1. Create BST from File"<<endl;
	cout<<"2. Add word to BST"<<endl;
	cout<<"3. Delete Word from BST"<<endl;
	cout<<"4. Search Word in BST"<<endl;
	cout<<"5. Traverse BST"<<endl;
	cout<<"6. What comes before word in BST?"<<endl;
	cout<<"7. What comes after word in BST?"<<endl;
	cout<<"8. Compare BSTs"<<endl;
	cout<<"9. Statistics"<<endl;
	cout<<"Q. Quit"<<endl;
}


Node* root = NULL;
int main() {

	bool flag = true;

	while(flag) {

		printMenu();
		char option;
		cout<<"Please enter an option: ";
		cin>>option;

		switch(option) {
			case '1': {
				cout<<"Please enter the name of the file or M (Menu): ";
				string filename;
				cin>>filename;
				if(filename=="M") {
					continue;
				} else {
					// Read file - words.txt
					fstream file;
					string word;
					file.open(filename);

					// store results into a map to use it later
					vector<string> words;
					while(file>>word) {
						words.push_back(word);
					}

					root = CreateBST(words);
					cout<<"----------------------------------"<<endl;
					cout<<"Binary Tree created successfully!"<<endl;
					cout<<"----------------------------------"<<endl;
				}
			}	
			break;
			case '2': {
				cout<<"Please enter the word to insert in the BST or M (Menu): ";
				string word;
				cin>>word;
				if(word=="M") {
					continue;
				} else {
					insert(root, word, NULL);
					cout<<"----------------------------------"<<endl;
					cout<<"Inserted "<<word<<" successfully!"<<endl;
					cout<<"----------------------------------"<<endl;
				}
			}
			break;
			case '3': {
				cout<<"Please enter the word to delete in the BST or M (Menu): ";
				string word;
				cin>>word;
				if(word=="M") {
					continue;
				} else {
					Delete(root, word);
					cout<<"----------------------------------"<<endl;
					cout<<"Deleted "<<word<<" successfully!"<<endl;
					cout<<"----------------------------------"<<endl;
				}
			}
			break;
			case '4': {
				cout<<"Please enter a word to search for or M (Menu): ";
				string word;
				cin>>word;
				if(word=="M") {
					continue;
				} else {
					Node* temp = recTreeSearch(root, word);
					if(!temp) {
						cout<<"-----------------------------------------"<<endl;
						cout<<"Sorry, "<<word<<" is not present in tree."<<endl;
						cout<<"-----------------------------------------"<<endl;
					} else {
						cout<<"--------------------------"<<endl;
						cout<<word<<" is found in tree."<<endl;
						cout<<"--------------------------"<<endl;
					}
				}
			}	
			break;
			case '5': {
				cout<<"Pre-order : ";
				preOrder(root);
				cout<<endl;
				cout<<"In-order : ";
				inOrder(root);
				cout<<endl;
			}
			break;
			case '6': {
				cout<<"Please enter the word: ";
				string word;
				cin>>word;
				Node* temp = floorVal(root, word);
				if(!temp) {
					cout<<"--------------------------"<<endl;
					cout<<"Such value doesn't exist."<<endl;
					cout<<"--------------------------"<<endl;
				} else {
					cout<<"--------------------------"<<endl;
					cout<<temp->data<<" comes before "<<word<<endl;
					cout<<"--------------------------"<<endl;
				}
			}
			break;
			case '7': {
				cout<<"Please enter the word: ";
				string word;
				cin>>word;
				Node* temp = ceiling(root, word);
				if(!temp) {
					cout<<"--------------------------"<<endl;
					cout<<"Such value doesn't exist."<<endl;
					cout<<"--------------------------"<<endl;
				} else {
					cout<<"--------------------------"<<endl;
					cout<<temp->data<<" comes after "<<word<<endl;
					cout<<"--------------------------"<<endl;
				}
			}
			break;
			case '8': {
				cout<<"Please enter the name of the file to create the BST or M (Menu): ";
				string filename;
				cin>>filename;

				if(filename=="M") {
					continue;
				} else {
					// Read file - words.txt
					fstream file;
					string word;
					file.open(filename);

					// store results into a map to use it later
					vector<string> values;
					while(file>>word) {
						values.push_back(word);
					}

					Node* another_tree = CreateBST(values);
					if(areSame(root, another_tree)) {
						cout<<"-----------------------"<<endl;
						cout<<"Both trees are same."<<endl;
						cout<<"-----------------------"<<endl;
					} else {
						cout<<"-----------------------------"<<endl;
						cout<<"No, both trees are not same."<<endl;
						cout<<"-----------------------------"<<endl;
					}
				}
			}
			break;
			case '9': {
				cout<<"---------------------------"<<endl;
				cout<<"TREE SUMMARY"<<endl;
				cout<<"Number of nodes in tree: "<<numberOfNodes(root)<<endl;
				cout<<"Height of the tree is: "<<height(root)<<endl;
				cout<<"Width of the tree is: "<<width(root)<<endl;
				cout<<"Weight of the tree is: "<<weight(root)<<endl;
				cout<<"Smallest word in tree is: "<<treeMinimum(root)->data<<endl;
				cout<<"Largest word in the tree is: "<<treeMaximum(root)->data<<endl;
				cout<<"---------------------------"<<endl;
			}
			break;
			case 'Q': {
				flag = false;
				break;
			}	
		}

	}

	return 0;
}