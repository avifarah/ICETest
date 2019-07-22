#include "pch.h"
#include "CppUnitTest.h"
#include "..\\AnagramUtils\AnagramParser.h"
#include "..\\AnagramUtils\Word.h"
#include <fstream>
#include <map>
#include <vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

namespace AnagramCppTest
{
	TEST_CLASS(AnagramCppParserTest)
	{
	public:

		TEST_METHOD(AnagramParser_GetWordsCount_Success)
		{
			// Arrange
			ifstream ifs("G:\\Dev\\ICE.Core\\Anagram.Cpp.Test\\Document1.txt");
			AnagramParser parser(ifs);
			LetterRepresentation rep;
			vector<pair<long long, Word>> expectedWords = {
				pair<long long, Word>( (long long)207031882L/*a*/ +  (long long)129113432L/*b*/ +  (long long)147952881L/*c*/, Word(rep, "Abc")),	//  484098195, Abc
				pair<long long, Word>( (long long)207031882L/*a*/ +  (long long)129113432L/*b*/ +  (long long)147952881L/*c*/, Word(rep, "abc")),	//  484098195, abc
				pair<long long, Word>( (long long)207031882L/*a*/ +  (long long)129113432L/*b*/ +  (long long)147952881L/*c*/, Word(rep, "bca")),	//  484098195, bca
				pair<long long, Word>((long long)1198613964L/*d*/ +  (long long)900798196L/*e*/ +  (long long)641766006L/*f*/, Word(rep, "def")),	// 2741178166, def
				pair<long long, Word>((long long)1294752809L/*g*/ + (long long)1143038047L/*h*/ + (long long)2080082395L/*i*/, Word(rep, "ghi")),	// 4517873251, ghi
				pair<long long, Word>( (long long)207031882L/*a*/ +  (long long)129113432L/*b*/ +  (long long)147952881L/*c*/, Word(rep, "cab")),	//  484098195, cab
				pair<long long, Word>( (long long)599264335L/*j*/ + (long long)2144146621L/*k*/ + (long long)2081532791L/*l*/, Word(rep, "jkl"))	// 4824943747, jkl
				// 123 is not a word
				// mno555 is not a word
			};
			int expectedWordCount = expectedWords.size();

			// Act
			auto wordMap = parser.GetAllWords();

			// Assert
			auto actualCount = 0;
			for (auto wmItem : wordMap)
				actualCount += wmItem.second.size();

			Assert::AreEqual(expectedWordCount, actualCount);
		}

		TEST_METHOD(AnagramParser_GetWordsCheck_Success)
		{
			// Arrange
			ifstream ifs("G:\\Dev\\ICE.Core\\Anagram.Cpp.Test\\Document1.txt");
			AnagramParser parser(ifs);
			LetterRepresentation rep;
			vector<pair<long long, Word>> expectedWords = {
				pair<long long, Word>( (long long)207031882L/*a*/ +  (long long)129113432L/*b*/ +  (long long)147952881L/*c*/, Word(rep, "Abc")),	//  484098195, Abc
				pair<long long, Word>( (long long)207031882L/*a*/ +  (long long)129113432L/*b*/ +  (long long)147952881L/*c*/, Word(rep, "abc")),	//  484098195, abc
				pair<long long, Word>( (long long)207031882L/*a*/ +  (long long)129113432L/*b*/ +  (long long)147952881L/*c*/, Word(rep, "bca")),	//  484098195, bca
				pair<long long, Word>((long long)1198613964L/*d*/ +  (long long)900798196L/*e*/ +  (long long)641766006L/*f*/, Word(rep, "def")),	// 2741178166, def
				pair<long long, Word>((long long)1294752809L/*g*/ + (long long)1143038047L/*h*/ + (long long)2080082395L/*i*/, Word(rep, "ghi")),	// 4517873251, ghi
				pair<long long, Word>( (long long)207031882L/*a*/ +  (long long)129113432L/*b*/ +  (long long)147952881L/*c*/, Word(rep, "cab")),	//  484098195, cab
				pair<long long, Word>( (long long)599264335L/*j*/ + (long long)2144146621L/*k*/ + (long long)2081532791L/*l*/, Word(rep, "jkl"))	// 4824943747, jkl
				// 123 is not a word
				// mno555 is not a word
			};
			int expectedWordCount = expectedWords.size();

			// Act
			auto wordMap = parser.GetAllWords();

			// Assert
			for (auto keyWrd : expectedWords)
			{
				auto found = false;
				for (auto wmIt = wordMap.begin(); wmIt != wordMap.end(); ++wmIt)
				{
					auto wrdsWsameKey = wmIt->second;
					auto it = find_if(wrdsWsameKey.begin(), wrdsWsameKey.end(), [&](auto x) { return x == keyWrd.second; });
					if (it == wrdsWsameKey.end()) continue;

					auto inx = distance(wrdsWsameKey.begin(), it);
					Assert::AreEqual(keyWrd.second.GetWordValue(), wrdsWsameKey[inx].GetWordValue());
					found = true;
					break;
				}

				Assert::IsTrue(found);
			}
		}

		TEST_METHOD(AnagramParser_GetWords_Success)
		{
			// Arrange
			ifstream ifs("G:\\Dev\\ICE.Core\\Anagram.Cpp.Test\\Document1.txt");
			AnagramParser parser(ifs);
			LetterRepresentation rep;
			auto expCnt484098195 = 4;
			auto wrds484098195 = (long long)207031882L/*a*/ + (long long)129113432L/*b*/ + (long long)147952881L/*c*/;	//  484098195, Abc
																														//  484098195, abc
																														//  484098195, bca
																														//  484098195, cab
			auto expCnt2741178166 = 1;
			auto wrds2741178166 = (long long)1198613964L/*d*/ + (long long)900798196L/*e*/ + (long long)641766006L/*f*/;	// 2741178166, def
			auto expCnt4517873251 = 1;
			auto wrds4517873251 = (long long)1294752809L/*g*/ + (long long)1143038047L/*h*/ + (long long)2080082395L/*i*/;	// 4517873251, ghi
			auto expCnt4824943747 = 1;
			auto wrds4824943747 = (long long)599264335L/*j*/ + (long long)2144146621L/*k*/ + (long long)2081532791L/*l*/;	// 4824943747, jkl

			// Act
			auto wordMap = parser.GetAllWords();

			// Assert
			Assert::AreEqual(expCnt484098195,  (int)wordMap[ wrds484098195].size());
			Assert::AreEqual(expCnt2741178166, (int)wordMap[wrds2741178166].size());
			Assert::AreEqual(expCnt4517873251, (int)wordMap[wrds4517873251].size());
			Assert::AreEqual(expCnt4824943747, (int)wordMap[wrds4824943747].size());
		}

		TEST_METHOD(AnagramParser_Extract_Success)
		{
			// Arrange
			ifstream ifs("G:\\Dev\\ICE.Core\\Anagram.Cpp.Test\\TestSimilarAnagramRepresentationButDifferentWord.txt");
			AnagramParser parser(ifs);
			map<char, long long> rep;
			for (auto i = 0; i < 26; ++i)
			{
				rep.insert(pair<char, long long>((char)((int)('a' + i)), i));
				rep.insert(pair<char, long long>((char)((int)('A' + i)), i));
			}
			LetterRepresentation repSimple(rep);

			Word word10(repSimple, "adegh");		// Anagram 0, count 1,  0/*a*/ + 3/*d*/ + 4/*e*/ + 6/*g*/ + 7/*h*/ = 20
			Word word11(repSimple, "degha");		// Anagram 0, count 2,  3/*d*/ + 4/*e*/ + 6/*g*/ + 7/*h*/ + 0/*a*/ = 20
			Word word12(repSimple, "hgeda");		// Anagram 0, count 3,  7/*h*/ + 6/*g*/ + 4/*e*/ + 3/*d8/ + 0/*a*/ = 20
			Word word13(repSimple, "gehda");		// Anagram 0, count 4,  6/*g*/ + 4/*e*/ + 7/*h*/ + 3/*d*/ + 0/*a*/ = 20
			Word word14(repSimple, "ADEGH");		// Same word
			Word word15(repSimple, "DEGHA");		// Same word
			Word word16(repSimple, "HGEDA");		// Same word
			Word word17(repSimple, "GEHDA");		// Same word

			Word word20(repSimple, "bcegh");		// Anagram 1, count 1,  1/*b*/ + 2/*c*/ + 4/*e*/ + 6/*g*/ + 7/*h*/ = 20
			Word word21(repSimple, "eghbc");		// Anagram 1, count 2,  4/*e*/ + 6/*g*/ + 7/*h*/ + 1/*b*/ + 2/*c*/ = 20
			Word word22(repSimple, "hgecb");		// Anagram 1, count 3,	7/*h*/ + 6/*g*/ + 4/*e*/ + 2/*c*/ + 1/*b*/ = 20
			Word word23(repSimple, "ghebc");		// Anagram 1, count 4,	6/*g*/ + 7/*h*/ + 4/*e*/ + 1/*b*/ + 2/*c*/ = 20
			
			Word word30(repSimple, "adffh");		// Anagram 3, count 1,	0/*a*/ + 3/*d*/ + 5/*f*/ + 5/*f*/ + 7/*h*/ = 20
			Word word31(repSimple, "dffha");		// Anagram 3, count 2,	3/*d*/ + 5/*f*/ + 5/*f*/ + 7/*h*/ + 0/*a*/ = 20
			Word word32(repSimple, "ffhad");		// Anagram 3, count 3,	5/*f*/ + 5/*f*/ + 7/*h*/ + 0/*a*/ + 3/*d*/ = 20
			Word word33(repSimple, "fhadf");		// Anagram 3, count 4,	5/*f*/ + 7/*h*/ + 0/*a*/ + 3/*d*/ + 5/*f*/ = 20
			auto eachAnagramSubListCount = 4;

			map<long long, vector<Word>> wordDic {
				{ 20, vector<Word> { word10, word11, word12, word13, word14, word15, word16, word17,   word20, word21, word22, word23,   word30, word31, word32, word33 } }
			};

			vector<Word> expectedAnagram1 { word10, word11, word12, word13 };
			vector<Word> expectedAnagram2 { word20, word21, word22, word23 };
			vector<Word> expectedAnagram3 { word30, word31, word32, word33 };

			auto execpectedAnagramListsCount = 3;

			// Act
			auto anagramLists = parser.GetAnagrams();

			// Assert
			Assert::AreEqual(execpectedAnagramListsCount, (int)anagramLists.size());
			for (auto i = 0; i < execpectedAnagramListsCount; ++i)
				Assert::AreEqual(eachAnagramSubListCount, (int)anagramLists[i].size());
		}
	};
}
