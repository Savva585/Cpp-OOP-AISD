

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
void FileImport( vector<string>& MyVector,const string& NameFile) {
	string buf;
	ifstream f(NameFile);
	for (int i = 0; !f.eof(); i++) {
		f >> buf;
		MyVector.push_back(buf);
	}
}
void EnglishChar(string& str) {
	for (int i = 0;i < str.length();++i) {
			if (!isalpha(str[i])) {
				str.erase(i,1);
			}
    }
}
int main()
{
	vector<string>MyVector;
	string buf;
	string NameFile = "C://1//ann.txt";
	FileImport(MyVector,NameFile);
	vector<string>MyVectorNormalize;
	for (const string& words : MyVector) {
		for (const char& ab : words) {
			buf += tolower(ab);
		}
		MyVectorNormalize.push_back(buf);
		buf = "";
	}
	for (string& words : MyVector) {
		EnglishChar(words);
	}
	for (const string& words : MyVector) {
		cout << words << "\n";
	}
	
}
