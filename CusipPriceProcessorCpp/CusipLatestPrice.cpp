#include "pch.h"
#include "CusipLatestPrice.h"

#include <limits>

CusipLatestPrice::CusipLatestPrice(string cusip) : Cusip(cusip), Price(numeric_limits<double>::lowest()), hasValue(true)
{
}

CusipLatestPrice::CusipLatestPrice(string cusip, double price) : Cusip(cusip), Price(price), hasValue(true)
{
}

CusipLatestPrice::~CusipLatestPrice() {}

const CusipLatestPrice CusipLatestPrice::NoValue(string(""));

string CusipLatestPrice::GetCusip() { return Cusip; }

double CusipLatestPrice::GetPrice() { return Price; }

bool CusipLatestPrice::HasValue() { return hasValue; }

bool CusipLatestPrice::operator ==(const CusipLatestPrice& rhs) const
{
	const double epsilon = 1.0e-14;

	if (Cusip != rhs.Cusip) return false;

	// I assume that price will not grow abve a few 100s
	if (abs(Price - rhs.Price) > epsilon) return false;
	return true;
}

bool CusipLatestPrice::operator !=(const CusipLatestPrice& rhs) const
{
	return !(*this == rhs);
}
