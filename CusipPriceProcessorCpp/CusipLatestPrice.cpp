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
