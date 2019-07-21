#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include "LetterRepresentation.h"
#include "Word.h"

using namespace std;

#ifdef ANAGRAMUTILS_EXPORTS
	#define ANAGRAM_DLLEXPORT __declspec(dllexport)
	#pragma message ("__declspec(dllexport)")
#else
	#define ANAGRAM_DLLEXPORT __declspec(dllimport)
	#pragma message ("__declspec(dllimport)")
#endif

class ANAGRAM_DLLEXPORT AnagramParser
{
private:
	ifstream& TextStream;
	LetterRepresentation Rep;
	static regex& WordRe;

	vector<vector<string>> ExtractAnagrams(vector<vector<Word>> anagramLists);

public:
	AnagramParser(ifstream& textStream);
	AnagramParser(ifstream& textStream, LetterRepresentation rep);
	~AnagramParser();

	map<long long, vector<Word>> GetAllWords();
	vector<vector<Word>> ExtractPotentialAnagrams(map<long long, vector<Word>> wordDic);
	vector<vector<string>> GetAnagrams();
};

