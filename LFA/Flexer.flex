%%

%class Flexer
%unicode
%int
%line
%column

LineTerminator = \r|\n|\r\n
WS = {LineTerminator} | [ \t\f]

lower_case_letter = [a-d]|[f-z]
digit = [0-9]
other = "-"|"="|"["|"]"|";"|"\\"|"."|"/"|"~"|"!"|"@"|"#"|"$"|"%"|"^"|"&"|"*"|"_"|"+"|":"|"|"|"<"|">"|"?"|"'"|"`"|"\""
terminal = {lower_case_letter} | {digit} | {other}

upper_case_letter = [A-Z]
nonTerminal = {upper_case_letter}

terminal_OR_nonTerminal = {terminal} | {nonTerminal}

replacement = e | {terminal_OR_nonTerminal}+

%s V V_ELEMENT SEP_V V_TO_ALPHABET
%s ALPHABET ALPHABET_EMPTY ALPHABET_ELEMENT SEP_A A_TO_PRODUCTION_RULES
%s PRODUCTION_RULES PR_EMPTY PR_START SEP_PR_RULES PR_LEFT_SIDE SEP_PR PR_RIGHT_SIDE PR_END PR_TO_START_SYMBOL 
%s START_SYMBOL FINAL

%{
    Terminals terminals = new Terminals();
	  NonTerminals nonTerminals = new NonTerminals();
    Alphabet alphabet = new Alphabet();
    ProductionRules pr = new ProductionRules();
    char startSymbol;
    String rule;
    boolean syntaxError = false;

    Terminals getTerminals() {
    	return terminals;
    }

    NonTerminals getNonTerminals() {
    	return nonTerminals;
    }

   	Alphabet getAlphabet() {
   		return alphabet;
   	}

   	ProductionRules getProductionRules() {
   		return pr;
   	}

    char getStartSymbol() {
    	return startSymbol;
    }

    boolean hasSyntaxError() {
      return syntaxError;
    }
%}

%%

{WS} {}

<YYINITIAL> {
    "(" {yybegin(V);}
    .	  {syntaxError = true;	return 0;}
}

<V> {
    "{" {yybegin(V_ELEMENT);}
    .   {syntaxError = true;  return 0;}    
}

<V_ELEMENT> {
    {terminal} {
	    yybegin(SEP_V);
	    terminals.addSymbol(yytext().charAt(0));
    }

    {nonTerminal} {
	    yybegin(SEP_V);
	    nonTerminals.addSymbol(yytext().charAt(0));
    }

    .   {syntaxError = true;  return 0;}
}

<SEP_V> {
    "," {yybegin(V_ELEMENT);}
    "}" {yybegin(V_TO_ALPHABET);}
    .   {syntaxError = true;  return 0;}
}

<V_TO_ALPHABET> {
    "," {yybegin(ALPHABET);}
    .   {syntaxError = true;  return 0;}     
}

<ALPHABET> {
    "{" {yybegin(ALPHABET_EMPTY);}
    .   {syntaxError = true;  return 0;} 
}

<ALPHABET_EMPTY> {
    "}" {yybegin(A_TO_PRODUCTION_RULES);}

    {terminal} {
   		alphabet.addSymbol(yytext().charAt(0));
   		yybegin(SEP_A);
    }

    .   {syntaxError = true;  return 0;} 
}

<ALPHABET_ELEMENT> {
    {terminal} {
   		alphabet.addSymbol(yytext().charAt(0));
   		yybegin(SEP_A);
    }

    .   {syntaxError = true;  return 0;} 
}

<SEP_A> {
    "," {yybegin(ALPHABET_ELEMENT);}
    "}" {yybegin(A_TO_PRODUCTION_RULES);}
    .   {syntaxError = true;  return 0;} 
}

<A_TO_PRODUCTION_RULES> {
    "," {yybegin(PRODUCTION_RULES);}
    .   {syntaxError = true;  return 0;} 
}

<PRODUCTION_RULES> {
    "{" {yybegin(PR_EMPTY);}
    .   {syntaxError = true;  return 0;} 
}

<PR_EMPTY> {
    "}" {yybegin(PR_TO_START_SYMBOL);}
    "(" {yybegin(PR_LEFT_SIDE);}
    .   {syntaxError = true;  return 0;}  
}

<PR_START> {
    "(" {yybegin(PR_LEFT_SIDE);} 
	  .   {syntaxError = true;  return 0;}   
}

<SEP_PR_RULES> {
    "," {yybegin(PR_START);}
    "}" {yybegin(PR_TO_START_SYMBOL);} 
    .   {syntaxError = true;  return 0;}      
}

<PR_LEFT_SIDE> {
    {nonTerminal} {
		  rule = yytext() + " ";
	    yybegin(SEP_PR);
    }

    .   {syntaxError = true;  return 0;} 
}

<SEP_PR> {
    "," {yybegin(PR_RIGHT_SIDE);}
    .   {syntaxError = true;  return 0;} 
}

<PR_RIGHT_SIDE> {
    {replacement} {
		  rule += yytext();
		  pr.addProductionRule(rule); 
	    yybegin(PR_END);
    }

	.   {syntaxError = true;  return 0;} 
}

<PR_END> {
    ")" {yybegin(SEP_PR_RULES);}
    .   {syntaxError = true;  return 0;} 
}

<PR_TO_START_SYMBOL> {
    "," {yybegin(START_SYMBOL);}
    .   {syntaxError = true;  return 0;} 
}

<START_SYMBOL> {
    {nonTerminal} {
		  startSymbol = yytext().charAt(0);
	    yybegin(FINAL);
    }

    .   {syntaxError = true;  return 0;} 
}

<FINAL> {
    ")" {}
    .   {syntaxError = true;  return 0;} 	
}