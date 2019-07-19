#include "pch.h"
#include <regex>
#include <map>
#include "AnagramParser.h"

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

map<long, vector<Word>> AnagramParser::GetAllWords()
{
	map<long, vector<Word>> wordDic;
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
			map<long, vector<Word>>::iterator wordDicIt = wordDic.find(rep);
			if (wordDicIt != wordDic.end())
				wordDicIt->second.push_back(word);
			else
			{
				vector<Word> vecOfWord;
				vecOfWord.push_back(word);
				wordDic.insert(pair<long, vector<Word>>(rep, vecOfWord));
			}

			++currentMatch;
		}
	}

	return wordDic;
}

vector<vector<Word>> AnagramParser::ExtractPotentialAnagrams(map<long, vector<Word>> wordDic)
{
	vector<vector<Word>> anagramLists;

	for (auto item : wordDic)
	{
		// If the word is a single word for the numeric representation then continue;
		if (item.second.size() == 1) continue;

		// In order to start the Anagram list take out the first word and match the rest of the words to it
		vector<Word> vecWord;
		vecWord.push_back(item.second[0]);
		auto firstWordList = vecWord;

		// Add this list to the localAnagramList
		anagramLists.push_back(firstWordList);

		// Cycle through all words in restOfWords
		auto restOfWordsIt = item.second.begin();
		++restOfWordsIt;
		auto wc = 1;
		for ( ; restOfWordsIt != item.second.end(); ++restOfWordsIt, ++wc)
		{
			// Cycle through all list of potential anagrams
			auto wordCounted = false;
			auto alc = 0;
			for (auto localAnagramIt = anagramLists.begin(); localAnagramIt != anagramLists.end(); ++localAnagramIt, ++alc)
			{
				auto f = (*localAnagramIt)[0];
				auto isAnagram = Word::IsWordAnagram(f, *restOfWordsIt);
				if (isAnagram == Word::SameWord)
				{
					wordCounted = true;
					break;
				}

				if (isAnagram == Word::YesAnagram)
				{
					// First make sure that it is not the same as any word in the list
					auto rcItr = find_if(localAnagramIt->begin(), localAnagramIt->end(),
						[&](auto& s) {
							if (s.GetWordValue().size() != (*restOfWordsIt).GetWordValue().size()) return false;
							for (size_t i = 0; i < s.GetWordValue().size(); ++i)
								if (::tolower(s.GetWordValue()[i]) == ::tolower((*restOfWordsIt).GetWordValue()[i])) return true;
							return false;
						}
					);
					if (rcItr != localAnagramIt->end())
						(*localAnagramIt).push_back(*restOfWordsIt);

					wordCounted = true;
					break;
				}
			}

			if (!wordCounted)
			{
				// No List found and word is not used add a new list
				vector<Word> rest;
				rest.push_back(*restOfWordsIt);
				anagramLists.push_back(rest);
			}
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
