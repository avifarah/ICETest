using System.Collections.Generic;
using System.IO;
using System.Text;
using Utils;
using Xunit;

namespace CusipPriceProcessor.Test
{
	public class CusipProcessorTest
	{
		[Fact]
		public void Readcusip_FileIsEmptyError_Failure()
		{
			// Arrange
			var feed = " ";
			var byteArray = Encoding.UTF8.GetBytes(feed);
			using (var feedMem = new MemoryStream(byteArray))
			using (var feedStream = new StreamReader(feedMem))
			{
				var proc = new CusipProcessor(feedStream);

				// Act
				var ex = Assert.Throws<FeedException>(proc.ReadCusip);

				// Assert
				Assert.Equal("First line of Feed is not a cusip", ex.Message);
				Assert.Equal(1, ex.CurrentLineCountOfException);
				Assert.Equal(feed, ex.LineOfException);
			}
		}

		[Fact]
		public void ReadPricesForCusips_FeedFileContainsOneCusipAndNoPrices_Failure()
		{
			// Arrange
			var feed = "A2345678";
			var byteArray = Encoding.UTF8.GetBytes(feed);
			using (var feedMem = new MemoryStream(byteArray))
			using (var feedStream = new StreamReader(feedMem))
			{
				var proc = new CusipProcessor(feedStream);
				var cusip = proc.ReadCusip();

				// Act
				var cusipPrices = proc.ReadPricesForCusips(cusip);
				var isCusipPrice = cusipPrices.GetEnumerator().MoveNext();

				// Assert
				Assert.False(isCusipPrice);
			}
		}

		[Fact]
		public void ReadPricesForCusips_FeedFileContainsTwoCusipAndNoPrices_Failure()
		{
			// Arrange
			var feed = @"A2345678
B2345678";
			var byteArray = Encoding.UTF8.GetBytes(feed);
			using (var feedMem = new MemoryStream(byteArray))
			using (var feedStream = new StreamReader(feedMem))
			{
				var proc = new CusipProcessor(feedStream);
				var cusip = proc.ReadCusip();

				// Act
				var cusipPrices = proc.ReadPricesForCusips(cusip);
				var ex = Assert.Throws<FeedException>(() => cusipPrices.GetEnumerator().MoveNext());

				// Assert
				Assert.Equal("Cusip A2345678 contains no price value", ex.Message);
				Assert.Equal(2, ex.CurrentLineCountOfException);
				Assert.Equal("B2345678", ex.LineOfException);
			}
		}

		[Fact]
		public void ReadPricesForCusips_LastLineIsNotBalnk_Successful()
		{
			// Arrange
			var feed = @"A2345678
123.456
B2345678
234.567
235.678
C2345678
345.678
346.789
347.89
348.901";
			var byteArray = Encoding.UTF8.GetBytes(feed);
			var cusipPricesDic = new Dictionary<string, decimal>();
			using (var feedMem = new MemoryStream(byteArray))
			using (var feedStream = new StreamReader(feedMem))
			{
				var proc = new CusipProcessor(feedStream);
				var cusip = proc.ReadCusip();

				// Act
				var cusipPrices = proc.ReadPricesForCusips(cusip);
				foreach (var clp in cusipPrices)
					cusipPricesDic.Add(clp.Cusip, clp.Price);

				// Assert
				Assert.Equal(123.456m, cusipPricesDic["A2345678"]);
				Assert.Equal(235.678m, cusipPricesDic["B2345678"]);
				Assert.Equal(348.901m, cusipPricesDic["C2345678"]);
			}
		}

		[Fact]
		public void ReadPricesForCusips_LastLineIsBalnk_Successful()
		{
			// Arrange
			var feed = @"A2345678
123.456
B2345678
234.567
235.678
C2345678
345.678
346.789
347.89
348.901

";
			var byteArray = Encoding.UTF8.GetBytes(feed);
			var cusipPricesDic = new Dictionary<string, decimal>();
			using (var feedMem = new MemoryStream(byteArray))
			using (var feedStream = new StreamReader(feedMem))
			{
				var proc = new CusipProcessor(feedStream);
				var cusip = proc.ReadCusip();

				// Act
				var cusipPrices = proc.ReadPricesForCusips(cusip);
				foreach (var clp in cusipPrices)
					cusipPricesDic.Add(clp.Cusip, clp.Price);

				// Assert
				Assert.Equal(123.456m, cusipPricesDic["A2345678"]);
				Assert.Equal(235.678m, cusipPricesDic["B2345678"]);
				Assert.Equal(348.901m, cusipPricesDic["C2345678"]);
			}
		}

		[Fact]
		public void ReadPricesForCusips_MiddleLineIsBalnk_Failure()
		{
			// Arrange
			var feed = @"A2345678
123.456
B2345678
234.567
235.678

C2345678
345.678
346.789
347.89
348.901
";
			var byteArray = Encoding.UTF8.GetBytes(feed);
			var cusipPricesDic = new Dictionary<string, decimal>();
			using (var feedMem = new MemoryStream(byteArray))
			using (var feedStream = new StreamReader(feedMem))
			{
				var proc = new CusipProcessor(feedStream);
				var cusip = proc.ReadCusip();

				// Act
				var cusipPrices = proc.ReadPricesForCusips(cusip);
				var ex = Assert.Throws<FeedException>(() => {
					foreach (var clp in cusipPrices)
						cusipPricesDic.Add(clp.Cusip, clp.Price);
				});

				// Assert
				Assert.Equal("A blank line in the middle of the file indicates a corrupt Feed file", ex.Message);
				Assert.Equal(7, ex.CurrentLineCountOfException);
				Assert.True(string.IsNullOrEmpty(ex.LineOfException));
			}
		}
	}
}

