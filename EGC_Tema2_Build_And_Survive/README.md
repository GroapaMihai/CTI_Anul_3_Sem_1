
		Groapa Mihai 334 CA
	
	
	
	AM IMPLEMENTAT BONUS!!!
	
	
	* Utilizare aplicatie
		- tastele W, A, S, D pentru miscare jucator
		- mouse : click dreapta apasat + miscare determina rotatia jucatorulu in directia
		respectiva, click stanga pentru a lansa proiectile
		- tastele 1, 2 si 3 pentru alegerea celor 3 arme disponibile
		- tasta b pentru a intra/iesi in modul "tower defence" + apasarea butonul stanga mouse
		pentru a plasa un turn in pozitia aleasa
		
	* Detalii de implementare
		- Am pornit implementarea de la laboratorul de camere - 5
		- Clasa "BuildAndSurvive" realizeaza coordonarea intregului joc
		- In afara acesteia, folosesc alte clase care reprezinta elemente ale jocului precum:
		enemy, player, life, tower, projectile etc
		
		Ideea de rezolvare
		
		MESHE
		- am incarcat de pe internet urmatoarele modele:
			- rabbit pentru jucatorul principal
			- dog pentru inamici
			- tower pentru turnuri (acelasi model ca cel din demo)
			- spehere si box (din laborator)
		
		LABIRINT
		- am inceput prin a alege un colt al labirintului, de unde apar inamicii si pe baza
		coordonatelor sale am calculat celelalte 3 coordonate ale "Z-ului" imaginar pe care il
		parcurg inamicii
		- am adaugat obiectul "plane" in aceste colturi, pentru a vizualiza mai bine traseul inamicilor
		
		CAMERE
		- folosesc 3 camere:
			- "camera" - ramane in spatele jucatorului si se roteste odata cu acesta
			- "miniCamera" - vede scena de sus si are ca target jucatorul
			- "buildCamera" - vede scena de sus si ramane focusata pe origine (o folosesc pentru bonus)
			
		CAMERA TPS
		- pentru a mentine camera TPS in spatele jucatorului am facut astfel:
			- stiind coordonatele player-ului si distanta de la care vreau sa il filmez, calculez
			coordonate pe un cerc imaginar in jurul axei OY si misc stanga/dreapta camera pe acest cerc
			in functie de sensivitatea mouse-ului pe OX
			- setez pozitia noua a camerei si ca target pozitia jucatorului
		
		CAMERA FPS
		- folosesc aceasta camera pentru pusca
		- procedez asemanator ca la camera TPS, doar ca pozitia camerei o aleg ca fiind centrul player-ului
		+ un deplasament astfel incat sa fiu putin in fata sa si ca target aleg un punct de pe un cerc al
		carui centru il setez ca fiind camera si avand o raza (distanta de zoom) aleasa de mine
		
		PARCURGEREA LABIRINTULUI DE CATRE INAMICI
		- consider traseul format din 3 segmente : 2 paralele cu OX, si unul pe diagonala
		- pe cele 2 segmente paralele, miscarea se face incrementand valoarea coordonatei X
		a playerului la fiecare frame
		- miscarea pe diagonala o fac modificand coordonatele X si Z-ului
		- atunci cand inamicul ajunge la al 4-lea colt al labirintului, scad o viata jucatorului si
		inamicul dispare (il sterg din vectorul de inamici)
		
		ARMELE
		- se selecteaza de pe tastele 1, 2, 3
		- pistolul : damage 30
		- pusca : damage 15
		- grenada : damage 50
		- acestora li se adauga proiectilele trase de turnuri : damage 25
		
		PISTOL
		- folosesc camera TPS si lansez proiectile de marime medie in directia player-ului
		- proiectilele lansate de pistol au viteza medie de deplasare (4) si pot lansa
		un nou astfel de proiectil o data la 0.8 secunde
		
		PUSCA
		- folosesc camera FPS si lansez proiectile de marime medie
		- viteza mai mare de deplasare (6), pot lansa o data la 0.4 secunde un nou proiectil
		
		GRENADE LAUNCHER
		- camera folosita este TPS
		- marime mai mare a proiectilului, viteza mai mica (3), si timp mare de asteptare intre
		focuri : 1.6 secunde
		
		MISCARE PROIECTILE
		1. grenadele : se misca pe toate cele 3 axe, miscarea pe OX si OZ se face tinand cont de
		unghiul sub care e rotit jucatorul. Miscarea pe OY (efectul de bolta) l-am realizat aplicand
		formule invatate la fizica, in functie de acceleratia gravitationala, unghi de lansare, viteza
		initiala de lansare si timp:
			** Vy = Vy_0 - g * t
			** y = 0.5 * (Vy_0 + Vy) * t -> functioneaza perfect
			
		2. pentru restul proiectilelor : calculez noile coordonate X si Z tinand cont de unghiul
		player-ului, si de cat ar trebui sa deplasez la fiecare frame:
			** dX = cos(p->getAngle());
			** dZ = sin(p->getAngle());
			
		Pentru fiecare tip de proiectil am o distanta maxima pe care poate sa o parcurga, astfel incat,
		daca depaseste acea distanta el sa fie sters.
			
		TURNURILE
		- pentru fiecare turn calculez distanta dintre el si fiecare inamic viu si la final aleg ca tinta
		inamicul cel mai apropiat (distanta o calculez folosind formula pentru distanta dintre 2 puncte,
		tinand cont doar de coordonatele X si Z - Y ramanand constant)
		- pentru fiecare turn retin intern timpul la care a lansat ultimul proiectil si atunci cand
		a trecut o anumita perioada de timp care trebuie sa treaca intre 2 focuri, pot lansa un proiectil
		spre inamicul cel mai apropiat si actualizez timpul de lansare
		
		DETECTIA DE COLIZIUNI SI SCADERE VIATA INAMICI
		- la inceputul jocului, inamicii au viata 100, urmand sa creasca pana la 500 maxim
		- am 2 detectii de coliziuni: una intre proiectil si inamic, si alta intre player si un obiect
		mini-turnulet, ce poate fi colectat si adaugat in scena, in modul build.
		- detectia de coliziuni foloseste modelul sfera-sfera, unde pentru inamic am ales ca raza
		semidiagonala formata pe planul XOZ, pentru player am aproximat-o la 1, pentru sfera am
		calculat-o exact si pentru mini-turnulet o aproximez in functie de nivelul de scalare.
		- cand un inamic este lovit de proiectil, daca viata devine <= 0, marchez timpul la care
		a murit pentru a putea face animatia de cadere si micsorare sa dureze un timp stabilit.
		
		MINIMAP
		- folosesc un viewport separat, de dimensiune 180x180 pe care il adaug dreapta-jos
		- mai intai, setez viewport-ul mare, apelez functia care asigura desfasruarea jocului in acesta,
		dupa care, golesc bufferele "GL_COLOR_BUFFER_BIT" si "GL_DEPTH_BUFFER_BIT" si aplic comanda
		"glScissor" pentru viewport-ul mic astfel incat acesta sa fie desenat peste cel mare.
		- setez viewportul mic, apelez o noua functie care doar deseneaza elementele din scena mare,
		le inlocuieste cu modelul "box" (minimap-ul nu verifica coliziuni etc), si foloseste
		camera ce filmeaza de deasupra impreuna cu o matrice ortho pentru randare.
		- pentru fiecare element randat in minimap, nu recalculez matricile de transformre, ci le
		stochez intern claselor si le refolosesc (au fost calculate in viewport-ul mare).
		
		CADERE LATERALA + MICSORARE
		- caderea laterala se executa pentru o perioada stabilita astfel: cat timp nu a trecut perioada de
		executare a animatiei, incrementez unghiul de cadere al fiecarui inamic mort (stocat ca un membru in
		clasa)
		- la fel procedez si cu scalarea catre 0, pornesc de la factor de scalare 1 si il decrementez astfel
		incat la finalul animatiei sa devina 0
		- rotatia o palic pe toate cele 3 axe, ai sa creez efectul de rasturnare
		
		VIETI
		- avand in vedere ca jucatorul se misca doar pe OX si OZ, axa sa OY ramane aceeasi cu cea a 
		sistemului, deci rotatia in jurul lui OY e mai usoara.
		- rotatia in jurul celorlalte 2 axe se face suprapunand cu axele sistemului
		
		
		
		BONUS : TOWER DEFENCE
		
		- la apasarea tastei 'b', se intra/iese din modul tower defence
		- acesta arata similar cu minimap-ul (camera situata deasupra + proiectie ortho), doar ca
		afisarea se face pe intreg ecranul si camera are setat ca target originea sistemului, nu player-ul.
		- in plus, aceasta camera surprinde intreg spatiul scenei.
		- modul tower defence permite adaugarea de noi turnuri, prin apasarea butonului stanga de mouse
		- adaugarea se face in scena 3D, pornind de la locatia unde a fost apasat butonul stanga
		in proiectia ortho descrisa mai sus si un procedeu de conversie a coordonatei mouseX si mouseY
		in coordonate din spatiul 3D.
		- adaugarea de turnuri se poate face oricand doreste player-ul, numai daca a colectat mini-turnuletele
		care raman in urma anumitor inamici care au murit.
		- o data la 30 de secunde, un inamic care moare lasa in urma sa un mini-turn, player-ul
		il colecteaza intrand in el si astfel i se adauga in inventar.
		- asadar, numarul de turnuri ce pot fi adaugate coincide cu numarul de mini-turnuri colectate,
		adaugarea unui turn pe harta duce la eliminarea lui din inventar.