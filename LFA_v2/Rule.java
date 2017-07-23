
public class Rule
{
	private char nonTerminal;
	private String replacement;

	public Rule(char nonTerminal, String replacement)
	{
		this.nonTerminal = nonTerminal;
		this.replacement = replacement;
	}

	public char getNonTerminal()
	{
		return nonTerminal;
	}

	public String getReplacement()
	{
		return replacement;
	}
}