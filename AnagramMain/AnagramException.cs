using System;
using System.Collections.Generic;
using System.Text;

namespace AnagramMain
{
	public class AnagramException : Exception
	{
		public string Word { get; }

		public int LineCount { get; }

		public int WordCount { get; }

		public AnagramException(string message, string word, int lineCount = 0, int wordCount = 0) : base(message)
		{
			Word = word;
			LineCount = lineCount;
			WordCount = wordCount;
		}
	}
}
