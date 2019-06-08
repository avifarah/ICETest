using System;
using System.IO;

namespace AnagramMain
{
	class Program
	{
		static void Main(string[] args)
		{
			var fileName = @"Data\AnagramTest.txt";
			using (var sr = new StreamReader(fileName))
			{
				var parser = new Parser(sr);
				var anagrams = parser.GetAnagrams();
				foreach (var anagramList in anagrams)
				{
					var anagramInList = string.Join(", ", anagramList);
					Console.WriteLine(anagramInList);
				}
			}
		}
	}
}
