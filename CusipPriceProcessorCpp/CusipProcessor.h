#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <regex>
#include <stdio.h>
#include "CusipLatestPrice.h"

using namespace std;

#ifdef  CUSIPPRICEPROCESSORCPP_EXPORTS
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT __declspec(dllimport)
#endif

class DLLEXPORT CusipProcessor
{
private:
	static regex cusipRe;
	static regex priceRe;
	ifstream& feedStream;
	int currentLineCount;
	double GetPrice(string line);
	string GetCusip(string line);
	string NextCusip;
	double PreviousPrice;

public:
	CusipProcessor(ifstream& feedStr);
	string ReadCusip();
	CusipLatestPrice ReadPricesForCusips();
};

