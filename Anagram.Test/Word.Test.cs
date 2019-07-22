using AnagramMain;
using Xunit;

namespace Anagram.Test
{
	public class WordTest
	{
		[Fact]
		public void GetWordKey_Success()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word = new Word(rep, "Cba");
			var expectedKey = "abC";

			// Act
			var actualKey = Word.GetWordKey(ref word);

			// Assert
			Assert.Equal(expectedKey, actualKey);
			Assert.Equal(expectedKey, word.WordKey);
		}

		[Fact]
		public void Equal_WordsBeforeGetWordKey_success()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "Abcdef");

			// Act
			var isSame = word1.Equals(word2);

			// Assert
			Assert.True(isSame);
		}

		[Fact]
		public void Equal_WordsBeforeGetWordKey_Failure()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "abcdef");

			// Act
			var isSame = word1.Equals(word2);

			// Assert
			Assert.False(isSame);
		}

		[Fact]
		public void Equal_WordsAfterSetWordKey_success()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "Abcdef");
			Word.GetWordKey(ref word1);
			Word.GetWordKey(ref word2);

			// Act
			var isSame = word1.Equals(word2);

			// Assert
			Assert.NotNull(word1.WordKey);
			Assert.NotNull(word2.WordKey);
			Assert.True(isSame);
		}

		[Fact]
		public void Equal_WordsAfterGetWordKey_Failure()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "abcdef");
			Word.GetWordKey(ref word1);
			Word.GetWordKey(ref word2);

			// Act
			var isSame = word1.Equals(word2);

			// Assert
			Assert.NotNull(word1.WordKey);
			Assert.NotNull(word2.WordKey);
			Assert.False(isSame);
		}

		[Fact]
		public void IsWordSame_Success()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "abcdef");

			// Act
			var isSame = Word.IsWordSame(word1, word2);

			// Assert
			Assert.True(isSame);
		}

		[Fact]
		public void IsWordAnagram_Success()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Fabcde");
			var word2 = new Word(rep, "Bcdefa");
			var expectedKey1 = "abcdeF";
			var expectedKey2 = "aBcdef";
			var expectedIsAnagram = Word.WordAnagram.YesAnagram;

			// Act
			var isAnagram = Word.IsWordAnagram(ref word1, ref word2);

			// Assert
			Assert.Equal(expectedIsAnagram, isAnagram);
			Assert.Equal(expectedKey1, word1.WordKey);
			Assert.Equal(expectedKey2, word2.WordKey);
		}

		[Fact]
		public void IsWordAnagram_WordsAreOfSameLength_Failure()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "Bcdefg");
			var expectedIsAnagram = Word.WordAnagram.NotAnagram;

			// Act
			var isAnagram = Word.IsWordAnagram(ref word1, ref word2);

			// Assert
			Assert.Equal(expectedIsAnagram, isAnagram);
		}

		[Fact]
		public void IsWordAnagram_WordsAreOfDifferentLengths_Failure()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "Bcdefgh");
			var expectedIsAnagram = Word.WordAnagram.NotAnagram;

			// Act
			var isAnagram = Word.IsWordAnagram(ref word1, ref word2);

			// Assert
			Assert.Equal(expectedIsAnagram, isAnagram);
		}

		[Fact]
		public void IsWordAnagram_WordsAreEqual_Failure()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "ABCDEF");
			var expectedIsAnagram = Word.WordAnagram.SameWord;

			// Act
			var isAnagram = Word.IsWordAnagram(ref word1, ref word2);

			// Assert
			Assert.Equal(expectedIsAnagram, isAnagram);
		}
	}
}
