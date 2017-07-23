
	Groapa Mihai - 334 CA
	
	
					Geometry Wars
	
	
	
	- Se folosesc tastele W, A, S, D pentru miscarea navei.
	- Miscarea navei din taste se face continuu. Adica: atata tip cat playerul
	tine apasate doua taste (cel mult), nava se va misca in directiile respective.
	Sunt permise combinatiile (W+A, W+D, S+A, S+D). In cazul in care este apasata
	deja o anumita tasta, apasarea tastei corespunzatoare directiei opuse ar face
	nava sa se miste in noua directie. Continuitatea este asigurata de folosirea
	a 4 variabile bool care indica daca o tasta este apasata. Starea acestora se
	modifica in functia OnKeyPress() si OnKeyRelease().
	
	- Rotatia navei astfel incat sa urmareasca cursorul o fac calculand unghiul
	dintre pozitia cursorului pe ecran si coordonatele centrului navei. (Nu am
	implementat spatiul logic, lucrez la nivel de viewPort).
	- Apasarea butonului stanga al mouse-ului va determina nava sa lanseze un
	proiectil in directia indicata de mouse.
	- Apasarea butonului dreapta va lansa 4 proiectile in directii diferite (in
	forma de cruce) doar daca jucatorul a colectat o abilitate bonus numita StarGun
	si timpul de folosire al acesteia nu s-a scurs.
	
	- Am creat meshe pentru absolut toate formele geometrice folosite in tema (inclusiv cerc).
	- Toate obiectele le desenez cu centrul in origine (pentru simplitate).
	- Majoritatea claselor folosite ce desemneaza forme geormetrice extind o clasa parinte
	numita GameObject care incapsuleaza majoritatea caracteristicilor.
	
	Realzarea temei pas cu pas:
	
	- desenarea vietilor in partea dreapta sus o realizez incepand de la dreapta spre stanga(este 
	utile deoarece pot astfel adauga vieti bonus mereu la stanga primei vieti).
	- obiectele fiind create direct in origine, daca am nevoie sa le rotesc pot aplica direct
	aceasta operatie.
	- rotesc nava jucator cu unghiul calculat in functie de pozitia cursorului, o translatez
	cu centerX si centerY, si actualizez coordonatele centrului in functie de tastele de miscare
	atata timp cat jocul este in desfasurare.
	- folosesc o variabila in care retin la ce moment de timp a fost generat ultimul inamic.
	- daca e cazul sa generez unul nou, generez numere aleatorii de care ma folosesc pentru a-i
	atribui o culoare (galben sau albastru), o viteza (am un vector ale carui elemente sunt valori
	posibile pentru viteza inamicilor), si o pozitie pe cercul virtual (de raza egala cu
	semi-diagonala ecranului) pe care o obtin generand un unghi random.
	- retin inamicii existenti intr-un vector. Parcurg toti inamicii, ii rotesc astfel incat sa fie
	cu fata spre nava jucator, ii translatez la pozitia lor actuala.
	- in cazul in care inamicul este o nava rosie, o scalez treptat la jumatate in 
	intervalul de 250ms, stiind care este durata desenarii unui frame si calculand pasul cu
	care trebuie scalata la fiecare frame.
	- verific daca are loc coliziune intre inamic si nava jucator, tinand cont ca daca inamicul este
	rosu, raza de impact este mai mica.
	- detectarea coliziunii se face pe modelul sfera-sfera :
		[(xc1 - xc2)^2 + (yc1 - yc2)^2] < (r1 + r2)^2.
	- obiectele nefiind sfere, am aproximat raza ca fiind lungime/2 (de regula).
	- daca inamicul atinge jucatorul, sterg inamicul din vectorul de inamici (folosesc iterator)
	si scad o viata.
	- efectul de urmarire al navei jucator de catre inamici il realizez translatand la fiecare frame
	centrul inamicilor cu o valoare ce depinde de viteza fiecaruia si micsorand distanta dintre
	acestia si jucator.
	- dupa ce am desenat inamicii, desenez gloantele si verific daca acestea lovesc vreun inamic.
	- daca nava lovita este galbena, aplic animatia de scalare, dublez viteza, o fac rosie si retin
	momentul de timp la care am lovit-o (pentru a sti cand s-au scrus cele 250ms necesare animatiei).
	- altfel, ea dispare.
	- retin in alt vector indicii gloantelor ce au lovit inamici, pentru a le sterge la frame-ul urmator.
	- atunci cand un proiectil loveste un inamic si il distruge, daca s-a scurs un anumit interval de timp
	ales de mine, din acesta va aparea o abilitate bonus (aleasa random) care se va deplasa pe OY 
	in jos (cadere) cu scopul de a fi colectata de jucator.
	- la sfarisutl fiecarui frame, reduc intervalul de aparitie al navelor inamice cu un pas constant,
	astfel incat acestia sa apara din ce in ce mai repede odata cu avansarea in joc.
	- daca jucatorul ramane fara vieti, marchez faptul ca jocul s-a incheiat, salvez timpul scurs de la
	incputul jocului pana in acest moment (pentru a putea face animatia de colorare ecran in rosu sa
	dureze 2 secunde).
	- am o variabila redIntensity, care porneste de la valoarea 0, si din momentul in care jocul s-a
	incheiat incepe sa creasca pana la 1, cu un pas care depinde de durata unui frame, astfel incat dupa
	2 secunde, adunand la fiecare frame valoarea pasului, redIntensity sa ajunga 1.
	
	
	
	BONUS
	
	- am implementat 3 abilitati ce pot fi colectate atunci cand a fost distrus un inamic si a trecut un
	anumit interval de timp:
	
		-> VIATA SUPLIMENTARA (reprezentata de o inima roz)
			- daca jucatorul colecteaza aceasta, ii va fi adaugata o viata in plus si inima dispare
			de pe ecran.
			- am desenat folosind vectorii de indici si vertecsi acestei meshe, cu centrul in origine.
			
		-> STAR_GUN (apasand click-dreapta pot trage in 4 directii (90 de grade) pentru o perioada de timp
		de 2.5 secunde)
			- acest bonus este marcat pe ecran de steluta cu 4 colturi (violet).
			- atunci cand jucatorul vrea sa o foloseasca, apasa click-dreapta, pe ecran o sa apara sub vieti
			o iconita stea-violet care arata ca abilitatea este in folosire.
			- cand efectul abilitatii este pe cale sa se termine (dupa secunda 2 din 2.5), iconita din dreapta
			se coloreaza in rosu, pentru a avertiza jucatorul ca timpul se scurge si exista posibilitatea ca
			o noua apasare, dupa terminarea timupului, sa conduca la folosirea unei noi abilitati similare,
			folosita involuntar (daca jucatorul are mai multe).
			
		-> SHIELD (cerc cu un punct turcoaz in centru si alte puncte orange pe margine)
			- creeaza un scut in jurul jucatorului (format din puncte orange pe margine)
			- scutul actioneaza timp de 5 secunde si impiedica navele inamice sa treaca dincolo de el.
			- scutul se activeaza automat, in momentul colectarii.
			- daca in momentul activarii scutului, vreu inamic este in interiorul sau, acesta nu poate lua
			viata jucatorului daca are loc impact intre acestia (de altfel, chiar daca jucatorul intra involuntar
			in vreun inamic, acestuia nu i se scade o viata cat timp abilitatea este activata).
			
	
	Probleme aparute
	
		- scutul a fost cel mai greu de incarcat ca mesha (am creat mai intai un punct, format din unirea mai
		multor triunhgiuri care au un varf in origine si celelalte 2 varfuri undeva pe circumferinta cercului).
		- generand aceste triunghiuri "cat mai des" si la distante egale (unghiuri) se poate obtine un punct perfect.
		- dupa ce am generat un punct, am creat scutul generand pe circumferinta unui cerc de raza data, puncte.
		- am ales sa nu generez punct din grad in grad (360 in total) pentru ca incarcam inutil procesul de desenare,
		astfel am preferat sa le fac mai "rare".
		- inca un lucru interesant pe care l-am facut a fost sa elimin gloantele si abilitatile (colectibles)
		care au depasit cu o anumita valoare marginile ecranului (daca nu as fi facut asta, vectorul de gloante ar
		fi pastrat n el toate gloantele trase, indiferent daca ele mai sunt vizibile sau nu). Totusi, probabil ca
		engine-ul este suficient de "smart" astfel incat sa nu mai randeze obiectele care nu apar in scena :)
			
			