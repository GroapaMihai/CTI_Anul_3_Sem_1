
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class GIC {
    private Terminals terminals;
    private NonTerminals nonTerminals;
    private Alphabet alphabet;
    private ProductionRules pr;
    private char startSymbol;
    private HashMap<Character, Boolean> uselessNonTerminals;
    private HashMap<Character, Boolean> nonTerminalHas_e;
    
    public GIC() {
        uselessNonTerminals = new HashMap<> ();
        nonTerminalHas_e = new HashMap<> ();
    }
    
    public void setTerminals(Terminals terminals) {
        this.terminals = terminals;
    }
    
    public void setNonTerminals(NonTerminals nonTerminals) {
        this.nonTerminals = nonTerminals;
    }
    
    public void setAlphabet(Alphabet alphabet) {
        this.alphabet = alphabet;
    }
    
    public void setProductionRules(ProductionRules pr) {
        this.pr = pr;
    }
    
    public void setStartSymbol(char startSymbol) {
        this.startSymbol = startSymbol;
    }

    public boolean isNonTerminal(char ch) {
        return Character.isUpperCase(ch);
    }
    
    public void initializeUselessNonTerminals() {
        int i;
        char ch;

        for(i = 0; i < nonTerminals.getCardinal(); i++) {
            ch = nonTerminals.getSymbol(i);
            uselessNonTerminals.put(ch, true);
        }
    }
    
    public void initializeHas_e() {
        int i;
        char ch;

        for(i = 0; i < nonTerminals.getCardinal(); i++) {
            ch = nonTerminals.getSymbol(i);
            nonTerminalHas_e.put(ch, false);
        }
    }
        
    // I. Alfabetul este inclus in multimea de terminali
    // intoarce true daca un simbol din alfabet nu se afla in terminals
    public boolean alphabetSemanticError() {
        int i;
        char ch;

        for(i = 0; i < alphabet.getCardinal(); i++) {
            ch = alphabet.getSymbol(i);

            if(!terminals.contains(ch))
                return true;
        }

        return false;
    }

    // II. Toti terminalii sunt in alfabet
    // intoarce true daca un simbol din terminals nu se afla in alfabet
    public boolean terminalsSemanticError() {
        int i;
        char ch;

        for(i = 0; i < terminals.getCardinal(); i++) {
            ch = terminals.getSymbol(i);

            if(!alphabet.contains(ch))
                return true;
        }

        return false;
    }
    
    // III. Simbolul de start se afla in multimea nonTerminalilor
    // intoarce true daca startSymbol nu se regaseste in nonTerminals
    public boolean startSymbolSemanticError() {
        return !nonTerminals.contains(startSymbol);
    }
    
    // IV. Partea din stanga a unei reguli se afla in multimea terminalilor
    // intoarce true daca un neterminal nu se afla in nonTerminals
    public boolean prLeftSideSemanticError() {
        int i;
        char nonTerminal;

        for(i = 0; i < pr.getCardinal(); i++) {
            nonTerminal = pr.getNonTerminal(i);

            if(!nonTerminals.contains(nonTerminal))
                return true;
        }

        return false;
    }
    
    // V. Partea din dreapta a unei reguli se afla in multimea (non)terminalilor
    public boolean prRightSideSemanticError() {
        int i, j;
        char ch;
        String replacement;

        for(i = 0; i < pr.getCardinal(); i++) {
            replacement = pr.getReplacement(i);

            for(j = 0; j < replacement.length(); j++) {
                ch = replacement.charAt(j);

                if(ch == 'e') {
                } else if(isNonTerminal(ch)) {
                    if(!nonTerminals.contains(ch))
                        return true;
                } else if(!terminals.contains(ch))
                    return true;
            }
        }

        return false;
    }
    
    public boolean hasSemanticError() {
        return (alphabetSemanticError() || terminalsSemanticError() || 
            startSymbolSemanticError() || prLeftSideSemanticError() || 
            prRightSideSemanticError());
    }
    
    public boolean isReplacementTerminal(String replacement) {
        int i;
        char ch;

        for(i = 0; i < replacement.length(); i++) {
            ch = replacement.charAt(i);

            if(!(ch == 'e' || terminals.contains(ch) || !uselessNonTerminals.get(ch)))
                return false;
        }

        return true;
    }
        
    public boolean replacementGenerates_e(String replacement) {
        int i;
        char ch;

        for(i = 0; i < replacement.length(); i++) {
            ch = replacement.charAt(i);

            if(!(ch == 'e' || (isNonTerminal(ch) && nonTerminalHas_e.get(ch))))
                return false;
        }

        return true;
    }
        
    public void findUselessNonTerminals() {
        boolean changed = true;
        int i, len = pr.getCardinal();
        char nonTerminal;
        String replacement;

        while(changed) {
            changed = false;

            // parcurg fiecare regula de productie cu nonterminal !useless
            for(i = 0; i < len; i++) {
                nonTerminal = pr.getNonTerminal(i);

                // pentru regula !useless, parcurg partea de replacement
                // si verific daca e formata doar din terminali/neterminali useless
                if(uselessNonTerminals.get(nonTerminal)) {
                    replacement = pr.getReplacement(i);

                    // am gasit o regula care duce la un sir terminal
                    if(isReplacementTerminal(replacement)) {
                        changed = true;
                        uselessNonTerminals.put(nonTerminal, false);
                    }
                }
            }
        }
    }
    
    @SuppressWarnings("unchecked")
    public ArrayList<Character> getUselessNonTerminals() {
        ArrayList<Character> result = new ArrayList<> ();
        
        Set<?> set = uselessNonTerminals.entrySet();
        Iterator<?> iterator = set.iterator();

        while(iterator.hasNext()) {
            Map.Entry<Character, Boolean> mentry;
            mentry = (Map.Entry<Character, Boolean>)iterator.next();
            
            if(mentry.getValue())
                result.add(mentry.getKey());
        }
        
        Collections.sort(result);
        
        return result;
    }
    
    public void nonTerminalHas_e() {
        boolean changed = true;
        int i, len = pr.getCardinal();
        char nonTerminal;
        String replacement;

        while(changed) {
            changed = false;

            // parcurg fiecare regula de productie cu nonterminal !useless
            // si despre care nu stiu inca ca poate genera sirul vid
            for(i = 0; i < len; i++) {
                nonTerminal = pr.getNonTerminal(i);

                // parcurg partea de replacement si verific ca contine 
                // doar e si nonTerminali marcati
                if(!uselessNonTerminals.get(nonTerminal) && !nonTerminalHas_e.get(nonTerminal)) {
                    replacement = pr.getReplacement(i);

                    // partea dreapta genereaza 'e'
                    if(replacementGenerates_e(replacement)) {
                        changed = true;
                        nonTerminalHas_e.put(nonTerminal, true);
                    }
                }
            }
        }
    }
        
    public boolean isVoid() {
    	return uselessNonTerminals.get(startSymbol);
    }
    
    public boolean has_e() {
    	return nonTerminalHas_e.get(startSymbol);
    }
}
