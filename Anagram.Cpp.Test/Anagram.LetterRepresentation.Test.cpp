#include "pch.h"
#include "CppUnitTest.h"
#include "..\\AnagramUtils\LetterRepresentation.h"
#include <map>
#include <string>

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnagramCppTest
{
	TEST_CLASS(AnagramCppLetterRepresentationTest)
	{
	public:

		TEST_METHOD(UpperCaseLetterSameAslowerCaseLetter_Success)
		{
			// Arrange
			string lcw[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
			string ucw[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
			long long lcRep[26];
			long long ucRep[26];
			long long expectedRep[] = { 207031882L/*a*/,  129113432L/*b*/,  147952881L/*c*/, 1198613964L/*d*/, 900798196L/*e*/,
				 641766006L/*f*/, 1294752809L/*g*/, 1143038047L/*h*/, 2080082395L/*i*/,  599264335L/*j*/,
				2144146621L/*k*/, 2081532791L/*l*/, 1047676367L/*m*/, 1230385815L/*n*/,  752418720L/*o*/,
				1137908481L/*p*/, 1638155167L/*q*/, 1300586832L/*r*/, 2106012734L/*s*/, 1687192378L/*t*/,
				 637242014L/*u*/, 1487765813L/*v*/,  755811883L/*w*/,  425306638L/*x*/, 1150261808L/*y*/,
				2051875233L/*z*/
			};
			LetterRepresentation lettRep;

			// Act
			for (auto i = 0; i < 26; ++i)
			{
				lcRep[i] = lettRep.WordRep(lcw[i]);
				ucRep[i] = lettRep.WordRep(ucw[i]);
			}

			// Assert
			for (auto i = 0; i < 26; ++i)
			{
				Assert::AreEqual(lcRep[i], ucRep[i]);
				Assert::AreEqual(expectedRep[i], lcRep[i]);
			}
		}

		TEST_METHOD(UpperCaseSameAslowerCase_AltRep_Success)
		{
			// Arrange
			string lcw[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
			string ucw[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
			long long lcRep[26];
			long long ucRep[26];

			map<char, long long> rep;
			for (auto i = 0; i < 26; ++i)
			{
				rep.insert(pair<char, long long>((char)((int)('a' + i)), i));
				rep.insert(pair<char, long long>((char)((int)('A' + i)), i));
			}
			LetterRepresentation lettRep(rep);

			// Act
			for (auto i = 0; i < 26; ++i)
			{
				lcRep[i] = lettRep.WordRep(lcw[i]);
				ucRep[i] = lettRep.WordRep(ucw[i]);
			}

			// Assert
			for (auto i = 0; i < 26; ++i)
			{
				Assert::AreEqual(lcRep[i], ucRep[i]);
				Assert::AreEqual((long long)i, lcRep[i]);
			}
		}

		TEST_METHOD(WordRepresentation_Success)
		{
			// Arrange
			string word = "abcxyz";
			long long expectedWordRep = (long long)207031882L/*a*/ + (long long)129113432L/*b*/ + (long long)147952881L/*c*/ + (long long)425306638L/*x*/ +
				(long long)1150261808L + (long long)2051875233L/*z*/;
			LetterRepresentation rep;

			// Act
			auto actualWordRep = rep.WordRep(word);

			// Assert
			Assert::AreEqual(expectedWordRep, actualWordRep);
		}

		TEST_METHOD(WordRepresentation_Alt_Success)
		{
			// Arrange
			string word = "abcxyz";
			auto expectedWordRep = 0L/*a*/ + ((long long)'b' - (long long)'a')/*b*/ + ((long long)'c' - (long long)'a')/*c*/ +
				((long long)'x' - (long long)'a')/*x*/ + ((long long)'y' - (long long)'a')/*y*/ + ((long long)'z' - (long long)'a')/*z*/;

			map<char, long long> rep;
			for (auto i = 0; i < 26; ++i)
			{
				rep.insert(pair<char, long long>((char)((int)('a' + i)), i));
				rep.insert(pair<char, long long>((char)((int)('A' + i)), i));
			}
			LetterRepresentation letterRep(rep);

			// Act
			auto actualWordRep = letterRep.WordRep(word);

			// Assert
			Assert::AreEqual(expectedWordRep, actualWordRep);
		}
	};
};
