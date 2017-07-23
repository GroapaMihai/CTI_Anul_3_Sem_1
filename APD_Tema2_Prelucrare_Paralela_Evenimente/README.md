
		Groapa Mihai 334CA


	* Parcurg argumentele primite in linie de comanda, salvez dimensiunea cozii
	si numarul de evenimente per fisier, calculez numarul total de evenimente
	pentru a putea opri thread-ul care pune workerii in functiune.
	* Obtin numarul de procesoare ale sistemului si creez un work-pool care
	contine numarul corespondent de workeri.
	* Pentru coada in care adaug evenimente folosesc ArrayBlockingQueue si pentru
	stocarea rezultatelor corespunzatoare fiecarui eveniment utilizez liste
	sincronizate.
	* Creez cate un generator pentru fiecare fisier cu date de input. Generatorul
	are rolul de a citi fiecare linie din fisier, a parsa informatia si de a 
	adauga evenimentul in coada.
	* Am o clasa Event din care extind alte 4 clase, cate una pentru fiecare
	tip de eveniment. Subclasele suprascriu metoda execute() a clasei parinte.
	Metoda execute a fiecarei sublcase are rolul de a calcula rezultatul pentru
	evenimentul corespondent.
	* Crearea de evenimente se face folosind design pattern-ul Factory.
	* Clasa EventExecutor extinde "Thread", o instantiez o singura data si are rolul
	de a scoate evenimente din coada daca aceasta nu este goala, daca sunt workeri
	disponibili in pool si de a crea un worker pentru executia evenimentului scos,
	dupa care marcheaza faptul ca un task este executat decrementand numarul de 
	workeri disponibili, si incrementand numarul de evenimente executate.
	* Un worker verifica ce tip are evenimentul de executat, dupa care adauga
	in lista sincronizata asociata tipului de eveniment rezultatul obtinut
	apeland metoda execute a taskului primit si incrementeaza numarul de workeri
	available din pool la finalul executiei taskului.
	* Dupa crearea generatorilor, dau start executorului de evenimente, pornesc
	generatorii care incep sa citeasca si sa adauge in coada si cand
	EventExecutor-ul a terminat de executat toate taskurile ii dau join, dau
	shutdown ExecutorService-ului si astept terminarea executiei taskurilor
	pentru toti workerii. La final, generatorii fac join, urmand ca thread-ul
	main sa sorteze cele 4 liste rezultate, dupa care, creaza 4 threaduri
	Writer, fiecare avand scopul de a scrie cate un fisier de output.
