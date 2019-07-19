#include "pch.h"
#include "CppUnitTest.h"
#include "..\\AnagramUtils\AnagramException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnagramCppTest
{
	TEST_CLASS(AnagramCppExceptionTest)
	{
	public:

		TEST_METHOD(TestException_1)
		{
			// Arrange
			string expectedMessage = "Test Anagram Exception";
			string expectedWord = "TestWord";
			int expectedLineCount = 0;
			int expectedWordCount = 0;

			try
			{
				// Act
				throw AnagramException("Test Anagram Exception", "TestWord");
			}
			catch (AnagramException ex)
			{
				// Assert
				Assert::AreEqual(expectedMessage, ex.GetExMessage());
				Assert::AreEqual(expectedWord, ex.GetWord());
				Assert::AreEqual(expectedLineCount, ex.GetLineCount());
				Assert::AreEqual(expectedWordCount, ex.GetWordCount());
			}
		}

		TEST_METHOD(TestException_2)
		{
			// Arrange
			string expectedMessage = "Test Anagram Exception";
			string expectedWord = "TestWord";
			int expectedLineCount = 123;
			int expectedWordCount = 0;

			try
			{
				// Act
				throw AnagramException("Test Anagram Exception", "TestWord", 123);
			}
			catch (AnagramException ex)
			{
				// Assert
				Assert::AreEqual(expectedMessage, ex.GetExMessage());
				Assert::AreEqual(expectedWord, ex.GetWord());
				Assert::AreEqual(expectedLineCount, ex.GetLineCount());
				Assert::AreEqual(expectedWordCount, ex.GetWordCount());
			}
		}

		TEST_METHOD(TestException_3)
		{
			// Arrange
			string expectedMessage = "Test Anagram Exception";
			string expectedWord = "TestWord";
			int expectedLineCount = 123;
			int expectedWordCount = 456;

			try
			{
				// Act
				throw AnagramException("Test Anagram Exception", "TestWord", 123, 456);
			}
			catch (AnagramException ex)
			{
				// Assert
				Assert::AreEqual(expectedMessage, ex.GetExMessage());
				Assert::AreEqual(expectedWord, ex.GetWord());
				Assert::AreEqual(expectedLineCount, ex.GetLineCount());
				Assert::AreEqual(expectedWordCount, ex.GetWordCount());
			}
		}
	};
}
