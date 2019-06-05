using System.Collections.Generic;

namespace AnagramMain
{
	public static class LetterRepresentation
	{
		public static long WordRep(string word, int lineCount = 0, int wordCount = 0)
		{
			long wordRep = 0L;
			foreach (var letter in word)
			{
				if (!LetterRep.ContainsKey(letter)) throw new AnagramException($"Letter {letter} is not a word letter", word, lineCount, wordCount);
				wordRep += LetterRep[letter];
			}

			return wordRep;
		}

		private static readonly Dictionary<char, long> LetterRep = new Dictionary<char, long> {
			{ 'a',  207031882L },
			{ 'A',  207031882L },
			{ 'b',  129113432L },
			{ 'B',  129113432L },
			{ 'c',  147952881L },
			{ 'C',  147952881L },
			{ 'd', 1198613964L },
			{ 'D', 1198613964L },
			{ 'e',  900798196L },
			{ 'E',  900798196L },
			{ 'f',  641766006L },
			{ 'F',  641766006L },
			{ 'g', 1294752809L },
			{ 'G', 1294752809L },
			{ 'h', 1143038047L },
			{ 'H', 1143038047L },
			{ 'i', 2080082395L },
			{ 'I', 2080082395L },
			{ 'j',  599264335L },
			{ 'J',  599264335L },
			{ 'k', 2144146621L },
			{ 'K', 2144146621L },
			{ 'l', 2081532791L },
			{ 'L', 2081532791L },
			{ 'm', 1047676367L },
			{ 'M', 1047676367L },
			{ 'n', 1230385815L },
			{ 'N', 1230385815L },
			{ 'o',  752418720L },
			{ 'O',  752418720L },
			{ 'p', 1137908481L },
			{ 'P', 1137908481L },
			{ 'q', 1638155167L },
			{ 'Q', 1638155167L },
			{ 'r', 1300586832L },
			{ 'R', 1300586832L },
			{ 's', 2106012734L },
			{ 'S', 2106012734L },
			{ 't', 1687192378L },
			{ 'T', 1687192378L },
			{ 'u',  637242014L },
			{ 'U',  637242014L },
			{ 'v', 1487765813L },
			{ 'V', 1487765813L },
			{ 'w',  755811883L },
			{ 'W',  755811883L },
			{ 'x',  425306638L },
			{ 'X',  425306638L },
			{ 'y', 1150261808L },
			{ 'Y', 1150261808L },
			{ 'z', 2051875233L },
			{ 'Z', 2051875233L }
		};
	}
}
