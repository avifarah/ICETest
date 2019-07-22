#include "pch.h"
#include "CppUnitTest.h"
#include "..\\UtilsCpp\StringExt.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StringExtCppTest
{
	TEST_CLASS(StringExtCppTest)
	{
	public:

		TEST_METHOD(TrimTest_StringEmpty)
		{
			// Arrange
			string empty = "";
			string expected = "";

			// Act
			auto actual = Trim(empty);

			// Assert;
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TrimTest_NoLeadingNoTrailing)
		{
			// Arrange
			string Orig = "abc123DoReMe";
			string expected = "abc123DoReMe";

			// Act
			auto actual = Trim(Orig);

			// Assert;
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TrimTest_LeadingSpace)
		{
			// Arrange
			string Orig = " \t  abc123DoReMe";
			string expected = "abc123DoReMe";

			// Act
			auto actual = Trim(Orig);

			// Assert;
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TrimTest_TrailingSpace)
		{
			// Arrange
			string Orig = "abc123DoReMe \t  ";
			string expected = "abc123DoReMe";

			// Act
			auto actual = Trim(Orig);

			// Assert;
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TrimTest_LeadingAndTrailingSpace)
		{
			// Arrange
			string Orig = " \t\t abc123DoReMe \t  ";
			string expected = "abc123DoReMe";

			// Act
			auto actual = Trim(Orig);

			// Assert;
			Assert::AreEqual(expected, actual);
		}
	};
}
