#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <regex>
#include <stdio.h>
#include "CusipLatestPrice.h"

using namespace std;

#ifdef  CUSIPPRICEPROCESSORCPP_EXPORTS
	#define CUSIP_PROCESSOR_EXPORT __declspec(dllexport)
	#pragma message("__declspec(dllexport)")
#else
	#define CUSIP_PROCESSOR_EXPORT __declspec(dllimport)
	#pragma message("__declspec(dllimport)")
#endif

class CUSIP_PROCESSOR_EXPORT CusipProcessor
{
private:
	static regex& cusipRe;
	static regex& priceRe;
	ifstream& feedStream;
	int currentLineCount;
	double GetPrice(string line);
	string& GetCusip(string line);
	string& NextCusip;
	double PreviousPrice;

public:
	CusipProcessor(ifstream& feedStr);
	~CusipProcessor();
	string ReadCusip();
	CusipLatestPrice ReadPricesForCusips();
};

