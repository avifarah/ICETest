#include "pch.h"
#include "CppUnitTest.h"
#include "..\\CusipPriceProcessorCpp\CusipProcessor.h"

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
	};
}
