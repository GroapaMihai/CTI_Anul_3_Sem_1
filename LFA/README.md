GROAPĂ MIHAI
CA334

	-Gramatica este reprezentata de clasa GIC ce cuprinde 5 componente, fiecare
	cu cate o clasa (mai putin simbolul de start) : terminali, neterminali(am
	ales sa separ componenta 'V' a gramaticii), alfabet, reguli si simbol de 
	start. Fiecare componenta retine intern o lista cu simbolurile continute.
	-Gramatica contine si 2 tabele asociative : <neterminal, bool> prin care
	marchez daca un neterminal este inutil/hasE. Algoritmul de constructie
	aplicat: parcurg succesiv neterminali nemarcati, verific daca partea
	dreapta are doar simboluri marcate si marchez neterminalul (Prog Dinamica).
	Starile le-am gandit astfel incat sa parseze corect gramatici bine definite
	si apoi, in fiecare stare, daca primesc un alt simbol/sir in afara celor
	stabilite, marchez ca am eroare sintactica si opresc parsarea.
	-Componenta 'V' are o stare care diferentiaza terminalii de neterminali 
	astfel incat sa ii pot adauga in lista asociata.
	-Alfabetul accepta doar simboluri terminali si are o regula suplimentara
	care permite ca acesta sa fie vid : din starea care accepta '{' trec in o
	noua stare in care pot accepta fie '}', fie terminal, altceva => eroare.
	-La regulile de productie am similar cu alfabetul, o stare care accepta
	multime vida. Regula o reprezint ca neterminal + spatiu + replacement.
	-Erorile semantice se verifica in clasa GIC.

