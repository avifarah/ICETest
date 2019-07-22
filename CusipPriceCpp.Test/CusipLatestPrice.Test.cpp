#include "pch.h"
#include "CppUnitTest.h"
#include "..\\CusipPriceProcessorCpp\CusipLatestPrice.h"
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CusipLatestPriceTest
{
	TEST_CLASS(CusipLatestPriceCppTest)
	{
	public:

		TEST_METHOD(CusipOnlyTest_Equal)
		{
			// Arrange
			auto clp1 = CusipLatestPrice("A2345678");
			auto clp2 = CusipLatestPrice("A2345678");
			auto expected = true;

			// Act
			auto actual1 = (clp1 == clp2);
			auto actual2 = !(clp1 != clp2);

			// Assert
			Assert::AreEqual(expected, actual1);
			Assert::AreEqual(expected, actual2);
		}

		TEST_METHOD(CusipOnlyTest_NotEqual)
		{
			// Arrange
			auto clp1 = CusipLatestPrice("A2345678");
			auto clp2 = CusipLatestPrice("B2345678");
			auto expected = false;

			// Act
			auto actual = (clp1 == clp2);

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(CusipPriceTest_Equal)
		{
			// Arrange
			auto clp1 = CusipLatestPrice("A2345678", 1.234);
			auto clp2 = CusipLatestPrice("A2345678", 1.234);
			auto expected = true;

			// Act
			auto actual1 = (clp1 == clp2);
			auto actual2 = !(clp1 != clp2);

			// Assert
			Assert::AreEqual(expected, actual1);
			Assert::AreEqual(expected, actual2);
		}

		TEST_METHOD(NoValueTest_Equal)
		{
			// Arrange
			auto clp1 = CusipLatestPrice::NoValue;
			auto clp2 = CusipLatestPrice::NoValue;
			auto expected = true;

			// Act
			auto actual1 = (clp1 == clp2);
			auto actual2 = !(clp1 != clp2);

			// Assert
			Assert::AreEqual(expected, actual1);
			Assert::AreEqual(expected, actual2);
		}

		TEST_METHOD(NoValueTest_Equal_2)
		{
			// Arrange
			auto clp1 = CusipLatestPrice::NoValue;
			auto clp2 = CusipLatestPrice("", numeric_limits<double>::lowest());
			auto expected = true;

			// Act
			auto actual1 = (clp1 == clp2);
			auto actual2 = !(clp1 != clp2);

			// Assert
			Assert::AreEqual(expected, actual1);
			Assert::AreEqual(expected, actual2);
		}

		TEST_METHOD(CusipPriceTest_NotEqualCusip)
		{
			// Arrange
			auto clp1 = CusipLatestPrice("A2345678", 1.234);
			auto clp2 = CusipLatestPrice("B2345678", 1.234);
			auto expected = false;

			// Act
			auto actual1 = (clp1 == clp2);
			auto actual2 = !(clp1 != clp2);

			// Assert
			Assert::AreEqual(expected, actual1);
			Assert::AreEqual(expected, actual2);
		}

		TEST_METHOD(CusipPriceTest_NotEqualPrice)
		{
			// Arrange
			auto clp1 = CusipLatestPrice("A2345678", 1.234);
			auto clp2 = CusipLatestPrice("A2345678", 1.2345);
			auto expected = false;

			// Act
			auto actual1 = (clp1 == clp2);
			auto actual2 = !(clp1 != clp2);

			// Assert
			Assert::AreEqual(expected, actual1);
			Assert::AreEqual(expected, actual2);
		}

		TEST_METHOD(CusipPriceTest_NotEqualCusipNotEqualPrice)
		{
			// Arrange
			auto clp1 = CusipLatestPrice("A2345678", 1.234);
			auto clp2 = CusipLatestPrice("B2345678", 1.2345);
			auto expected = false;

			// Act
			auto actual1 = (clp1 == clp2);
			auto actual2 = !(clp1 != clp2);

			// Assert
			Assert::AreEqual(expected, actual1);
			Assert::AreEqual(expected, actual2);
		}

		TEST_METHOD(GetCusipTest_Success)
		{
			// Arrange
			auto clp = CusipLatestPrice("A2345678", 1.234);
			auto expected = string("A2345678");

			// Act
			auto actual = clp.GetCusip();

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(GetPriceTest_Success)
		{
			// Arrange
			auto clp = CusipLatestPrice("A2345678", 1.234);
			auto expected = 1.234;
			const double epsilon = 1e-14;

			// Act
			auto actual = clp.GetPrice();

			// Assert
			Assert::IsTrue(abs(expected - actual) < epsilon);
		}

		TEST_METHOD(HasValueTest_Success)
		{
			// Arrange
			auto clp = CusipLatestPrice("A2345678", 1.234);
			auto expected = true;

			// Act
			auto actual = clp.HasValue();

			// Assert
			Assert::AreEqual(expected, actual);
		}
	};
}
