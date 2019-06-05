<Query Kind="Program">
  <Output>DataGrids</Output>
  <Namespace>CRNG = System.Security.Cryptography.RandomNumberGenerator</Namespace>
</Query>

void Main()
{
	var letters = Enumerable.Range(0, 26).Select(i => ((char)((int)'a' + i)));

	Console.WriteLine($"{new string(' ', 8)}private static Dictionary<char, long> LetterRep = new Dictionary<char, long> {{");
	Console.WriteLine(string.Join($",{Environment.NewLine}", letters.Select(l => {
		var rep = BetterRandom.NextInt();
		return  $"{new string(' ', 12)}{{ '{l}', {rep,10}L }},\r\n" +			// Lower case letter with a representation
				$"{new string(' ', 12)}{{ '{char.ToUpper(l)}', {rep,10}L }}";	// Upper case letter with same representation
		})));
	Console.Write($"{new string(' ', 8)}}};");
}

/// <summary>
/// See Fixing Random
/// https://ericlippert.com/2019/02/04/fixing-random-part-2/
/// </summary>
public static class BetterRandom
{
	private static readonly ThreadLocal<CRNG> crng = new ThreadLocal<CRNG>(CRNG.Create);
	private static readonly ThreadLocal<byte[]> bytes = new ThreadLocal<byte[]>(() => new byte[sizeof(int)]);

	public static int NextInt()
	{
		crng.Value.GetBytes(bytes.Value);
		return BitConverter.ToInt32(bytes.Value, 0) & int.MaxValue;
	}

	public static double NextDouble()
	{
		while (true)
		{
			long x = NextInt() & 0x001FFFFF;
			x <<= 31;
			x |= (long)NextInt();
			double n = x;
			const double d = 1L << 52;
			double q = n / d;
			if (q != 1.0)
				return q;
		}
	}
}
