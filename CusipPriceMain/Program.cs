using CusipPriceProcessor;
using System;
using System.IO;
using Utils;

namespace CusipPriceMain
{
	class Program
	{
		static void Main(string[] args)
		{
			var dataFile1 = @"Data\Feed1Good.txt";
			using (var cusipPriceSr = new StreamReader(dataFile1))
			{
				try
				{
					var proc = new CusipProcessor(cusipPriceSr);
					proc.CusipPriceHandler += ProcCusipPriceHandler;
					var t = proc.ProcessFeedFile();

					// Something else can be done here

					_ = t.Result;			// Wait for the feed file to complete processesing
				}
				catch (FeedException ex)
				{
					Console.WriteLine();
					Console.WriteLine($"System threw and exception.  Problem in line in input file: {ex.CurrentLineCountOfException}");
					if (!string.IsNullOrEmpty(ex.LineOfException))
						Console.WriteLine($"Input Line of exception: \"{ex.LineOfException}\"");
					Console.WriteLine(ex.Message);
					Console.WriteLine();
				}
				catch (Exception ex)
				{
					Console.WriteLine();
					Console.WriteLine($"{ex.GetType().Name}.  {ex.Message}");
					Console.WriteLine();
				}
			}

			Console.WriteLine("Press the Enter key to exit");
			Console.ReadKey();
		}

		private static void ProcCusipPriceHandler(object sender, CusipPriceEventArgs e)
			=> Console.WriteLine($"Cusip: {e.Cusip}, price: {e.LatestPrice}");
	}
}
