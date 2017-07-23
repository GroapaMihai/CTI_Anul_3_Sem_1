import java.io.*;
import java.util.ArrayList;

public class Main 
{
    public static void main(String[] args) 
    {
        Grammar grammar;
        String request;
        BufferedReader reader;
        String fileName = "grammar";

        if(args.length != 1) 
        {
            System.err.println("Argument error");
            return;
        }

        request = args[0];

        if(!(request.equals("--is-void") || request.equals("--has-e") || request.equals("--useless-nonterminals"))) 
        {
            System.err.println("Argument error");
            return;
        }

        try {
            reader = new BufferedReader(new FileReader(fileName));
            lexer parser = new lexer(reader);
            parser.yylex();
            
            if(parser.isSyntacticWrong()) 
            {
                System.err.println("Syntax error");
                return;
            }
            
            grammar = new Grammar(parser.getTerminalsAndNonTerminals(),
            					  parser.getAlphabet(),
            					  parser.getProductionRules(),
            					  parser.getStartSymbol());
            
            if(grammar.isSemanticallyWrong()) 
            {
                System.err.println("Semantic error");
                return;
            }
            
            ArrayList<Character> uselessNonTerminals = grammar.getUseless();
            
            if(request.equals("--is-void")) 
                System.out.println(grammar.isVoid());
            else if(request.equals("--has-e")) 
                System.out.println(grammar.hasE());
            else for(int i = 0; i < uselessNonTerminals.size(); i++)
                System.out.println(uselessNonTerminals.get(i));
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}