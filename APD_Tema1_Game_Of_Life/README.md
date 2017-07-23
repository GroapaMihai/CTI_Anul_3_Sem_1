
	Groapa Mihai
	Grupa : 334 CA

								Tema 1 APD
							 - Game of Life -


	1. Varianta seriala

		- folosesc 2 matrici (oldMatrix si newMatrix), alocate dinamic;
		- matricile au dimensiunile m + 2 linii si n + 2 coloane, pentru
		a putea realiza bordarea;
		- citesc caracter cu caracter din fisierul de intrare si salvez
		datele in matricea oldMatrix;

		- folosesc 2 vectori definiti astfel:
		  	- char iCoeficient[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  			- char jCoeficient[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
  		- cu ajutorul lor, pot accesa facil cei 8 vecini ai unei celule astfel:
  			oldMatrix[i + iCoeficient[k]] [j + jCoeficient[k]], k = 0...7.
  		- astfel evit sa verific "manual" cele 8 celule vecine, adica:
  		oldMatrix[i - 1][j - 1], oldMatrix[i - 1][j] etc.

  		- parcurg urmatoarele etape de nr_generatii ori:
  			- adaug cele 4 colturi pentru bordare;
  			- adaug liniile 0 si m + 1, respectiv coloanele 0 si m + 1;

  			- parcurg fiecare celula si pentru fiecare calculez numarul de
  			celule vecine in viata.
  			- in functie de numarul de vecini, actualizez starea celulei:
  				1. mai putin de 2 vecini ALIVE => DEAD
           		2. 2 sau 3 vecini ALIVE => ALIVE
           		3. mai mult de 3 vecini => DEAD
           		4. DEAD are exact 3 vecini ALIVE => ALIVE

           	- Observatie : calculul se face in matricea veche, iar
           	actualizarile se aplica in matricea noua!!!
           	- copiez matricea noua in cea veche si trec la urmatoarea generatie;
        - dupa ce am parcurs numarul de generatii, afisez matricea noua;
        - la sfarsit eliberez memoria si inchid fisierele.



    2. Varianta paralelizata

    	Ideea: Calculul numarului de celule vecine in viata pentru o celula
    	oarecare este independent de alta celula => poate fi paralelizat. 
    	La fiecare generatie creez o echipa de thread-uri urmand ca fiecare
    	sa se ocupe de mai multe celule din matrice.

    	Imbunatatiri aduse:

    		1. alocarea memoriei pentru fiecare linie din cele doua matrici se
    		realizeaza in paralel;
    		2. citirea matricei din fisier o fac in paralel:
    			- creez mai multe threaduri, urmand ca acestea, in paralel sa
    			citeasca un rand de matrice din fisier;
    			- fiecare thread deschide fisierul, dupa care ii sunt asignate
    			mai multe linii spre a fi citite;
    			- partea dificila este pozitionarea in fisier la inceput de linie:
    				- citesc separat linia cu M si N (prima) si retin un pointer 
    				la pozitia actuala;
    				- stiind ca pe o linie sunt N valori separate prin N spatii
    				si fiecare linie este incheiata de un \n calculez inceputurile
    				de linie si pozitionez threadul acolo folosind "fseek".
    		3. bordarea cu linii si coloane se face paralel;
    		4. thread-urile calculeaza numarul de vecini pentru celulele care le
        sunt atribuite;
    		5. copierea matricii noi in cea veche la fiecare generatie se face
    		paralel;
    		6. eliberarea memoriei la nivel de linie este realizata de mai
    		multe thread-uri.