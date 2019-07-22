using AnagramMain;
using Xunit;

namespace Anagram.Test
{
	public class AnagramExceptionTest
	{
		[Fact]
		public void TestException_NoLineCoutNoWordCount()
		{
			// Arrange
			string expectedMessage = "Test Anagram Exception";
			string expectedWord = "TestWord";
			int expectedLineCount = 0;
			int expectedWordCount = 0;

			try
			{
				// Act
				throw new AnagramException("Test Anagram Exception", "TestWord");
			}
			catch (AnagramException ex)
			{
				// Assert
				Assert.Equal(expectedMessage, ex.Message);
				Assert.Equal(expectedWord, ex.Word);
				Assert.Equal(expectedLineCount, ex.LineCount);
				Assert.Equal(expectedWordCount, ex.WordCount);
			}
		}

		[Fact]
		public void TestException_WithLineCountNoWordCount()
		{
			// Arrange
			string expectedMessage = "Test Anagram Exception";
			string expectedWord = "TestWord";
			int expectedLineCount = 123;
			int expectedWordCount = 0;

			try
			{
				// Act
				throw new AnagramException("Test Anagram Exception", "TestWord", 123);
			}
			catch (AnagramException ex)
			{
				// Assert
				Assert.Equal(expectedMessage, ex.Message);
				Assert.Equal(expectedWord, ex.Word);
				Assert.Equal(expectedLineCount, ex.LineCount);
				Assert.Equal(expectedWordCount, ex.WordCount);
			}
		}

		[Fact]
		public void TestException_WithLineCountAndWordCount()
		{
			// Arrange
			string expectedMessage = "Test Anagram Exception";
			string expectedWord = "TestWord";
			int expectedLineCount = 123;
			int expectedWordCount = 456;

			try
			{
				// Act
				throw new AnagramException("Test Anagram Exception", "TestWord", 123, 456);
			}
			catch (AnagramException ex)
			{
				// Assert
				Assert.Equal(expectedMessage, ex.Message);
				Assert.Equal(expectedWord, ex.Word);
				Assert.Equal(expectedLineCount, ex.LineCount);
				Assert.Equal(expectedWordCount, ex.WordCount);
			}
		}
	}
}
