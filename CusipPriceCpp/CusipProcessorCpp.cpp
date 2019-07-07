#include "CusipProcessorCpp.h"
#include "FeedExceptionCpp.h"

using namespace std;

regex CusipProcessorCpp::cusipRe("^\\s*(\\w{8})\\s*$");
regex CusipProcessorCpp::priceRe("^\\s*(\\d*\\.\\d+)\\s*$");

CusipProcessorCpp::CusipProcessorCpp(ifstream& feedStream) : feedStream(feedStream)
{
}

CusipProcessorCpp::~CusipProcessorCpp()
{
}

// <summary>
// This method will be used for the first line of the feed file to be read which is expected to be a cusip
// </summary>
string CusipProcessorCpp::ReadCusip()
{
	if (feedStream.eof()) return string("");

	string cusip;
	getline(feedStream, cusip);
	++currentLineCount;
	if (cusip.empty())
		throw FeedExceptionCpp("First line of Feed is not a cusip", currentLineCount, cusip);

	return cusip;
}

/*
		/// <summary>
		/// This method will be used for the first line of the feed file to be read which is expected to be a cusip
		/// </summary>
		/// <returns></returns>
		public string ReadCusip()
		{
			if (feedStream.EndOfStream) throw new FeedException("Feed file seems to be empty", 1, string.Empty);

			// Reading asyncronously of a single line may be an overkill, it will be useful if the file is in a remote location
			// In which case we will need to provide a timeout mechanism.  Since decorating the method as async and returning a Task<string>
			// I decided that this is a half baked solution and as such we will read the file synchronously as opposed to the decoration and
			// The read as follows:
			//		var line = await feedStream.ReadLineAsync().ConfigureAwait(false);
			var line = feedStream.ReadLine();
			++currentLineCount;
			var cusip = line.GetCusip();
			if (cusip == null) throw new FeedException("First line of Feed is not a cusip", currentLineCount, line);

			return cusip;
		}
*/

string CusipProcessorCpp::GetCusip(string line)
{
	smatch m;
	auto rc = regex_search(line, m, cusipRe);
	if (!rc) return string("");

	return m.str(1);
}

double CusipProcessorCpp::GetPrice(string line)
{
	smatch m;
	auto rc = regex_search(line, m, priceRe);
	if (!rc) return numeric_limits<double>::min();

	auto sPrice = m.str(1);
	auto price = stod(sPrice);
	return price;
}

/*
		public static decimal? GetPrice(this string line)
		{
			var m = priceRe.Match(line);
			if (!m.Success) return null;

			var sPrice = m.Groups["price"].Value;
			var price = decimal.Parse(sPrice);
			return price;
		}
*/
