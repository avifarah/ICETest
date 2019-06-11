#include "CusipLatestPrice.h"


CusipLatestPrice::CusipLatestPrice(string cusip, double price /*= std::numeric_limits<double>::lowest()*/) :
	Cusip(cusip), Price(price)
{
	if (Null == nullptr)
		Null = std::make_shared<CusipLatestPrice>(new CusipLatestPrice(nullptr));

	HasValue = (price > std::numeric_limits<double>::lowest());
}

CusipLatestPrice::~CusipLatestPrice() { }
