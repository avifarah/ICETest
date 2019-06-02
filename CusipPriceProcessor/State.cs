using System.Text.RegularExpressions;

namespace CusipPriceProcessor
{
	public static class State
	{
		private static Regex _cusipRe = new Regex(@"^\s*(?<cusip>\w{8})\s*$");
		private static Regex _priceRe = new Regex(@"^\s*(?<price>\d*\.\d+)\s*$");

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
