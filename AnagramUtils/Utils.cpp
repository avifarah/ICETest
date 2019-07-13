#include "pch.h"
#include "Utils.h"
#include <string>

using namespace std;

bool Utils::IsStringSame(string text1, string text2)
{
	return equal(text1.begin(), text1.end(), text2.begin(), text2.end(), [](char c1, char c2) { return toupper(c1) == toupper(c2); });
}
