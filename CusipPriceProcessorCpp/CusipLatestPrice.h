#pragma once

#include <string>

using namespace std;

#ifdef  CUSIPPRICEPROCESSORCPP_EXPORTS
	#define DLLEXPORT __declspec(dllexport)
#else
	#define DLLEXPORT __declspec(dllimport)
#endif

class DLLEXPORT CusipLatestPrice
{
private:
	string Cusip;
	double Price;
	bool hasValue;

public:
	CusipLatestPrice(string cusip);
	CusipLatestPrice(string, double price);
	~CusipLatestPrice();
	static const CusipLatestPrice NoValue;
	string GetCusip();
	double GetPrice();
	bool HasValue();
};
