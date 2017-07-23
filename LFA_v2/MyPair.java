
public class MyPair
{
	private char nonTerminal;
	private boolean status;

	public MyPair(char nonTerminal, boolean status)
	{
		this.nonTerminal = nonTerminal;
		this.status = status;
	}

	public char getNonTerminal()
	{
		return nonTerminal;
	}

	public boolean getStatus()
	{
		return status;
	}

	public void changeStatus(boolean status)
	{
		this.status = status;
	}
}