#pragma once

#include <string>

using namespace std;


#ifdef  LETTERREPRESENTATIONCPP_EXPORTS
	#define LETTERDLLEXPORT __declspec(dllexport)
	#pragma message ("__declspec(dllexport)")
#else
	#define LETTERDLLEXPORT __declspec(dllimport)
	#pragma message ("__declspec(dllimport)")
#endif

class LETTERDLLEXPORT AnagramException
{
private:
	string& Message;
	string& Word;
	int LineCount;
	int WordCount;

public:
	AnagramException(string message, string word, int lineCount = 0, int wordCount = 0);
	~AnagramException();
	string GetExMessage();
	string GetWord();
	int GetLineCount();
	int GetWordCount();
};
