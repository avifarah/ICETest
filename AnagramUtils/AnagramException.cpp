#include "pch.h"
#include <string>
#include "AnagramException.h"

using namespace std;

AnagramException::AnagramException(string message, string word, int lineCount /*= 0*/, int wordCount /*= 0*/)
	: Message(message), Word(word), LineCount(lineCount), WordCount(wordCount)
{
}

AnagramException::~AnagramException() { }

string AnagramException::GetExMessage() { return Message; }

string AnagramException::GetWord() { return Word; }

int AnagramException::GetLineCount() { return LineCount; }

int AnagramException::GetWordCount() { return WordCount; }

