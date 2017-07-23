import java.util.ArrayList;

public class ProductionRules {
    private ArrayList<String> rules;

    public ProductionRules() {
        rules = new ArrayList<> ();
    }

    public void addProductionRule(String rule) {
        rules.add(rule);
    }
    
    public int getCardinal() {
        return rules.size();
    }

    public boolean isEmpty() {
        return rules.isEmpty();
    }

    public char getNonTerminal(int i) {
        String rule = rules.get(i);

        return rule.charAt(0);
    }

    public String getReplacement(int i) {
        String rule = rules.get(i);

        return rule.substring(2);
    }

    @Override
    public String toString() {
        String output = "";

        if(isEmpty())
            return "[]";

        for(int i = 0; i < rules.size(); i++)
            output += "[" + getNonTerminal(i) + "->" + getReplacement(i) + "] ";

        return output.trim();
    }
}
