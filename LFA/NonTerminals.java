
import java.util.ArrayList;

public class NonTerminals {
    private ArrayList<Character> symbols;
    
    public NonTerminals() {
       symbols = new ArrayList<> ();
    }
   
    public void addSymbol(char symbol) {
        symbols.add(symbol);
    }
    
    public int getCardinal() {
        return symbols.size();
    }

    public boolean isEmpty() {
        return symbols.isEmpty();
    }

    public char getSymbol(int i) {
        return symbols.get(i);
    }

    public boolean contains(char c) {
        if(isEmpty())
            return false;

        for(char ch : symbols)
            if(c == ch)
                return true;

        return false;
    }

    @Override
    public String toString() {
        if(isEmpty())
            return "[]";

        String output = "[";

        for(char ch : symbols)
            output += ch + " ";

        return output.trim() + "]";
    }
}
