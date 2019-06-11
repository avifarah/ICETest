
namespace CusipPriceProcessor
{
	public struct CusipLatestPrice
	{
		public string Cusip { get; }

		public decimal Price { get; }

		public bool HasValue { get; }

		public static CusipLatestPrice Null = new CusipLatestPrice(null);

		public CusipLatestPrice(string cusip, decimal price)
		{
			Cusip = cusip;
			Price = price;
			HasValue = true;
		}

		public CusipLatestPrice(string cusip)
		{
			Cusip = cusip;
			Price = decimal.MinValue;
			HasValue = false;
		}
	}
}
