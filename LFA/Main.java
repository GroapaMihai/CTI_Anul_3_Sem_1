import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        String command;
        BufferedReader br;
        Terminals terminals;
        NonTerminals nonTerminals;
        Alphabet alphabet;
        ProductionRules pr;
        char startSymbol;
        GIC grammar;

        if(args.length != 1) {
            System.err.println("Argument error");
            return;
        }

        command = args[0];
        boolean c1 = command.equals("--is-void");
        boolean c2 = command.equals("--has-e");
        boolean c3 = command.equals("--useless-nonterminals");

        if(!(c1 || c2 || c3)) {
            System.err.println("Argument error");
            return;
        }

        try {
            br = new BufferedReader(new FileReader("grammar"));
            Flexer scanner = new Flexer(br);
            scanner.yylex();
            
            if(scanner.hasSyntaxError()) {
                System.err.println("Syntax error");
                return;
            }
            
            terminals = scanner.getTerminals();
            nonTerminals = scanner.getNonTerminals();
            alphabet = scanner.getAlphabet();
            pr = scanner.getProductionRules();
            startSymbol = scanner.getStartSymbol();
            
            grammar = new GIC();
            grammar.setTerminals(terminals);
            grammar.setNonTerminals(nonTerminals);
            grammar.setAlphabet(alphabet);
            grammar.setProductionRules(pr);
            grammar.setStartSymbol(startSymbol);
            
            if(grammar.hasSemanticError()) {
                System.err.println("Semantic error");
                return;
            }
            
            grammar.initializeUselessNonTerminals();
            grammar.findUselessNonTerminals();
            
            if(c1) {
                if(grammar.isVoid())
                    System.out.println("Yes");
                else
                    System.out.println("No");
            }
            else if(c2) {
                grammar.initializeHas_e();
	        grammar.nonTerminalHas_e();
                
                if(grammar.has_e())
                    System.out.println("Yes");
                else
                    System.out.println("No");
            }
            else if(c3) {
                ArrayList<Character> uselessNonTerminals;
                uselessNonTerminals = grammar.getUselessNonTerminals();
                
                for(Character ch : uselessNonTerminals)
                    System.out.println(ch);
            }
            
        } catch (FileNotFoundException e) {
            System.out.println(e);
        } catch (IOException e) {
            System.out.println(e);
        }
    }
}