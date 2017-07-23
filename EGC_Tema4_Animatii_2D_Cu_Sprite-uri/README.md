

	Groapa Mihai
	334 CA
	
	
	Am 2 personaje : un samurai (Ichigo) si o fantoma (Menos)
	
	*Taste
	
		-> W : Ichigo ataca cu sabia
		-> S : Ichigo bareaza lovituri
		-> A : Ichigo isi schimba directia de deplasare spre stanga si se deplaseaza
		in acea directie daca tasta se tine apasata mai mult timp
		-> D : Ichigo isi schimba directia de deplasare spre dreapta si se deplaseaza
		
		-> KEY_UP : Menos ataca cu pumnul
		-> KEY_DOWN : Menos bareaza lovituri
		-> KEY_LEFT : similar cu efectul tastei 'A' dar aplicat lui menos
		-> KEY_RIGHT : analog
	
	*Clase
	
		Player : retin coordonatele jucatorului, directia de deplasare, viteza, 
		si animatiile pe care poate sa le realizeze (sub forma de vector);
		
		Animation : fiecare animatie are un nume, si mai multe Meshe.
		Fiecare mesh are o anumita latime data de coordonatele de texturare, de 
		asemenea are un factor de scalare, calculat pe baza mediei latimilor
		meshelor ce compun animatia. Scalarea fiecarei meshe cu factorul propriu
		calculat elimina acel efect de "latire" care apare daca se trece de la un
		mesh ingust la altul mai lat. O animatie are o durata care depinde de numarul
		de frame-uri componente. Un frame este randat in principiu de 15-20 de ori consecutiv.
		
		Laborator9 : aici parsez fisierele auxiliare, incarc cele 2 imagini ca texturi,
		incarc meshe pentru fiecare frame al fiecarei animatii si desfasor jocul.
		
	*Detalii de implementare
	
	-> rande pe ecran sub forma unui dreptunghi o imagine de background.
	-> sprite-sheets le-am editat astfel incat sa cuprinda doar animatiile de care am nevoie.
	-> cele 2 fisiere sunt similare cu cel dat ca exemplu in cerinta, fara partea de Triangles,
	pentru ca la mine meshele sunt redate pe un dreptunghi.
	-> parsez cele 2 fisiere si incarc meshe in forma de patrat pe care aplic pe rand
	texturi corespunzatoare unui frame.
	-> cele 2 personaje realizeaza "default" o animatie numita "stance" -> acel efect de bataie
	a vantului in scena.
	-> miscarea acelerata stanga/dreapta o realizez memorand momentul la care a inceput apasarea
	tastei pentru miscare si calculand timpul scurs din acel moment. Folosind valoarea acestui interval
	calculez noua pozitie in care sa fie randata mesha si de asemenea, trec mai rapid prin animatii
	reducand perioada fiecarui frame.
	-> personajul Ichigo realizeaza 2 animatii diferite de deplasare : daca au trecut mai putin de 2
	secunde de la inceperea apasarii tastei, animatia redata este "Walk", dupa, trece in modul "Run" :
	alearga cu sabia tinuta pe umar. Pentru Menos nu am gasit animatie de "Run".
	-> personajul Menos face o animatie de revenire din modul Guard la modul Stance.
	-> in ceea ce prveste animatia de cadere, pe langa rularea acesteia, deplasez si "dreptunghiurile"
	pe care sunt redate personajele astfel : daca personajul atacat este lovit in spate, acesta se 
	roteste in directia opusa si "se deplaseaza" in acea directie pe parcursul caderii (se obtine
	un efect de aruncare a personajului in directia in care a fost impins).
	-> jocul permite ca atacul sa se faca in timpul deplasarii insotit de o incetinire a 
	personajului la un sfert din viteza initiala, la sfarsitul atacului revenindu-se la viteza normala.
	-> in principiu am incercat sa tratez toate combinatiile posibile de taste, astfel incat sa se
	obtina un efect corect si autentic. Am tinut cont pe cat posibil de formulele matematice
	la deplasare, la verificarea coliziunilor - AABB, reducerea vitezei la 0 la schimbarea directiei de
	deplasare.

	*Cea mai mare dificultate in realizarea temei a fost decuparea corecta/egala/simetrica din spritesheet.
	E imposibil sa decupezi aplicand formule mtematice la unele animatii deoarece cadrele sunt inegale ca
	dimensuni, stabilirea coordonatelor am facut-o ochiometric, prin incercari repetate, tinand cont ca 
	frame-urile ce compun animatia sa aiba o latime aproximatv egala a coordonatelor de textura
	(la unele am mers pana la a 4-a zecimala).