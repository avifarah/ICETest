using System;
using System.Linq;

namespace AnagramMain
{
	public struct Word : IEquatable<Word>
	{
		public enum WordAnagram { YesAnagram, SameWord, NotAnagram }

		/// <summary>The original value of the word</summary>
		public string WordValue { get; }

		/// <summary>A key for the word shared by all anagrams.</summary>
		public string WordKey { get; private set; }

		/// <summary>Numerical representation of the word</summary>
		public long WordRepresentation { get; }

		/// <summary>Line count where word was found</summary>
		public int LineCount { get; }

		/// <summary>Count of this word index in the current line</summary>
		public int WordCount { get; }

		private bool KeySet { get; set; }

		public Word(ILetterRepresentation rep, string word, int lineCount = 0, int wordCount = 0)
		{
			WordValue = word;
			WordKey = null;
			KeySet = false;
			WordRepresentation = rep.WordRep(word);
			LineCount = lineCount;
			WordCount = wordCount;
		}

		/// <summary>
		/// Either case sensitive equality or case insensitive equality is needed for Word copmarison.
		/// I choose case sensitive because I feel that this would be the consumer of the class' expectation.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		public bool Equals(Word other) => WordValue == other.WordValue;

		public override int GetHashCode() => WordValue.GetHashCode();

		#region AnagramHelper

		public static string GetWordKey(ref Word word)
		{
			if (word.KeySet) return word.WordKey;

			word.WordKey = new string(word.WordValue.OrderBy(c => Char.ToUpper(c)).ToArray());
			word.KeySet = true;
			return word.WordKey;
		}

		public static bool IsWordSame(Word word1, Word word2) => string.Compare(word1.WordValue, word2.WordValue, StringComparison.CurrentCultureIgnoreCase) == 0;

		/// <summary>
		/// Is Word an Anagram
		/// 
		/// <remark>
		/// Anagramic words necessarily have the same word representation
		/// Same word representation do not necesitate anagramic words.  The ultimate test of if words are
		/// an anagram is the fact that their word key are the same.
		/// </remark> 
		/// </summary>
		/// <param name="word1"></param>
		/// <param name="word2"></param>
		/// <returns></returns>
		public static WordAnagram IsWordAnagram(ref Word word1, ref Word word2)
		{
			if (IsWordSame(word1, word2)) return WordAnagram.SameWord;
			if (word1.WordValue.Length != word2.WordValue.Length) return WordAnagram.NotAnagram;
			if (word1.WordRepresentation != word2.WordRepresentation) return WordAnagram.NotAnagram;

			if (!word2.KeySet) GetWordKey(ref word2);
			if (!word1.KeySet) GetWordKey(ref word1);

			if (string.Compare(word1.WordKey, word2.WordKey, StringComparison.CurrentCultureIgnoreCase) == 0) return WordAnagram.YesAnagram;
			return WordAnagram.NotAnagram;
		}

		#endregion
	}
}
