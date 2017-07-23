%%

%class lexer
%int
%line
%column
%unicode

LineTerminator = \r|\n|\r\n
spaces = {LineTerminator} | [ \t\f]

upper = [A-Z]
digit = [0-9]
lower = [a-d]|[f-z]
other = "-"|"="|"["|"]"|";"|"\\"|"."|"/"|"~"|"!"|"@"|"#"|"$"|"%"|"^"|"&"|"*"|"_"|"+"|":"|"|"|"<"|">"|"?"|"'"|"`"|"\""
nonTerminal = {upper}
terminal = {digit} | {lower} | {other}
replacement = e | ({terminal} | {nonTerminal})+

%{
    TerminalsAndNonTerminals v = new TerminalsAndNonTerminals();
    Alphabet alphabet = new Alphabet();
    ProductionRules prodRules = new ProductionRules();
    char start;
    char ruleNonTerminal;
    char character;
    boolean syntacticWrong = false;

    TerminalsAndNonTerminals getTerminalsAndNonTerminals() 
    {
    	return v;
    }

   	Alphabet getAlphabet() 
   	{
   		return alphabet;
   	}

   	ProductionRules getProductionRules() 
   	{
   		return prodRules;
   	}

    char getStartSymbol() 
    {
    	return start;
    }

    boolean isSyntacticWrong() 
    {
      return syntacticWrong;
    }
%}

%state S1 S2 S3 S4 S5 S6 S7 S8 S9 S10 S11 S12 S13 S14 S15 S16 S17 S18 S19 S20 Error_state

%%

{spaces} {}

<YYINITIAL> 
{
    "(" 
    {
    	yybegin(S1);
    }

    .
    {
	    yybegin(Error_state);
    }
}

<S1> 
{
    "{" 
    {
    	yybegin(S2);
    }
    
    .
    {
        yybegin(Error_state);
    } 
}

<S3> 
{
    "}" 
    {
    	yybegin(S4);
    }

    "," 
    {
   		yybegin(S2);
    }
    
    .
    {
        yybegin(Error_state);
    }
}

<S2> 
{
    {nonTerminal} 
    {
	    yybegin(S3);
	    character = yytext().charAt(0);
	    v.addNonTerminal(character);
    }

    {terminal} 
    {
	    yybegin(S3);
	    character = yytext().charAt(0);
	    v.addTerminal(character);
    }
    
    .
    {
        yybegin(Error_state);
    }
}

<S4> 
{
    "," 
    {
    	yybegin(S5);
    }
    
    .
    {
        yybegin(Error_state);
    }  
}

<S5> 
{
    "{" 
    {
    	yybegin(S6);
    }
    
    .
    {
        yybegin(Error_state);
    }
}

<S6> 
{
    {terminal} 
    {
    	character = yytext().charAt(0);
   		alphabet.addCharacter(character);
   		yybegin(S8);
    }

    "}" 
    {
    	yybegin(S9);
	}
 
    .
    {
        yybegin(Error_state);
    }
}


<S8> 
{
    "}" 
    {
    	yybegin(S9);
    }

    "," 
    {
    	yybegin(S7);
    }
    
    .
    {
        yybegin(Error_state);
    }
}

<S7> 
{
    {terminal} 
    {
    	character = yytext().charAt(0);
   		alphabet.addCharacter(character);
   		yybegin(S8);
    }
 
    .
    {
        yybegin(Error_state);
    }
}

<S9> 
{
    "," 
    {
    	yybegin(S10);
	}
    
    .
    {
        yybegin(Error_state);
    }
}

<S10> 
{
    "{" 
    {
    	yybegin(S11);
	}
    
    .
    {
        yybegin(Error_state);
    }
}

<S12> 
{
    "(" 
    {
    	yybegin(S14);
    } 
    
    .
    {
        yybegin(Error_state);
    }
}

<S13> 
{
    "}" 
    {
    	yybegin(S18);
    } 

    "," 
    {
    	yybegin(S12);
    }
    
    .
    {
        yybegin(Error_state);
    }    
}


<S11> 
{
    "(" 
    {
    	yybegin(S14);
    }

    "}" 
    {
    	yybegin(S18);
    }
    
    .
    {
        yybegin(Error_state);
    }
}

<S14> 
{
    {nonTerminal} 
    {
		ruleNonTerminal = yytext().charAt(0);
	    yybegin(S15);
    }
    
    .
    {
        yybegin(Error_state);
    }
}

<S16> 
{
    {replacement} 
    {
		prodRules.addRule(new Rule(ruleNonTerminal, yytext())); 
	    yybegin(S17);
    }
    
    .
    {
        yybegin(Error_state);
    }
}

<S15> 
{
    "," 
    {
    	yybegin(S16);
	}
    
    .
    {
        yybegin(Error_state);
    }
}

<S17> 
{
    ")"
    {
    	yybegin(S13);
    }
    
    .
    {
        yybegin(Error_state);
    }
}

<S18> 
{
    "," 
    {
    	yybegin(S19);
    }
    
    .
    {
        yybegin(Error_state);
    }
}

<S19> 
{
    {nonTerminal} 
    {
	    start = yytext().charAt(0);
	    yybegin(S20);
    }
    
    .
    {
        yybegin(Error_state);
    }
}

<S20> 
{
    ")" {}
    
    .
    {
        yybegin(Error_state);
    }	
}

<Error_state>.
{
    syntacticWrong = true;  
    return 0;
}