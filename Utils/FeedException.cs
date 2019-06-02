using System;

namespace Utils
{
	public class FeedException : Exception
	{
		public FeedException(string message, int lineCountOfException = -1, string lineOfException = "") : base(message)
		{
			CurrentLineCountOfException = lineCountOfException;
			LineOfException = lineOfException;
		}

		public int CurrentLineCountOfException { get; }

		public string LineOfException { get; }
	}
}
