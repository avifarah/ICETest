#pragma once

#include <string>

using namespace std;


#ifdef ANAGRAMUTILS_EXPORTS
	#define ANAGRAM_DLLEXPORT __declspec(dllexport)
	#pragma message ("__declspec(dllexport)")
#else
	#define ANAGRAM_DLLEXPORT __declspec(dllimport)
	#pragma message ("__declspec(dllimport)")
#endif

class ANAGRAM_DLLEXPORT Parser
{
private:

public:

};

/*
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
		/// a construct allowing for further processing
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
				var FirstWordList = new List<Word> { item.Value.First() };

				// Add this list to the localAnagramList
				anagramLists.Add(FirstWordList);

				var restOfWords = item.Value.Skip(1).ToArray();

				// Cycle through all words
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
*/
