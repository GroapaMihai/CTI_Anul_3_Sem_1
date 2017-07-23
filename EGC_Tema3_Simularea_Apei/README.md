	Groapa Mihai 334CA
	
						Tema3 - Simularea Apei
						
						
		Utilizare aplicatie
	
	- tastele W, A, S, D, Q, E asigura miscarea camerei (click dreapta apasat)
	precum si deplasarea sursei luminoase.
	- sagetile permit miscarea sferei din care se lanseaza picaturi.
	- tasta space determina caderea unei picaturi.
	- tastele 1 si 2 modifica unghiul de cut-off.
	- tasta F permite randarea obiectelor astfel incat sa fie desenate doar liniile
	din care sunt formate.
	- tasta G duce la aparitia valurilor Gerstner.
	- tastele NUM_PAD_2 si NUM_PAD_8 fac posibil efectul de slow-motion respectiv
	fast-forward.
	
		Creare Plasa Poligonala
	
	- Am creat o plasa formata din patrate mici, cu o diagonala trasata fiecare.
	Plasa poate fi creata stabilind numarul de patrate de pe linii si coloane,
	precum si dimensiunile acestora. Totul este programatic, am folosit VAO, VBO etc.
	Cu toate acestea, plasa mea nu este randata de Functia RenderSimpleMesh (care
	permite selectia culorii obiectelor), desi RenderMesh o deseneaza, astfel incat
	pentru a putea realiza tema am folosit un grid obj.
	
		Sfera controlata din taste si lansarea de picaturi cu bouncing effect
	
	- Am sfera controlata din taste, dar nu am implementat bouncing efect, deoarece
	nu am putut constrange programul astfel incat sa genereze o singura unda.
	In momentul in care picatura atinge suprafata grid-ului, se formeaza instant unde
	circulare pana la marginile plasei.
	
		Calculul varfurilor din plasa poligonala deformata
	
	- Am calculat in VertexShader coordonatele varfurilor vecine vertex-ului curent,
	scazand/adunand 1 la coordonatele x si z ale celui din urma. Coordonata y a 
	fiecarui vertex am calculato folosind formula prezentata in cerinta : 
		V.y += A * (1 + sin(w * scalarProd + time * phi));	<= pentru unde circulare
	si urmatoarea formula pentru unde gerstner:
		V.y += Q * A * (cos(scalarProd * w + time * phi) + cos(scalarProd2 * w + time * phi));
	Mentionez ca am trimis catre VertexShader vectori pentru faze, amplitudini si coordonatele
	x si z ale centrelor, pentru a putea face compunerea undelor simultane.
	Compunerea se face doar pentru unde circulare si presupune "acumularea" valorii y pe care
	o genereaza fiecare unda asupra vertex-ului intr-o variabila suma.
	
		Calculul normalelor varfurilor in plasa deformata
	
	- Calculul normalei per triunghi l-am realizat prin produs vectorial intre doua laturi ale
	triunghiului (folosind cross) si la final am facut media intre cele 4 normale, pentru fiecare
	componenta (x, y si z) si am atribuit-o ca normala a vertex-ului curent.
	
		Atenuarea undelor in timp
		
	- Am stabilit un timp dupa care undele generate de o picatura dispar (20 de secunde). Am calculat
	apoi pasul cu care trebuie redusa amplitudinea la fiecare frame, astfel incat dupa 20 de secunda
	sa ajunga 0 si am redus-o cu acest pas.
	
		Efect de slow-motion (sau fast-forward) fara sacadare
	
	- Cat timp apas una din cele 2 taste NUM_PAD enumerate mai sus, acumulez intr-o variabila
	extraSpeed care poate fi pozitiv (produce efect de fast-forward) si negativ (efect invers).
	Atunci cand tasta nu mai este apasata - "released", adaug extraSpeed-ul la viteza de deplasarea
	a undelor (in acest fel elimin efectul de sacadare).
	
		Iluminarea folosind modelul de shading Phong
		
	- Preluat din laborator. Singurul lucru de mentionat ar fi ca in VertexShader verific daca
	punctul curent se afla in afara intervalului [-1, 1] ca inaltime, astfel incat sa nu deformez 
	soarele si picaturile.
	
		Camera FPS functionala
		
	- Preluata din laboratorul 5.
	
	