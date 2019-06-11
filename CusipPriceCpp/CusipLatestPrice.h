#include <string>
#pragma once

#include <limits>
#include <memory>

using std::string;

class CusipLatestPrice
{
public:
	CusipLatestPrice(string cusip, double price = std::numeric_limits<double>::lowest());
	~CusipLatestPrice();

	string Cusip;
	double Price;
	bool HasValue;
	std::shared_ptr<CusipLatestPrice> Null;
};
