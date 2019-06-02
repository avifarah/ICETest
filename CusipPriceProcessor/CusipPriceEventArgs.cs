using System;

namespace CusipPriceProcessor
{
	public class CusipPriceEventArgs : EventArgs
	{
		public string Cusip { get; }

		public decimal LatestPrice { get; }

		public CusipPriceEventArgs(string cusip, decimal price)
		{
			Cusip = cusip;
			LatestPrice = price;
		}
	}
}
