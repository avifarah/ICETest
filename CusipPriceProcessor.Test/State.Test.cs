using CusipPriceProcessor;
using Xunit;

namespace CusipPriceProcessor.Test
{
	public class StateTest
	{
		#region Cusip

		[Fact]
		public void CusipParse_LineContainsNoXtraSpaces_Successful()
		{
			// Arrange
			var line = "a2345678";
			var expectedCusip = line;

			// Act
			var actualCusip = line.GetCusip();

			// Assert
			Assert.Equal(expectedCusip, actualCusip);
		}

		[Fact]
		public void CusipParse_LineContainsLeadingAndTrailingSpaces_Successful()
		{
			// Arrange
			var line = " \ta2345678 \t\r\n";
			var expectedCusip = "a2345678";

			// Act
			var actualCusip = line.GetCusip();

			// Assert
			Assert.Equal(expectedCusip, actualCusip);
		}

		[Fact]
		public void CusipParse_CusipTooShort_Failure()
		{
			// Arrange
			var line = "a234567";

			// Act
			var actualCusip = line.GetCusip();

			// Assert
			Assert.Null(actualCusip);
		}

		[Fact]
		public void CusipParse_CusipTooLong_Failure()
		{
			// Arrange
			var line = "a23456789";

			// Act
			var actualCusip = line.GetCusip();

			// Assert
			Assert.Null(actualCusip);
		}

		[Fact]
		public void CusipParse_CusipContainsNonAlphnumericCharacters_Failure()
		{
			// Arrange
			var line = "a234.678";

			// Act
			var actualCusip = line.GetCusip();

			// Assert
			Assert.Null(actualCusip);
		}

		#endregion

		#region Price

		[Fact]
		public void PriceParse_LineContainsNoExtraSpace_PriceContainsLeadingDigits_Success()
		{
			// Arrange
			var line = "123.456";
			var expectedPrice = 123.456m;

			// Act
			var actualPrice = line.GetPrice();

			// Assert
			Assert.Equal(expectedPrice, actualPrice);
		}

		[Fact]
		public void PriceParse_LineContainsNoExtraSpace_PriceContainsNoLeadingDigits_Success()
		{
			// Arrange
			var line = ".456";
			var expectedPrice = 0.456m;

			// Act
			var actualPrice = line.GetPrice();

			// Assert
			Assert.Equal(expectedPrice, actualPrice);
		}

		[Fact]
		public void PriceParse_MissingDecimalPoint_Failure()
		{
			// Arrange
			var line = "123456";

			// Act
			var actualPrice = line.GetPrice();

			// Assert
			Assert.Null(actualPrice);
		}

		[Fact]
		public void PriceParse_MissingDigitsAfterDecimalsPoint_Failure()
		{
			// Arrange
			var line = "123456.";

			// Act
			var actualPrice = line.GetPrice();

			// Assert
			Assert.Null(actualPrice);
		}

		[Fact]
		public void PriceParse_ContainsNondigitCharacters_Failure()
		{
			// Arrange
			var line = "123o.456";

			// Act
			var actualPrice = line.GetPrice();

			// Assert
			Assert.Null(actualPrice);
		}

		[Fact]
		public void PriceParse_LineContainsContainingLeadingAndTrailingSpaces_PriceContainsLeadingDigits_Success()
		{
			// Arrange
			var line = " \t123.456 \t\r\n";
			var expectedPrice = 123.456m;

			// Act
			var actualPrice = line.GetPrice();

			// Assert
			Assert.Equal(expectedPrice, actualPrice);
		}

		#endregion
	}
}
