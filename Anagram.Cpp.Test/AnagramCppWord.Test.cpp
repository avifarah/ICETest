#include "pch.h"
#include "CppUnitTest.h"
#include "..\\AnagramUtils\Word.h"
#include "..\\AnagramUtils\AnagramException.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

namespace AnagramCppTest
{
	TEST_CLASS(AnagramCppWordTest)
	{
	public:

		TEST_METHOD(TestWord_WordRep)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr = "WordTest";
			long long expWordRepresentation = (long long)755811883L/*W*/ + (long long)752418720L/*o*/ + (long long)1300586832L/*r*/ +
				(long long)1198613964L/*d*/ + (long long)1687192378L/*T*/ + (long long)900798196L/*e*/ + (long long)2106012734L/*s*/ + (long long)1687192378L/*t*/;

			// Act
			auto word = Word(rep, wStr);

			// Assert
			Assert::AreEqual(expWordRepresentation, word.GetWordRepresentation());
		}

		TEST_METHOD(TestWord_WordValue)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr = "WordTest";
			string expectedValue = "WordTest";

			// Act
			auto word = Word(rep, wStr);

			// Assert
			Assert::AreEqual(expectedValue, word.GetWordValue());
		}

		TEST_METHOD(TestWord_WordKey_Exception)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr = "WordTest";
			string expectedMsg = "WordKey was not set";
			auto word = Word(rep, wStr);

			try
			{
				// Act
				auto wordKey = word.GetWordKey();
				Assert::Fail();
			}
			catch (AnagramException ex)
			{
				// Assert
				Assert::AreEqual(expectedMsg, ex.GetExMessage());
				Assert::AreEqual(wStr, ex.GetWord());
			}
		}

		TEST_METHOD(TestWord_WordKey)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr = "WordTest";
			string expectedValue1 = "deorsTtW";
			string expectedValue2 = "deorstTW";
			auto word = Word(rep, wStr);
			auto retWordKey = Word::GetWordKey(word);

			// Act
			auto wordKey = word.GetWordKey();

			// Assert
			Assert::AreEqual(retWordKey, wordKey);
			Assert::IsTrue(expectedValue1 == wordKey || expectedValue2 == wordKey);
		}

		TEST_METHOD(TestWord_IsWordSame_True)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr1 = "WordTest";
			string wStr2 = "WordTest";
			auto word1 = Word(rep, wStr1);
			auto word2 = Word(rep, wStr2);

			// Act
			auto isSame = Word::IsWordSame(word1, word2);

			// Assert
			Assert::IsTrue(isSame);
		}

		TEST_METHOD(TestWord_IsWordSame2_True)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr1 = "WordTest";
			string wStr2 = "wORDtEST";
			auto word1 = Word(rep, wStr1);
			auto word2 = Word(rep, wStr2);

			// Act
			auto isSame = Word::IsWordSame(word1, word2);

			// Assert
			Assert::IsTrue(isSame);
		}

		TEST_METHOD(TestWord_IsWordSame_False)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr1 = "WordTest";
			string wStr2 = "WordTess";
			auto word1 = Word(rep, wStr1);
			auto word2 = Word(rep, wStr2);

			// Act
			auto isSame = Word::IsWordSame(word1, word2);

			// Assert
			Assert::IsFalse(isSame);
		}

		TEST_METHOD(TestWord_IsEqual_True)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr1 = "WordTest";
			string wStr2 = "WordTest";
			auto word1 = Word(rep, wStr1);
			auto word2 = Word(rep, wStr2);

			// Act
			auto isSame = word1 == word2;

			// Assert
			Assert::IsTrue(isSame);
		}

		TEST_METHOD(TestWord_IsWorEqual_False)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr1 = "WordTest";
			string wStr2 = "wORDtEST";
			auto word1 = Word(rep, wStr1);
			auto word2 = Word(rep, wStr2);

			// Act
			auto isSame = word1 != word2;

			// Assert
			Assert::IsTrue(isSame);
		}

		TEST_METHOD(TestWord_IsWordAnagram_YesAnagram)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr1 = "WordTest";
			string wStr2 = "dTtWeosr";
			auto word1 = Word(rep, wStr1);
			auto word2 = Word(rep, wStr2);
			auto expected = Word::YesAnagram;

			// Act
			Word::WordAnagram anagram = Word::IsWordAnagram(word1, word2);

			// Assert
			Assert::AreEqual((int)expected, (int)anagram);
		}

		TEST_METHOD(TestWord_IsWordAnagram_SameWord)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr1 = "WordTest";
			string wStr2 = "wORDtEST";
			auto word1 = Word(rep, wStr1);
			auto word2 = Word(rep, wStr2);
			auto expected = Word::SameWord;

			// Act
			Word::WordAnagram anagram = Word::IsWordAnagram(word1, word2);

			// Assert
			Assert::AreEqual((int)expected, (int)anagram);
		}

		TEST_METHOD(TestWord_IsWordAnagram_NotAnagram)
		{
			// Arrange
			LetterRepresentation rep;
			string wStr1 = "WordTest";
			string wStr2 = "WordTess";
			auto word1 = Word(rep, wStr1);
			auto word2 = Word(rep, wStr2);
			auto expected = Word::NotAnagram;

			// Act
			Word::WordAnagram anagram = Word::IsWordAnagram(word1, word2);

			// Assert
			Assert::AreEqual((int)expected, (int)anagram);
		}

		TEST_METHOD(TestWord_IsWordAnagram_DifferentWords_SameRepresentation)
		{
			// Arrange

			map<char, long long> rep;
			for (auto i = 0; i < 26; ++i)
			{
				rep.insert(pair<char, long long>((char)((int)('a' + i)), i));
				rep.insert(pair<char, long long>((char)((int)('A' + i)), i));
			}
			LetterRepresentation letterRep(rep);
			string wStr1 = "Adefgh";
			string wStr2 = "Bcefgh";
			auto word1 = Word(rep, wStr1);
			auto word2 = Word(rep, wStr2);
			auto expected = Word::NotAnagram;

			// Act
			Word::WordAnagram anagram = Word::IsWordAnagram(word1, word2);

			// Assert
			Assert::AreEqual(word1.GetWordRepresentation(), word2.GetWordRepresentation());
			Assert::AreEqual((int)expected, (int)anagram);
		}
	};
}
