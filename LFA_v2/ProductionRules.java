import java.util.ArrayList;

public class ProductionRules 
{
    private ArrayList<Rule> rules;

    public ProductionRules() 
    {
        rules = new ArrayList<Rule> ();
    }

    public void addRule(Rule rule) 
    {
        rules.add(rule);
    }
    
    public ArrayList<Rule> getProductionRules()
    {
    	return rules;
    }
}
