#pragma once

#include <string>
#include <stdlib.h>

using namespace std;

#ifdef  CUSIPPRICEPROCESSORCPP_EXPORTS
	#define CUSIP_LATEST_PRICE_EXPORT __declspec(dllexport)
	#pragma message("__declspec(dllexport)")
#else
	#define CUSIP_LATEST_PRICE_EXPORT __declspec(dllimport)
	#pragma message("__declspec(dllimport)")
#endif

class CUSIP_LATEST_PRICE_EXPORT CusipLatestPrice
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

	bool operator ==(const CusipLatestPrice& rhs) const;
	bool operator !=(const CusipLatestPrice& rhs) const;
};
