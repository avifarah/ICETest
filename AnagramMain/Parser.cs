using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;
using System.Linq;

namespace AnagramMain
{
	/// <summary>
	/// Lexically parse an input stream into words
	/// </summary>
	public class Parser
	{
		private readonly StreamReader _textStream;
		private readonly ILetterRepresentation _rep;

		public Parser(StreamReader stream, ILetterRepresentation rep = null)
		{
			_textStream = stream;
			_rep = rep ?? LetterRepresentation.Inst.CreateRep();
		}

		private readonly Regex _wordRe = new Regex(@"\b(?<word>[A-Za-z]+)\b");

		/// <summary>
		/// Extracts all words from a stream (document) and stuff them into
		/// a dictionary construct, keyed off the word representation, allowing
		/// for further processing.
		/// </summary>
		/// <returns></returns>
		public Dictionary<long, List<Word>> GetAllWords()
		{
			var wordDic = new Dictionary<long, List<Word>>();
			for (var lc = 1; !_textStream.EndOfStream; ++lc)
			{
				var line = _textStream.ReadLine();
				var ms = _wordRe.Matches(line);
				var wc = 0;
				foreach (Match m in ms)
				{
					++wc;
					var word = new Word(_rep, m.Groups["word"].Value, lc, wc);
					var rep = word.WordRepresentation;
					if (wordDic.ContainsKey(rep))
						wordDic[rep].Add(word);
					else
						wordDic.Add(rep, new List<Word> { word });
				}
			}

			return wordDic;
		}

		/// <summary>
		/// This method, ExtractAnagrams(..), is supposed to follow the GetAllWords().
		/// Algorithm:
		///		*	Create anagramLists a List<list<Word>>
		///		*	cycle through all the words in wordDic
		///		*		each iteration through the dictionary deals with an item having the same Anagram Key
		///				(2 words with the same anagram key does not guarantee that the 2 words are anagramatic, they
		///				may be the same or they may be non anagramatic.  However, words having different anagramatic key
		///				are necessarily not anagrams.)
		///				During each iteration we build the anagramLists as follows
		///		*			if the word is part of any of the lists in the anagramLists then we do nothing
		///					else if it is anagramit to any of the lists in the anagramLists then it is added to that list
		///					else it is the beginning of a new list
		/// </summary>
		/// <param name="wordDic"></param>
		/// <returns></returns>
		private List<List<Word>> ExtractPotentialAnagrams(Dictionary<long, List<Word>> wordDic)
		{
			var anagramLists = new List<List<Word>>();

			foreach (var item in wordDic)
			{
				// If the word is a single word for the numeric representation then continue;
				if (item.Value.Count == 1) continue;

				// In order to start the Anagram list take out the first word and match the rest of the words to it
				var firstWordList = new List<Word> { item.Value.First() };

				// Add this list to the localAnagramList
				anagramLists.Add(firstWordList);

				var restOfWords = item.Value.Skip(1).ToArray();

				// Cycle through all words in restOfWords
				for (var wc = 0; wc < restOfWords.Length; ++wc)
				{
					// Cycle through all list of potential anagrams
					var wordCounted = false;
					for (int alc = 0; alc < anagramLists.Count; ++alc)
					{
						var f = anagramLists[alc].First();
						var isAnagram = Word.IsWordAnagram(ref f, ref restOfWords[wc]);
						if (isAnagram == Word.WordAnagram.SameWord)
						{
							wordCounted = true;
							break;
						}

						if (isAnagram == Word.WordAnagram.YesAnagram)
						{
							// First make sure that it is not the same as any word in the list
							var rc = anagramLists[alc].Any(w => string.Compare(w.WordValue, restOfWords[wc].WordValue, StringComparison.CurrentCultureIgnoreCase) == 0);
							if (!rc)
								anagramLists[alc].Add(restOfWords[wc]);
							wordCounted = true;
							break;
						}
					}

					if (!wordCounted)
					{
						// No List found and word is not used add a new list
						anagramLists.Add(new List<Word> { restOfWords[wc] });
					}
				}
			}

			return anagramLists;
		}

		private List<List<string>> ExtractAnagrams(List<List<Word>> anagramLists)
		{
			var trueAnagrams = new List<List<string>>();
			foreach (var anList in anagramLists)
			{
				if (anList.Count == 1) continue;
				trueAnagrams.Add(anList.Select(a => a.WordValue).ToList());
			}

			return trueAnagrams;
		}

		/// <summary>
		/// Since ExtractAnagrams(..) does not fucntion on its own it must follow 
		/// </summary>
		/// <returns></returns>
		public List<List<string>> GetAnagrams()
		{
			var dicWords = GetAllWords();
			var anagramLists = ExtractPotentialAnagrams(dicWords);
			var trueLists = ExtractAnagrams(anagramLists);
			return trueLists;
		}
	}
}
