
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class Grammar 
{
    private TerminalsAndNonTerminals v;
    private Alphabet sigma;
    private ProductionRules prodRules;
    private char start;

    private ArrayList<MyPair> uselessNonTerminals;
    private ArrayList<MyPair> nonTerminalDerivesE;
    private SemanticErrorDetector detector;
    
    public Grammar(TerminalsAndNonTerminals v, Alphabet sigma, ProductionRules prodRules, char start) 
    {
        this.v = v;
        this.sigma = sigma;
        this.prodRules = prodRules;
        this.start = start;

        uselessNonTerminals = new ArrayList<MyPair> ();
        nonTerminalDerivesE = new ArrayList<MyPair> ();
        detector = new SemanticErrorDetector(v, sigma, prodRules, start);
    }
    
    public int indexOf(ArrayList<MyPair> list, char nonTerminal)
    {
        for(int i = 0; i < list.size(); i++)
            if(list.get(i).getNonTerminal() == nonTerminal)
                return i;

        return -1;
    }

    public boolean isSemanticallyWrong() 
    {
        if(detector.sigmaSemErr())
            return true;

        if(detector.terminalsSemErr())
            return true;

        if(detector.startSemErr())
            return true;

        if(detector.prodRuleNonTerminalSemErr())
            return true;

        if(detector.prReplacementSemErr())
            return true;

        return false;
    }

    public boolean derivationEnds(String repl) 
    {
        int index;
        char[] charArray = repl.toCharArray();
        boolean is_e, terminalInV;

        for(int i = 0; i < charArray.length; i++) 
        {
            index = indexOf(uselessNonTerminals, charArray[i]);
            is_e = (charArray[i] == 'e');
            terminalInV = v.containsTerminal(charArray[i]);

            if(is_e == false && terminalInV == false && uselessNonTerminals.get(index).getStatus() == true)
                return false;
        }

        return true;
    }
        
    public boolean replacementDerivesE(String repl) 
    {
        int index;
        char[] charArray = repl.toCharArray();
        boolean is_e, isNonTerminal;

        for(int i = 0; i < charArray.length; i++) 
        {
            index = indexOf(nonTerminalDerivesE, charArray[i]);
            is_e = (charArray[i] == 'e');
            isNonTerminal = Character.isUpperCase(charArray[i]);

            if(is_e == false && !(isNonTerminal && nonTerminalDerivesE.get(index).getStatus() == true))
                return false;
        }

        return true;
    }
        
    public String isVoid() 
    {
        int index = indexOf(uselessNonTerminals, start);

        if(uselessNonTerminals.get(index).getStatus() == true)
            return "Yes";
        return "No";
    }
    
    public String hasE() 
    {
        boolean nextIter = true, hasE, isUseless, generatesE;
        int indexU, indexH, index;
        ArrayList<Rule> rules = prodRules.getProductionRules();
        ArrayList<Character> nonTerminals = v.getNonTerminals();
        char nonTerminal;

        for(int i = 0; i < nonTerminals.size(); i++) 
            nonTerminalDerivesE.add(new MyPair(nonTerminals.get(i), false));

        do 
        {
            nextIter = false;

            for(int i = 0; i < rules.size(); i++) 
            {
                nonTerminal = rules.get(i).getNonTerminal();
                indexU = indexOf(uselessNonTerminals, nonTerminal);
                indexH = indexOf(nonTerminalDerivesE, nonTerminal);

                hasE = (nonTerminalDerivesE.get(indexH).getStatus() == true);
                isUseless = (uselessNonTerminals.get(indexU).getStatus() == true);
                generatesE = (replacementDerivesE(rules.get(i).getReplacement()) == true);

                if(hasE == false && isUseless == false && generatesE == true) 
                {                  
                    nonTerminalDerivesE.get(indexU).changeStatus(true);
                    nextIter = true;
                }
            }
        }
        while(nextIter == true);

        index = indexOf(nonTerminalDerivesE, start);

        if(nonTerminalDerivesE.get(index).getStatus() == true)
            return "Yes";

        return "No";
    }

    public ArrayList<Character> getUseless() 
    {
        char nonTerminal;
        boolean nextIter, isUseless, ends;
        int i, index;
        ArrayList<Rule> rules = prodRules.getProductionRules();
        ArrayList<Character> nonTerminals = v.getNonTerminals();
        ArrayList<Character> useless = new ArrayList<> ();

        for(i = 0; i < nonTerminals.size(); i++) 
        {
            uselessNonTerminals.add(new MyPair(nonTerminals.get(i), true));
            useless.add(nonTerminals.get(i));
        }

        do
        {
            nextIter = false;

            for(i = 0; i < rules.size(); i++) 
            {
                nonTerminal = rules.get(i).getNonTerminal();
                index = indexOf(uselessNonTerminals, nonTerminal);
                isUseless = (uselessNonTerminals.get(index).getStatus() == true);
                ends = (derivationEnds(rules.get(i).getReplacement()) == true);

                if(isUseless && ends)
                {  
                    uselessNonTerminals.get(index).changeStatus(false);
                    nextIter = true;
                    index = useless.indexOf(nonTerminal);
                    useless.remove(index);
                }
            }
        }
        while(nextIter == true);
        
        return useless;
    }
}
