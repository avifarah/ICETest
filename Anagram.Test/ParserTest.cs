using AnagramMain;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Linq;
using Xunit;

namespace Anagram.Test
{
	public class ParserTest
	{
		[Fact]
		public void GetAllWordsCount_Success()
		{
			// Arrange
			var text = @"Abc, abc.
bca; def- ghi'
cab"" jkl 123 mno555";
			var rep = LetterRepresentation.Inst.CreateRep();

			var expectedWords = new List<(long, Word)> {
				( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "Abc")),	//  484098195, Abc
				( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "abc")),	//  484098195, abc
				( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "bca")),	//  484098195, bca
				(1198613964L/*d*/+  900798196L/*e*/ +  641766006L/*f*/, new Word(rep, "def")),	// 2741178166, def
				(1294752809L/*g*/+ 1143038047L/*h*/ + 2080082395L/*i*/, new Word(rep, "ghi")),	// 4517873251, ghi
				( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "cab")),	//  484098195, cab
				( 599264335L/*j*/+ 2144146621L/*k*/ + 2081532791L/*l*/, new Word(rep, "jkl")),	// 4824943747, jkl
				// 123 is not a word
				// mno555 is not a word
			};
			var byteArray = Encoding.UTF8.GetBytes(text);
			using (var anagramMem = new MemoryStream(byteArray))
			using (var anagramStream = new StreamReader(anagramMem))
			{
				var parser = new Parser(anagramStream, rep);

				// Act
				var dicWords = parser.GetAllWords();

				var wordCount = 0;
				foreach (var wds in dicWords)
					wordCount += wds.Value.Count;

				// Assert
				Assert.Equal(expectedWords.Count, wordCount);
			}
		}

		[Fact]
		public void GetAllWordsCheck_Success()
		{
			// Arrange
			var text = @"Abc, abc.
bca; def- ghi'
cab"" jkl 123 mno555";
			var rep = LetterRepresentation.Inst.CreateRep();

			var expectedWords = new List<(long, Word)> {
				( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "Abc")),	//  484098195, Abc
				( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "abc")),	//  484098195, abc
				( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "bca")),	//  484098195, bca
				(1198613964L/*d*/+  900798196L/*e*/ +  641766006L/*f*/, new Word(rep, "def")),	// 2741178166, def
				(1294752809L/*g*/+ 1143038047L/*h*/ + 2080082395L/*i*/, new Word(rep, "ghi")),	// 4517873251, ghi
				( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "cab")),	//  484098195, cab
				( 599264335L/*j*/+ 2144146621L/*k*/ + 2081532791L/*l*/, new Word(rep, "jkl")),	// 4824943747, jkl
				// 123 is not a word
				// mno555 is not a word
			};
			var byteArray = Encoding.UTF8.GetBytes(text);
			using (var anagramMem = new MemoryStream(byteArray))
			using (var anagramStream = new StreamReader(anagramMem))
			{
				var parser = new Parser(anagramStream, rep);

				// Act
				var dicWords = parser.GetAllWords();

				// Assert
				foreach (var lw in dicWords)
				{
					foreach (var w in lw.Value)
					{
						var inx = expectedWords.IndexOf((w.WordRepresentation, w));
						(long rr, Word wr) = expectedWords[inx];
						Assert.Equal(wr.WordRepresentation, w.WordRepresentation);
						Assert.Equal(wr.WordValue, w.WordValue);
					}
				}
			}
		}

		[Fact]
		public void GetAllWordsAnagrams_Success()
		{
			// Arrange
			var text = @"Abc, abc.
bca; def- ghi'
cab"" jkl 123 mno555";
			var rep = LetterRepresentation.Inst.CreateRep();
			var expectedanagramCount484098195 = 4;

			//var expectedWords = new List<(long, Word)> {
			//	( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "Abc")),	//  484098195, Abc	// Anagram count = 1
			//	( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "abc")),	//  484098195, abc	// Anagram count = 2
			//	( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "bca")),	//  484098195, bca	// Anagram count = 3
			//	(1198613964L/*d*/+  900798196L/*e*/ +  641766006L/*f*/, new Word(rep, "def")),	// 2741178166, def	// Single, no anagram in collection
			//	(1294752809L/*g*/+ 1143038047L/*h*/ + 2080082395L/*i*/, new Word(rep, "ghi")),	// 4517873251, ghi	// Single, no anagram in collection
			//	( 207031882L/*a*/+  129113432L/*b*/ +  147952881L/*c*/, new Word(rep, "cab")),	//  484098195, cab	// Anagram count = 4
			//	( 599264335L/*j*/+ 2144146621L/*k*/ + 2081532791L/*l*/, new Word(rep, "jkl")),	// 4824943747, jkl	// Single, no anagram in collection
			//	// 123 is not a word
			//	// mno555 is not a word
			//};
			var byteArray = Encoding.UTF8.GetBytes(text);
			using (var anagramMem = new MemoryStream(byteArray))
			using (var anagramStream = new StreamReader(anagramMem))
			{
				var parser = new Parser(anagramStream, rep);

				// Act
				var dicWords = parser.GetAllWords();

				// Assert
				Assert.Equal(expectedanagramCount484098195, dicWords[484098195L].Count);
				Assert.Single(dicWords[2741178166L]);
				Assert.Single(dicWords[4517873251L]);
				Assert.Single(dicWords[4824943747L]);
			}
		}

		//
		// 	ExtractAnagrams(..)
		//
		[Fact]
		public void ExtractAnagrams_Success()
		{
			// Arrange
			// Create a dictionary of letter representation where we can easily create same numeric representation of words
			// that are not anagrams.  With our random number generated representative it will be difficult to get to same
			// numeric word representation but not anagrams.
			var dic = new Dictionary<char, long>();
			Enumerable.Range(0, 'z' - 'a' + 1).ToList().ForEach(i => { dic.Add((char)('A' + i), i); dic.Add((char)('a' + i), i); });
			var repSimple = LetterRepresentation.Inst.CreateRep(dic);

			// The representation of all these words is 20
			var text = @"adegh, degha, hgeda, gehda,
bcegh, eghbc, hgecb, ghebc,
adffh, dffha, ffhad, fhadf
ADEGH DEGHA HGEDA GEHDA ";

			var word10 = new Word(repSimple, "adegh");		// Anagram 0, count 1
			var word11 = new Word(repSimple, "degha");      // Anagram 0, count 2
			var word12 = new Word(repSimple, "hgeda");      // Anagram 0, count 3
			var word13 = new Word(repSimple, "gehda");      // Anagram 0, count 4
			var word14 = new Word(repSimple, "ADEGH");		// Same word
			var word15 = new Word(repSimple, "DEGHA");		// Same word
			var word16 = new Word(repSimple, "HGEDA");      // Same word
			var word17 = new Word(repSimple, "GEHDA");      // Same word

			var word20 = new Word(repSimple, "bcegh");      // Anagram 1, count 1
			var word21 = new Word(repSimple, "eghbc");      // Anagram 1, count 2
			var word22 = new Word(repSimple, "hgecb");      // Anagram 1, count 3
			var word23 = new Word(repSimple, "ghebc");      // Anagram 1, count 4

			var word30 = new Word(repSimple, "adffh");      // Anagram 3, count 1
			var word31 = new Word(repSimple, "dffha");      // Anagram 3, count 2
			var word32 = new Word(repSimple, "ffhad");      // Anagram 3, count 3
			var word33 = new Word(repSimple, "fhadf");      // Anagram 3, count 4

			var wordDic = new Dictionary<long, List<Word>> {
				{ 20, new List<Word> { word10, word11, word12, word13, word14, word15, word16, word17,
					word20, word21, word22, word23,
					word30, word31, word32, word33 }
				}
			};

			var expectedAnagram1 = new List<Word> { word10, word11, word12, word13 };
			var expectedAnagram2 = new List<Word> { word20, word21, word22, word23 };
			var expectedAnagram3 = new List<Word> { word30, word31, word32, word33 };
			var expectedAnagramGroups = 3;
			var expectedAnagramsInEachGroup = 4;

			// Act
			var byteArray = Encoding.UTF8.GetBytes(text);
			using (var anagramMem = new MemoryStream(byteArray))
			using (var anagramStream = new StreamReader(anagramMem))
			{
				var parser = new Parser(anagramStream, repSimple);

				// Act
				var anagramLists = parser.GetAnagrams();

				// Assert
				Assert.Equal(expectedAnagramGroups, anagramLists.Count);
				for (var i = 0; i < expectedAnagramGroups; ++i)
					Assert.Equal(expectedAnagramsInEachGroup, anagramLists[i].Count);
			}
		}
	}
}
