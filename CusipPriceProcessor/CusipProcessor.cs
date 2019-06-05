using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using Utils;

namespace CusipPriceProcessor
{
	public class CusipProcessor
	{
		private readonly StreamReader _feedStream;
		private int _currentLineCount = 0;

		public CusipProcessor(StreamReader feedStream)
		{
			_feedStream = feedStream;
		}

		/// <summary>
		/// This method will be used for the first line of the feed file to be read which is expected to be a cusip
		/// </summary>
		/// <returns></returns>
		public string ReadCusip()
		{
			if (_feedStream.EndOfStream) throw new FeedException("Feed file seems to be empty", 1, string.Empty);

			// Reading asyncronously of a single line may be an overkill, it will be useful if the file is in a remote location
			// In which case we will need to provide a timeout mechanism.  Since decorating the method as async and returning a Task<string>
			// I decided that this is a half baked solution and as such we will read the file synchronously as opposed to the decoration and
			// The read as follows:
			//		var line = await _feedStream.ReadLineAsync().ConfigureAwait(false);
			var line = _feedStream.ReadLine();
			++_currentLineCount;
			var cusip = line.GetCusip();
			if (cusip == null) throw new FeedException("First line of Feed is not a cusip", _currentLineCount, line);

			return cusip;
		}

		/// <summary>
		/// At the beginning of this routine we are at the state where a Cusip was read
		/// Therefore, the next state is either a Price, EOF or an Exception.
		/// 
		/// This is a Left-to-Right parsing of the feed file, going through the file a line at a
		/// time with a single line lookahead, LL(1).
		/// </summary>
		/// <param name="cusip"></param>
		/// <returns></returns>
		public IEnumerable<CusipLatestPrice> ReadPricesForCusips(string cusip)
		{
			// This isPreviousBlank can be considered an additional state in the state machine I discussed in the
			// "Assumptions and discussion.txt" file
			var isPreviousBlank = false;

			// Loop through the cusips
			for (; ; )
			{
				if (_feedStream.EndOfStream) yield break;

				// A place holder for the fact that we encountered no price yet
				var prevPrice = decimal.MinValue;

				// Loop through prices
				for (; ; )
				{
					if (_feedStream.EndOfStream)
					{
						if (prevPrice == decimal.MinValue) throw new FeedException($"Cusip {cusip} contains no price value", _currentLineCount);
						yield return new CusipLatestPrice(cusip, prevPrice);
						break;
					}

					++_currentLineCount;

					// In the event that this statement throws an AggregateException then it will be caught by one of the calling routines
					var line = Task.Run(_feedStream.ReadLineAsync).Result;

					// It is acceptable for the last lines to be blank lines
					if (string.IsNullOrEmpty(line))
					{
						isPreviousBlank = true;
						continue;
					}
					else if (isPreviousBlank)
					{
						throw new FeedException("A blank line in the middle of the file indicates a corrupt Feed file", _currentLineCount);
					}

					var price = line.GetPrice();
					if (!price.HasValue)
					{
						// At this point we finished reading the prices for a cusip
						// If the cusip contained no prices then the feed file is corrupt
						// Since the line is not a price then it is either a Cusip or the feed file is corrupt
						var nextPrice = line.GetCusip();
						if (nextPrice == null) throw new FeedException($"Line is neither a cusip nor a price", _currentLineCount, line);
						if (prevPrice == decimal.MinValue) throw new FeedException($"Cusip {cusip} contains no price value", _currentLineCount, line);

						yield return new CusipLatestPrice(cusip, prevPrice);

						cusip = nextPrice;
						break;
					}

					prevPrice = price.Value;
				}
			}
		}

		/// <summary>
		/// Since we initalize the EventHandler there is no need to check for null when we
		/// raise the event.
		/// </summary>
		public event EventHandler<CusipPriceEventArgs> CusipPriceHandler = delegate { };

		public async Task<bool> ProcessFeedFile()
		{
			var t = await Task.Run(() => {
				var cusip = ReadCusip();
				var cusipPrices = ReadPricesForCusips(cusip);
				foreach (var clp in cusipPrices)
					Raise(new CusipPriceEventArgs(clp.Cusip, clp.Price));

				return true;
			});

			return t;
		}

		private void Raise(CusipPriceEventArgs ea) => CusipPriceHandler(this, ea);
	}
}
