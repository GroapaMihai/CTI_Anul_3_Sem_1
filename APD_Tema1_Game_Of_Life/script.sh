#!/bin/bash
export OMP_NUM_THREADS=15
time ./g_omp $1 $2 $3
