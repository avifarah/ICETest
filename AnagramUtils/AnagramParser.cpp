#include "pch.h"
#include <regex>
#include <map>
#include "AnagramParser.h"
#include "utils.h"

using namespace std;

static regex AnagramParserRe = regex("\\b([A-Za-z]+)\\b");
regex& AnagramParser::WordRe(AnagramParserRe);

AnagramParser::AnagramParser(ifstream& textStream) : TextStream(textStream), Rep(LetterRepresentation())
{
}

AnagramParser::AnagramParser(ifstream& textStream, LetterRepresentation rep) : TextStream(textStream), Rep(LetterRepresentation(rep))
{
}

AnagramParser::~AnagramParser()
{
}

map<long long, vector<Word>> AnagramParser::GetAllWords()
{
	map<long long, vector<Word>> wordDic;
	for (auto lc = 1; !TextStream.eof(); ++lc)
	{
		string line;
		getline(TextStream, line);

		sregex_iterator currentMatch(line.begin(), line.end(), WordRe);
		sregex_iterator lastMatch;
		auto wc = 0;
		while (currentMatch != lastMatch)
		{
			++wc;
			smatch match = *currentMatch;
			auto word = Word(Rep, match.str(), lc, wc);
			auto rep = word.GetWordRepresentation();
			map<long long, vector<Word>>::iterator wordDicIt = wordDic.find(rep);
			if (wordDicIt != wordDic.end())
				wordDicIt->second.push_back(word);
			else
			{
				vector<Word> vecOfWord;
				vecOfWord.push_back(word);
				wordDic.insert(pair<long long, vector<Word>>(rep, vecOfWord));
			}

			++currentMatch;
		}
	}

	return wordDic;
}

// This method, ExtractAnagrams(..), is supposed to follow the GetAllWords().
// Algorithm:
//		*	Create anagramLists a vector<vector<Word>>
//		*	cycle through all the words in wordDic
//		*		each iteration through the dictionary deals with an item having the same Anagram Key
//				(2 words with the same anagram key does not guarantee that the 2 words are anagramatic, they
//				may be the same or they may be non anagramatic.  However, words having different anagramatic key
//				are necessarily not anagrams.)
//				During each iteration we build the anagramLists as follows
//		*			if the word is part of any of the lists in the anagramLists then we do nothing
//					else if it is anagramit to any of the lists in the anagramLists then it is added to that list
//					else it is the beginning of a new list
vector<vector<Word>> AnagramParser::ExtractPotentialAnagrams(map<long long, vector<Word>> wordDic)
{
	// All words will be divvied up by their anagramatic indicator into these lists
	vector<vector<Word>> anagramLists;

	// Go through all input words 
	for (auto item : wordDic)
	{
		// If the word is a single word for the numeric representation then continue;
		if (item.second.size() == 1) continue;

		// In order to start the Anagram list take out the first word and match the rest of the words to it
		vector<Word> firstWordList { item.second[0] };

		// Add this list to the breakdown of the lists of anagrams
		anagramLists.push_back(firstWordList);

		// Cycle through all words in restOfWords
		auto restOfWordsIt = item.second.begin();
		++restOfWordsIt;
		auto wc = 1;
		for ( ; restOfWordsIt != item.second.end(); ++restOfWordsIt, ++wc)
		{
			auto currentRestWord = *restOfWordsIt;

			// Cycle through all list of potential anagrams
			auto wordCounted = false;
			auto alc = 0;
			for (auto localAnagramIt = anagramLists.begin(); localAnagramIt != anagramLists.end(); ++localAnagramIt, ++alc)
			{
				auto f = (*localAnagramIt)[0];
				auto isAnagram = Word::IsWordAnagram(f, currentRestWord);
				if (isAnagram == Word::SameWord)
				{
					wordCounted = true;
					break;
				}

				if (isAnagram == Word::YesAnagram)
				{
					// First make sure that it is not the same as any word in the list
					auto rcItr = find_if(localAnagramIt->begin(), localAnagramIt->end(), [&](auto s) { return Utils::IsStringSame(s.GetWordValue(), currentRestWord.GetWordValue()); });
					if (rcItr == localAnagramIt->end())
						localAnagramIt->push_back(*restOfWordsIt);

					wordCounted = true;
					break;
				}
			}

			// No List found containing the word, *restOfWordsIt, nor any word in the lists an anagram to the word, *restOfWordsIt, 
			// then add the word, *restOfWordsIt, to a new list
			if (!wordCounted)
				anagramLists.push_back(vector<Word> { *restOfWordsIt });
		}
	}

	return anagramLists;
}

vector<vector<string>> AnagramParser::ExtractAnagrams(vector<vector<Word>> anagramLists)
{
	vector<vector<string>> trueAnagrams;
	for (auto anList : anagramLists)
	{
		if (anList.size() == 1) continue;
		vector<string> trueList;
		for (auto a : anList)
			trueList.push_back(a.GetWordValue());

		trueAnagrams.push_back(trueList);
	}

	return trueAnagrams;
}

vector<vector<string>> AnagramParser::GetAnagrams()
{
	auto dicWords = GetAllWords();
	auto anagramLists = ExtractPotentialAnagrams(dicWords);
	auto trueLists = ExtractAnagrams(anagramLists);
	return trueLists;
}
