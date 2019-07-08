
//Trim trailing and leading white spaces from both ends of a string
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//using std::cout;
//using std::string;

string Trim(string text)
{
	string newstr = "";
	int inxBeg = 0;

	while (text.at(inxBeg) == ' ') inxBeg++;

	int inxEnd = text.length() - 1;
	while (text.at(inxEnd) == ' ') inxEnd--;

	newstr = text.substr(i, j - i + 1);
	return newstr;
}