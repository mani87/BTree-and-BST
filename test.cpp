#include <bits/stdc++.h>

using namespace std;

int main() {
	
	string filename, word;
	cin>>filename;

	fstream file;
	file.open(filename);

	while(file>>word) {
		cout<<word<<" ";
	}

	file.close();
	return 0;
}
