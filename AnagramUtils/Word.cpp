#include "pch.h"
#include <algorithm>
#include <vector>
#include <string>
#include "..\\AnagramUtils\Utils.h"
#include "..\\AnagramUtils\AnagramException.h"
#include "Word.h"

using namespace std;

static string emptyWordString = "";

Word::Word(LetterRepresentation letterRep, string word, int lineCount /*= 0*/, int wordCount /*= 0*/)
	: KeySet(false), WordValue(word), WordKey(emptyWordString), LineCount(lineCount), WordCount(wordCount)
{
	WordRepresentation = letterRep.WordRep(word, lineCount, wordCount);
}

Word::~Word()
{
}

string Word::GetWordValue() const { return WordValue; }

string Word::GetWordKey() const
{
	if (KeySet) return WordKey;
	throw AnagramException("WordKey was not set", WordValue, LineCount, WordCount);
}

long long Word::GetWordRepresentation() const { return WordRepresentation; }

string Word::SortWord(Word& word)
{
	if (word.KeySet) return word.WordKey;

	auto wordValue = word.GetWordValue();
	vector<char> v(wordValue.begin(), wordValue.end());

	sort(v.begin(), v.end(), [](const char& c1, const char& c2) { return toupper(c1) < toupper(c2); });
	string s(v.begin(), v.end());
	word.WordKey = s;
	word.KeySet = true;
	return word.WordKey;
}

bool Word::IsWordSame(Word word1, Word word2) { return Utils::IsStringSame(word1.GetWordValue(), word2.GetWordValue()); }

Word::WordAnagram Word::IsWordAnagram(Word& word1, Word& word2)
{
	if (IsWordSame(word1, word2)) return SameWord;
	if (word1.GetWordValue().size() != word2.GetWordValue().size())
		return NotAnagram;

	if (!word2.KeySet) SortWord(word2);
	if (!word1.KeySet) SortWord(word1);

	if (word1.GetWordRepresentation() != word2.GetWordRepresentation())
		return NotAnagram;

	if (Utils::IsStringSame(word1.GetWordKey(), word2.GetWordKey()))
		return YesAnagram;

	return NotAnagram;
}

bool Word::operator ==(const Word& rhs) { return (GetWordValue() == rhs.GetWordValue()); }
bool Word::operator !=(const Word& rhs) { return !(*this == rhs); }
