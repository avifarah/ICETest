#pragma once

#include <string>
#include "LetterRepresentation.h"

using namespace std;

#ifdef ANAGRAMUTILS_EXPORTS
#define LETTERDLLEXPORT __declspec(dllexport)
#pragma message ("__declspec(dllexport)")
#else
#define LETTERDLLEXPORT __declspec(dllimport)
#pragma message ("__declspec(dllimport)")
#endif

class LETTERDLLEXPORT Word
{
private:
	const string WordValue;			// The original value of the word
	long long WordRepresentation;	// Numerical representation of the word
	string WordKey;					// A key for the word shared by all anagrams.
	int LineCount;					// Line count where word was found
	int WordCount;					// Count of this word index in the current line
	bool KeySet;					// A flag indicating whether the WordKey was set already or not

public:
	Word(LetterRepresentation letterRep, string word, int lineCount = 0, int wordCount = 0);
	~Word();

	enum WordAnagram { YesAnagram, SameWord, NotAnagram };
	string GetWordValue() const;
	string GetWordKey() const;
	long long GetWordRepresentation() const;

	bool operator ==(const Word& rhs);
	bool operator !=(const Word& rhs);

	static string SetWordKey(Word& word);
	static bool IsWordSame(Word word1, Word word2);
	static WordAnagram IsWordAnagram(Word& word1, Word& word2);
};
