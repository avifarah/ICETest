#include "pch.h"
#include "CppUnitTest.h"
#include "..\\UtilsCpp\FeedExceptionCpp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FeedExceptionCppTest
{
	TEST_CLASS(FeedExceptoinCppTest)
	{
	public:

		TEST_METHOD(FeedException_MessageOnly_Success)
		{
			// Assert
			auto msg = string("Test message");
			auto expectedMsg = msg;
			auto expectedLineCountOfException = -1;
			auto expectedLineOfException = string("");

			try
			{
				// Act
				throw FeedExceptionCpp(msg);
			}
			catch (FeedExceptionCpp ex)
			{
				// Assert
				Assert::AreEqual(expectedMsg, ex.GetExMessage());
				Assert::AreEqual(expectedLineCountOfException, ex.GetCurrentLineCountOfException());
				Assert::AreEqual(expectedLineOfException, ex.GetLineOfException());
			}
		}

		TEST_METHOD(FeedException_MessageAndLineCountOnly_Success)
		{
			// Assert
			auto msg = string("Test message");
			auto expectedMsg = msg;
			auto expectedLineCountOfException = 123;
			auto expectedLineOfException = string("");

			try
			{
				// Act
				throw FeedExceptionCpp(msg, 123);
			}
			catch (FeedExceptionCpp ex)
			{
				// Assert
				Assert::AreEqual(expectedMsg, ex.GetExMessage());
				Assert::AreEqual(expectedLineCountOfException, ex.GetCurrentLineCountOfException());
				Assert::AreEqual(expectedLineOfException, ex.GetLineOfException());
			}
		}

		TEST_METHOD(FeedException_MessageLineCountAndLineofexception_Success)
		{
			// Assert
			auto msg = string("Test message");
			auto expectedMsg = msg;
			auto expectedLineCountOfException = 123;
			auto expectedLineOfException = string("Line of exception");

			try
			{
				// Act
				throw FeedExceptionCpp(msg, 123, "Line of exception");
			}
			catch (FeedExceptionCpp ex)
			{
				// Assert
				Assert::AreEqual(expectedMsg, ex.GetExMessage());
				Assert::AreEqual(expectedLineCountOfException, ex.GetCurrentLineCountOfException());
				Assert::AreEqual(expectedLineOfException, ex.GetLineOfException());
			}
		}
	};
}
