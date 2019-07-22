using System.Text.RegularExpressions;

namespace CusipPriceProcessor
{
	public static class State
	{
		/// <summary>A cusip is an 8 alphanumeric characters long</summary>
		private static readonly Regex _cusipRe = new Regex(@"^\s*(?<cusip>\w{8})\s*$");

		/// <summary>Format of a price is defined by the examples: 95.752 and 101.255</summary>
		private static readonly Regex _priceRe = new Regex(@"^\s*(?<price>\d*\.\d+)\s*$");

		public static string GetCusip(this string line)
		{
			var m = _cusipRe.Match(line);
			if (!m.Success) return null;

			return m.Groups["cusip"].Value;
		}

		public static decimal? GetPrice(this string line)
		{
			var m = _priceRe.Match(line);
			if (!m.Success) return null;

			var sPrice = m.Groups["price"].Value;
			var price = decimal.Parse(sPrice);
			return price;
		}
	}
}
