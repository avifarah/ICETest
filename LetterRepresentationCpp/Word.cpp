#include "pch.h"
#include <algorithm>
#include <vector>
#include <string>
#include "..\\AnagramUtils\Utils.h"
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

string Word::GetWordValue() { return WordValue; }

string Word::GetWordKey() { return WordKey; }

long Word::GetWordRepresentation() { return WordRepresentation; }

bool Word::operator ==(Word& rhs) const { return (WordValue == rhs.GetWordValue()); }

bool Word::operator !=(Word& rhs) const { return !(*this == rhs); }

string Word::SetWordKey(Word& word)
{
	if (word.KeySet) return word.WordKey;

	vector<char> v(word.GetWordValue().begin(), word.GetWordValue().end());

	sort(v.begin(), v.end(), [](const char& c1, const char& c2) { return toupper(c1) < toupper(c2); });
	string s(v.begin(), v.end());
	word.WordKey = s;
	word.KeySet = true;
}

bool Word::IsWordSame(Word word1, Word word2)
{
	return Utils::IsStringSame(word1.GetWordValue(), word2.GetWordValue());
}

Word::WordAnagram Word::IsWordAnagram(Word& word1, Word& word2)
{
	if (IsWordSame(word1, word2)) return SameWord;
	if (word1.GetWordValue().size() != word2.GetWordValue().size()) return NotAnagram;
	if (word1.WordRepresentation != word2.WordRepresentation) return NotAnagram;

	if (!word2.KeySet) SetWordKey(word2);
	if (!word1.KeySet) SetWordKey(word1);

	if (Utils::IsStringSame(word1.GetWordKey(), word2.GetWordKey())) return YesAnagram;
	return NotAnagram;
}
