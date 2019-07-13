using System;
using System.Collections.Generic;
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

		public bool Equals(Word other) => WordValue == other.WordValue;

		public override int GetHashCode() => WordValue.GetHashCode();

		#region AnagramHelper

		public static string SortWord(ref Word word)
		{
			if (word.KeySet) return word.WordKey;

			word.WordKey = new string(word.WordValue.OrderBy(c => Char.ToUpper(c)).ToArray());
			word.KeySet = true;
			return word.WordKey;
		}

		public static bool IsWordSame(Word word1, Word word2) => string.Compare(word1.WordValue, word2.WordValue, StringComparison.CurrentCultureIgnoreCase) == 0;

		/// <summary>
		/// Is Word an Anagram
		/// </summary>
		/// <param name="word1"></param>
		/// <param name="word2"></param>
		/// <returns></returns>
		public static WordAnagram IsWordAnagram(ref Word word1, ref Word word2)
		{
			if (IsWordSame(word1, word2)) return WordAnagram.SameWord;
			if (word1.WordValue.Length != word2.WordValue.Length) return WordAnagram.NotAnagram;

			SortWord(ref word2);
			SortWord(ref word1);
			if (string.Compare(word1.WordKey, word2.WordKey, StringComparison.CurrentCultureIgnoreCase) == 0) return WordAnagram.YesAnagram;

			return WordAnagram.NotAnagram;
		}

		#endregion
	}
}
