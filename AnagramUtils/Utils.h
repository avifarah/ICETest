#pragma once

#include <string>
#include <algorithm>

using namespace std;

#ifdef ANAGRAMUTILS_EXPORTS
	#define ANAGRAM_DLLEXPORT __declspec(dllexport)
	#pragma message ("__declspec(dllexport)")
#else
	#define ANAGRAM_DLLEXPORT __declspec(dllimport)
	#pragma message ("__declspec(dllimport)")
#endif

class ANAGRAM_DLLEXPORT Utils
{
public:
	static bool IsStringSame(string text1, string text2);
};

