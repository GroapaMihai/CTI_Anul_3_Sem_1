
import java.util.ArrayList;

public class TerminalsAndNonTerminals
{
    private ArrayList<Character> terminals;
    private ArrayList<Character> nonTerminals;
    
    public TerminalsAndNonTerminals()
    {
       terminals = new ArrayList<Character> ();
       nonTerminals = new ArrayList<Character> ();
    }
   
    public void addTerminal(char s)
    {
        terminals.add(s);
    }
    
    public ArrayList<Character> getTerminals()
    {
    	return terminals;
    }

    public boolean containsTerminal(char s) 
    {
        for(int i = 0; i < terminals.size(); i++)
            if(terminals.get(i) == s)
                return true;

        return false;
    }

    public void addNonTerminal(char s) 
    {
        nonTerminals.add(s);
    }

    public ArrayList<Character> getNonTerminals()
    {
    	return nonTerminals;
    }

    public boolean containsNonTerminal(char s) 
    {
        for(int i = 0; i < nonTerminals.size(); i++)
            if(nonTerminals.get(i) == s)
                return true;

        return false;
    }
}
