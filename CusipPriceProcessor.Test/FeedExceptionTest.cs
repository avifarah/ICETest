using Xunit;
using Utils;

namespace CusipPriceProcessor.Test
{
	public class FeedExceptionTest
	{
		[Fact]
		public void FeedException_MessageOnly_Success()
		{
			// Assert
			var msg = "Test message";
			var expectedMsg = msg;
			var expectedLineCountOfException = -1;
			var expectedLineOfException = string.Empty;

			// Act
			var ex = Assert.ThrowsAsync<FeedException>(() => throw new FeedException(msg)).Result;

			// Assert
			Assert.Equal(expectedMsg, ex.Message);
			Assert.Equal(expectedLineCountOfException, ex.CurrentLineCountOfException);
			Assert.Equal(expectedLineOfException, ex.LineOfException);
		}

		[Fact]
		public void FeedException_MessageAndLineCountOnly_Success()
		{
			// Assert
			var msg = "Test message";
			var expectedMsg = msg;
			var expectedLineCountOfException = 123;
			var expectedLineOfException = string.Empty;

			// Act
			var ex = Assert.ThrowsAsync<FeedException>(() => throw new FeedException(msg, 123)).Result;

			// Assert
			Assert.Equal(expectedMsg, ex.Message);
			Assert.Equal(expectedLineCountOfException, ex.CurrentLineCountOfException);
			Assert.Equal(expectedLineOfException, ex.LineOfException);
		}

		[Fact]
		public void FeedException_MessageLineCountAndLineofexception_Success()
		{
			// Assert
			var msg = "Test message";
			var expectedMsg = msg;
			var expectedLineCountOfException = 123;
			var expectedLineOfException = "Line of exception";

			// Act
			var ex = Assert.ThrowsAsync<FeedException>(() => throw new FeedException(msg, 123, "Line of exception")).Result;

			// Assert
			Assert.Equal(expectedMsg, ex.Message);
			Assert.Equal(expectedLineCountOfException, ex.CurrentLineCountOfException);
			Assert.Equal(expectedLineOfException, ex.LineOfException);
		}
	}
}
