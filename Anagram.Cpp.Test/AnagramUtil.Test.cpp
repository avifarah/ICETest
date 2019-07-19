#include "pch.h"
#include "CppUnitTest.h"
#include "..\\AnagramUtils\Utils.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

namespace AnagramCppTest
{
	TEST_CLASS(AnagramCppUtilTest)
	{
	public:

		TEST_METHOD(IdentialStrings_Success)
		{
			// Arrange
			string str1 = "abc";
			string str2 = "abc";
			bool expected = true;

			// Act
			auto actual = Utils::IsStringSame(str1, str2);

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(IdentialEmptyStrings_Success)
		{
			// Arrange
			string str1 = "";
			string str2 = "";
			bool expected = true;

			// Act
			auto actual = Utils::IsStringSame(str1, str2);

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(DifferingByCaseOnlyStrings_Success)
		{
			// Arrange
			string str1 = "Abc";
			string str2 = "aBC";
			bool expected = true;

			// Act
			auto actual = Utils::IsStringSame(str1, str2);

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(DifferentStrings_Success)
		{
			// Arrange
			string str1 = "Abc";
			string str2 = "aBC1";
			bool expected = false;

			// Act
			auto actual = Utils::IsStringSame(str1, str2);

			// Assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(DifferentStringsSameLength_Success)
		{
			// Arrange
			string str1 = "Abc2";
			string str2 = "aBC1";
			bool expected = false;

			// Act
			auto actual = Utils::IsStringSame(str1, str2);

			// Assert
			Assert::AreEqual(expected, actual);
		}
	};
}
