serial: g_serial

g_serial.o: g_serial.c
	gcc -g -Wall -Wextra -c g_serial.c

g_serial: g_serial.o
	gcc -g g_serial.o -o g_serial

parallel: g_omp

g_omp.o: g_omp.c
	gcc -g -Wall -Wextra -fopenmp -c g_omp.c

g_omp: g_omp.o
	gcc -g g_omp.o -fopenmp -o g_omp

.PHONY : clean
clean:
	rm -f g_serial g_omp *.o
