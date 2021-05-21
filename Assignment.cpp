#include <iostream>
#include "BST.h"

using namespace std;


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
					// create BST here with the filename
					vector<string> words;
					words = getData(filename);
					Node* root = CreateBST(words);
					cout<<"BST created successfully!"<<endl;
				}
				break;
			}	
			case 'Q': {
				flag = false;
				break;
			}	
		}

	}

	return 0;
}