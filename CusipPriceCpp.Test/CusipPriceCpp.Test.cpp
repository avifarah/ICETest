#include "pch.h"
#include "CppUnitTest.h"
#include "..\\CusipPriceProcessorCpp\CusipProcessor.h"
#include "..\\UtilsCpp\FeedExceptionCpp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CusipPriceCppTest
{
	TEST_CLASS(CusipPriceCppTest)
	{
	public:

		TEST_METHOD(ReadCusipTest_Success)
		{
			// Arrange
			ifstream ifs("G:\\Dev\\ICE.Core\\CusipPriceCpp.Test\\CusipPrice-1.txt");
			auto cp = CusipProcessor(ifs);

			// Act
			auto actual = cp.ReadCusip();
			auto expected = string("A2345678");

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(ReadPriceTest_Success)
		{
			// Arrange
			ifstream ifs("G:\\Dev\\ICE.Core\\CusipPriceCpp.Test\\CusipPrice-1.txt");
			auto cp = CusipProcessor(ifs);

			// Act
			auto expected = CusipLatestPrice(string("A2345678"), atof("123.456"));
			auto cusip = cp.ReadCusip();
			auto actual = cp.ReadPricesForCusips();

			// Assert
			Assert::AreEqual(expected.GetCusip(), actual.GetCusip());
			Assert::AreEqual(expected.GetPrice(), actual.GetPrice());
			Assert::AreEqual(expected.HasValue(), actual.HasValue());
		}

		TEST_METHOD(ReadPriceTest_ExtraSpce_Error)
		{
			// Arrange
			auto expectedMsg = string("A blank line in the middle of the file indicates a corrupt Feed file");
			auto expectedLc = 4;
			auto expectedLine = string("B2345678");

			try
			{
				// Arrange
				ifstream ifs("G:\\Dev\\ICE.Core\\CusipPriceCpp.Test\\CusipPrice-extraSpace-Error.txt");
				auto cp = CusipProcessor(ifs);

				// Act
				auto cusip = cp.ReadCusip();
				auto latestPrice = cp.ReadPricesForCusips();
				Assert::Fail();
			}
			catch (FeedExceptionCpp ex)
			{
				// Assert
				Assert::AreEqual(expectedMsg, ex.GetExMessage());
				Assert::AreEqual(expectedLc, ex.GetCurrentLineCountOfException());
				Assert::AreEqual(expectedLine, ex.GetLineOfException());
			}
		}

		TEST_METHOD(ReadPriceTest_CusipCusip_Error)
		{
			// Arrange
			auto expectedMsg = string("Cusip B2345678 contains no price value");
			auto expectedLc = 4;
			auto expectedLine = string("C2345678");

			try
			{
				// Arrange
				ifstream ifs("G:\\Dev\\ICE.Core\\CusipPriceCpp.Test\\CusipPrice-CusipCusip-Error.txt");
				auto cp = CusipProcessor(ifs);

				// Act
				auto cusip = cp.ReadCusip();
				auto latestPrice = cp.ReadPricesForCusips();
				auto latestPrice2 = cp.ReadPricesForCusips();
				Assert::Fail();
			}
			catch (FeedExceptionCpp ex)
			{
				// Assert
				Assert::AreEqual(expectedMsg, ex.GetExMessage());
				Assert::AreEqual(expectedLc, ex.GetCurrentLineCountOfException());
				Assert::AreEqual(expectedLine, ex.GetLineOfException());
			}
		}

		TEST_METHOD(ReadPriceTest_FirstLineBlank_Error)
		{
			// Arrange
			auto expectedMsg = string("First line of Feed is not a cusip");
			auto expectedLc = 1;
			auto expectedLine = string("");

			try
			{
				// Arrange
				ifstream ifs("G:\\Dev\\ICE.Core\\CusipPriceCpp.Test\\CusipPrice-FirstLineBlank.txt");
				auto cp = CusipProcessor(ifs);

				// Act
				auto cusip = cp.ReadCusip();
				Assert::Fail();
			}
			catch (FeedExceptionCpp ex)
			{
				// Assert
				Assert::AreEqual(expectedMsg, ex.GetExMessage());
				Assert::AreEqual(expectedLc, ex.GetCurrentLineCountOfException());
				Assert::AreEqual(expectedLine, ex.GetLineOfException());
			}
		}

		TEST_METHOD(ReadPriceTest_SecondLineBlank_Error)
		{
			// Arrange
			auto expectedMsg = string("A blank line in the middle of the file indicates a corrupt Feed file");
			auto expectedLc = 3;
			auto expectedLine = string("123.456");

			try
			{
				// Arrange
				ifstream ifs("G:\\Dev\\ICE.Core\\CusipPriceCpp.Test\\CusipPrice-SeondLineBlank.txt");
				auto cp = CusipProcessor(ifs);

				// Act
				auto cusip = cp.ReadCusip();
				auto latestPrice = cp.ReadPricesForCusips();
				Assert::Fail();
			}
			catch (FeedExceptionCpp ex)
			{
				// Assert
				Assert::AreEqual(expectedMsg, ex.GetExMessage());
				Assert::AreEqual(expectedLc, ex.GetCurrentLineCountOfException());
				Assert::AreEqual(expectedLine, ex.GetLineOfException());
			}
		}
	};
}
