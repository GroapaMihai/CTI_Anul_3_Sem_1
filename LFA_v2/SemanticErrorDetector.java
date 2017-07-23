
import java.util.ArrayList;

public class SemanticErrorDetector
{
    private TerminalsAndNonTerminals v;
    private Alphabet sigma;
    private ProductionRules prodRules;
    private char start;

	public SemanticErrorDetector(TerminalsAndNonTerminals v, Alphabet sigma, ProductionRules prodRules, char start)
	{
        this.v = v;
        this.sigma = sigma;
        this.prodRules = prodRules;
        this.start = start;
	}

 	public boolean sigmaSemErr() 
    {
        ArrayList<Character> alphabetCharacters = sigma.getAlphabetCharacters();

        for(int i = 0; i < alphabetCharacters.size(); i++) 
            if(v.containsTerminal(alphabetCharacters.get(i)) == false)
                return true;

        return false;
    }

    public boolean terminalsSemErr() 
    {
        ArrayList<Character> terminals = v.getTerminals();

        for(int i = 0; i < terminals.size(); i++) 
            if(sigma.contains(terminals.get(i)) == false)
                return true;

        return false;
    }
    
    public boolean startSemErr() 
    {
        return (v.containsNonTerminal(start) == false);
    }
    
    public boolean prodRuleNonTerminalSemErr() 
    {
        ArrayList<Rule> rules = prodRules.getProductionRules();

        for(int i = 0; i < rules.size(); i++) 
            if(v.containsNonTerminal(rules.get(i).getNonTerminal()) == false)
                return true;

        return false;
    }
    
    public boolean wrongReplacement(String repl)
    {
        char[] charArray = repl.toCharArray();

        for(int i = 0; i < charArray.length; i++) 
        {
            if(charArray[i] == 'e')
                continue;
            else if(Character.isUpperCase(charArray[i])) 
            {
                if(v.containsNonTerminal(charArray[i]) == false)
                    return true;
            } 
            else if(v.containsTerminal(charArray[i]) == false)
                return true;
        }

        return false;
    }

    public boolean prReplacementSemErr() 
    {
        ArrayList<Rule> rules = prodRules.getProductionRules();

        for(int i = 0; i < rules.size(); i++) 
            if(wrongReplacement(rules.get(i).getReplacement()) == true)
                return true;

        return false;
    }
}