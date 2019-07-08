//Trim trailing and leading white spaces from both ends of a string

#include "pch.h"

#include "StringExt.h"
#include <iostream>
#include <vector>

string Trim(string text)
{
	if (text.length() == 0) return text;

	int inxBeg = 0;
	while (text.at(inxBeg) == ' ' || text.at(inxBeg) == '\t') inxBeg++;

	int inxEnd = text.length() - 1;
	while (text.at(inxEnd) == ' ' || text.at(inxEnd) == '\t') inxEnd--;

	auto trimmed = text.substr(inxBeg, inxEnd - inxBeg + 1);
	return trimmed;
};