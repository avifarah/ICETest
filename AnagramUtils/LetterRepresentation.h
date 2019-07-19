#pragma once

#include "pch.h"
#include <map>
#include <string>

using namespace std;

#ifdef  ANAGRAMUTILS_EXPORTS
#define LETTEREXPORT __declspec(dllexport)
#pragma message ("__declspec(dllexport)")
#else
#define LETTEREXPORT __declspec(dllimport)
#pragma message ("__declspec(dllimport)")
#endif

class LETTEREXPORT LetterRepresentation
{
private:
	map<char, long> LetterRep;

public:
	LetterRepresentation();
	LetterRepresentation(map<char, long> dic);
	~LetterRepresentation();
	long WordRep(string word, int lineCount = 0, int wordCount = 0);
};
