using AnagramMain;
using Xunit;

namespace Anagram.Test
{
	public class WordTest
	{
		[Fact]
		public void Sort_Success()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word = new Word(rep, "Cba");
			var expected = "abC";

			// Act
			var actual = Word.SortWord(ref word);

			// Assert
			Assert.Equal(expected, actual);
		}

		[Fact]
		public void Equal_WordsBeforeSort_success()
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
		public void Equal_WordsBeforeSort_Failure()
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
		public void Equal_WordsAfterSort_success()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "Abcdef");
			Word.SortWord(ref word1);           // Make sure word1 is sortd
			Word.SortWord(ref word2);			// Make sure word2 is sorted

			// Act
			var isSame = word1.Equals(word2);

			// Assert
			Assert.NotNull(word1.WordKey);
			Assert.NotNull(word2.WordKey);
			Assert.True(isSame);
		}

		[Fact]
		public void Equal_WordsAfterSort_Failure()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "abcdef");
			Word.SortWord(ref word1);           // Make sure word1 is sortd
			Word.SortWord(ref word2);           // Make sure word2 is sorted

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

			// Act
			var isAnagram = Word.IsWordAnagram(ref word1, ref word2);

			// Assert
			Assert.Equal(Word.WordAnagram.YesAnagram, isAnagram);
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

			// Act
			var isAnagram = Word.IsWordAnagram(ref word1, ref word2);

			// Assert
			Assert.Equal(Word.WordAnagram.NotAnagram, isAnagram);
		}

		[Fact]
		public void IsWordAnagram_WordsAreOfDifferentLengths_Failure()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "Bcdefgh");

			// Act
			var isAnagram = Word.IsWordAnagram(ref word1, ref word2);

			// Assert
			Assert.Equal(Word.WordAnagram.NotAnagram, isAnagram);
		}

		[Fact]
		public void IsWordAnagram_WordsAreEqual_Failure()
		{
			// Arrange
			var rep = LetterRepresentation.Inst.CreateRep();
			var word1 = new Word(rep, "Abcdef");
			var word2 = new Word(rep, "ABCDEF");

			// Act
			var isAnagram = Word.IsWordAnagram(ref word1, ref word2);

			// Assert
			Assert.Equal(Word.WordAnagram.SameWord, isAnagram);
		}
	}
}
