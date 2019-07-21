
namespace AnagramMain
{
	/// <summary>
	/// We need the interface in order to provide an alternative representation for
	/// testing.
	/// </summary>
	public interface ILetterRepresentation
	{
		long WordRep(string word, int lineCount = 0, int wordCount = 0);
	}
}
