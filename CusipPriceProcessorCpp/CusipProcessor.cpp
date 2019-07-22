#include "pch.h"
#include <limits>
#include <sstream>
#include <regex>
#include "CusipProcessor.h"
#include "..\\UtilsCpp\FeedExceptionCpp.h"
#include "..\\UtilsCpp\StringExt.h"

using namespace std;

static regex CusipReCusipProcessor("^\\s*(\\w{8})\\s*$");
static regex PriceReCusipProcessor("^\\s*(\\d*\\.\\d+)\\s*$");
static string emptyNextCusipCusipProcessor = string("");

regex& CusipProcessor::cusipRe(CusipReCusipProcessor);
regex& CusipProcessor::priceRe(PriceReCusipProcessor);

CusipProcessor::CusipProcessor(ifstream& feedStr) : feedStream(feedStr), currentLineCount(0), NextCusip(emptyNextCusipCusipProcessor), PreviousPrice(0.0)
{
}

CusipProcessor::~CusipProcessor()
{
}

string CusipProcessor::ReadCusip()
{
	if (feedStream.eof()) return string("");

	string cusip;
	getline(feedStream, cusip);
	++currentLineCount;
	if (cusip.empty())
		throw FeedExceptionCpp(string("First line of Feed is not a cusip"), currentLineCount, cusip);

	NextCusip = cusip;
	return cusip;
}

double CusipProcessor::GetPrice(string line)
{
	smatch matches;
	regex_search(line, matches, priceRe);
	if (matches.empty())
		return numeric_limits<double>::lowest();

	auto sPrice = matches.str(1);
	auto price = atof(sPrice.c_str());
	return price;
}

string CusipProcessor::GetCusip(string line)
{
	smatch matches;
	regex_search(line, matches, cusipRe);
	if (matches.empty())
		return emptyNextCusipCusipProcessor;

	auto cusip = matches.str(1);
	return cusip;
}


CusipLatestPrice CusipProcessor::ReadPricesForCusips()
{
	auto isPreviousBlank = false;
	string cusip = NextCusip;

	// Loop through the cusips
	for (; ; )
	{
		if (feedStream.eof()) return CusipLatestPrice::NoValue;

		// Loop through prices
		for (; ; )
		{
			if (feedStream.eof())
			{
				if (PreviousPrice == numeric_limits<double>::lowest())
				{
					stringstream msg;
					msg << "Cusip " << cusip << " contains no price value";
					throw FeedExceptionCpp(msg.str(), currentLineCount);
				}
				return CusipLatestPrice(cusip, PreviousPrice);
			}

			string line = string("");
			if (feedStream.peek() == '\n')
			{
				istreambuf_iterator<char> iter(feedStream);
				++iter;
				++currentLineCount;
			}
			else if (feedStream.peek() == '\r')
			{
				// Advance the file by 1 char and do not inc line count
				istreambuf_iterator<char> iter(feedStream);
				++iter;
				continue;
			}
			else
			{
				getline(feedStream, line);
				++currentLineCount;
			}

			// It is acceptable for the last lines to be blank lines
			if (Trim(line) == string(""))
			{
				isPreviousBlank = true;
				continue;
			}
			else if (isPreviousBlank)
			{
				throw FeedExceptionCpp("A blank line in the middle of the file indicates a corrupt Feed file", currentLineCount, line);
			}

			auto price = GetPrice(line);
			if (price == numeric_limits<double>::lowest())
			{
				auto nextCusip = GetCusip(line);
				if (nextCusip == string(""))
				{
					throw FeedExceptionCpp("Line is neither a cusip nor a price", currentLineCount, line);
				}
				if (PreviousPrice == numeric_limits<double>::lowest())
				{
					stringstream msg;
					msg << "Cusip " << cusip << " contains no price value";
					throw FeedExceptionCpp(msg.str(), currentLineCount, line);
				}

				auto prevCusip = cusip;
				NextCusip = nextCusip;
				price = PreviousPrice;
				PreviousPrice = numeric_limits<double>::lowest();
				return CusipLatestPrice(prevCusip, price);
			}

			PreviousPrice = price;
		}
	}
}

