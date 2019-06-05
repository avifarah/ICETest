using System.Linq;
using Xunit;
using static AnagramMain.LetterRepresentation;

namespace Anagram.Test
{
	public class LetterRepresentationTest
	{
		[Fact]
		public void UpperCaseHasSameRepresentationAsLowerCase_Success()
		{
			// Arrange
			var lc = Enumerable.Range(0, 'z' - 'a' + 1).Select(i => (char)('a' + i)).ToList();
			var uc = Enumerable.Range(0, 'Z' - 'A' + 1).Select(i => (char)('A' + i)).ToList();

			// Act
			var lcRep = lc.Select(l => WordRep(l.ToString())).ToList();
			var ucRep = uc.Select(l => WordRep(l.ToString())).ToList();

			// Assert
			// Uppercase letters have equal representation to lowercase representation
			for (var i = 0; i < 'z' - 'a' + 1; ++i)
				Assert.Equal(lcRep[i], ucRep[i]);

			// No one letter representation equals to another letter representation
			foreach (var lcr in lcRep)
			{
				int countEqual = 0;
				foreach (var lcr2 in lcRep)
					if (lcr == lcr2) ++countEqual;
				Assert.Equal(1, countEqual);
			}
		}

		[Fact]
		public void MultiletterWord_Success()
		{
			// Arrange
			var word = "abcxyz";
			var expectedWordRep = 207031882L /*a*/ + 129113432L /*b*/ + 147952881L /*c*/ + 425306638L /*x*/ + 1150261808L /*y*/ + 2051875233L /*z*/;

			// Act
			var actualWordRep = WordRep(word);

			// Assert
			Assert.Equal(expectedWordRep, actualWordRep);
		}
	}
}
