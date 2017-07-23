#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readMatrix(FILE *in, char **oldMatrix, char **newMatrix, int m, int n) {  
	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++) {
			fscanf(in, "%c ", *(oldMatrix + i) + j);
			*(*(newMatrix + i) + j) = '.';
		}
}

void printMatrix(FILE *out, char **oldMatrix, int m, int n) {
	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++)
			fprintf(out, "%c ", *(*(oldMatrix + i) + j));
		if(i != m)
			fprintf(out, "\n");
	}
}

int main(int argc, char **argv) {
	// verificare corectitudine format comanda
	if(argc != 4) {
		printf("Format: ./g_serial fisier_intrare iteratii fisier_iesire\n");
		return -1;
	}

	// deschiderea fisierelor si verificarea posibilitatii de deschidere
	FILE *in, *out;
	in = fopen(argv[1], "rt");
	if(in == NULL) {
		printf("Error when opening input file\n");
		return -1;
	}

	out = fopen(argv[3], "wt");
	if(out == NULL) {
		printf("Error when opening output file\n");
		return -1;
	}

	int m, n, i, j, k, gen, living_neighbours;
	char **oldMatrix;
	char **newMatrix;
	fscanf(in, "%d %d\n", &m, &n);
	char iCoeficient[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	char jCoeficient[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

	// alocare matrice
	oldMatrix = calloc(m + 2, sizeof(char*));
	newMatrix = calloc(m + 2, sizeof(char*));
	for(i = 0; i < m + 2; i++) {
		*(oldMatrix + i) = (char*) calloc(n + 2, sizeof(char));
		*(newMatrix + i) = (char*) calloc(n + 2, sizeof(char));
	}

	readMatrix(in, oldMatrix, newMatrix, m, n);

	for(gen = 0; gen < atoi(argv[2]); gen++) {
		// initializare colturi
		(**oldMatrix) = *(*(oldMatrix + m) + n);
		*(*(oldMatrix + m + 1) + n + 1) = *(*(oldMatrix + 1) + 1);
		*(*(oldMatrix) + n + 1) = *(*(oldMatrix + m) + 1);
		**(oldMatrix + m + 1) = *(*(oldMatrix + 1) + n);

		// adaugare linii exterioare
		for(j = 1; j <= n; j++) {
			*(*(oldMatrix) + j) = *(*(oldMatrix + m ) + j);
			*(*(oldMatrix + m + 1) + j) = *(*(oldMatrix + 1) + j);
		}

		// adaugare coloane exterioare
		for(i = 1; i <= m; i++) {
			**(oldMatrix + i) = *(*(oldMatrix + i) + n);
			*(*(oldMatrix + i) + n + 1) = *(*(oldMatrix + i) + 1);
		}

		for(i = 1; i <= m; i++)
			for(j = 1; j <= n; j++) {
				living_neighbours = 0;
				for(k = 0; k < 8; k++)
					if(*(*(oldMatrix + i + iCoeficient[k]) + j + jCoeficient[k]) == 'X')
						living_neighbours++;

				/* 1. mai putin de 2 vecini ALIVE => DEAD
				2. 2 sau 3 vecini ALIVE => ALIVE
				3. mai mult de 3 vecini => DEAD
				4. DEAD are exact 3 vecini ALIVE => ALIVE */
				if(living_neighbours < 2)
					*(*(newMatrix + i) + j) = '.';
				else if(living_neighbours <= 3 && *(*(oldMatrix + i) + j) == 'X')
					*(*(newMatrix + i) + j) = 'X';
				else if(living_neighbours > 3)
					*(*(newMatrix + i) + j) = '.';
				else if(living_neighbours == 3 && *(*(oldMatrix + i) + j) == '.')
					*(*(newMatrix + i) + j) = 'X';
			}

		// copiere matrice noua in cea veche
		for(i = 1; i <= m; i++)
			for(j = 1; j <= n; j++)
				*(*(oldMatrix + i) + j) = *(*(newMatrix + i) + j);
	}

	printMatrix(out, newMatrix, m, n);

	// eliberare memorie + inchidere fisiere
	for(i = 0; i < m + 2; i++) {
		free(*(oldMatrix + i));
		free(*(newMatrix + i));
	}

	free(oldMatrix);
	free(newMatrix);
	fclose(in);
	fclose(out);

	return 0;
}
