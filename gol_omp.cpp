#include "gol.hpp"

#include <iostream>
#include <cstdlib>

using namespace std;

void step_omp(int **__restrict__ & matrix, int ** __restrict__ & matrixOld, int n, int m, int nw) {
    int i,j;
    #pragma omp parallel num_threads(nw) shared(matrix,matrixOld) private(i,j) firstprivate(n,m)
    {
        //#pragma omp single
        #pragma omp for schedule(static)
        for(i=1; i<n-1; i++) {
            //cout<<"ciclo: "<<i<<" ";
            //#pragma omp simd
            for(j=1; j<m-1; j++) {
                matrixOld[i][j] = matrix[i-1][j-1]+matrix[i-1][j]+matrix[i-1][j+1];
                matrixOld[i][j] += matrix[i][j-1]+matrix[i][j+1];
                matrixOld[i][j] += matrix[i+1][j-1]+matrix[i+1][j]+matrix[i+1][j+1];
            }
        }
        //#pragma omp single
        #pragma omp for schedule(static)
        for(i=1; i<n-1; i++) {
            //#pragma omp simd
            for(j=1; j<m-1; j++) {
                bool val=0;
                if(matrixOld[i][j] == 3)
                    val = 1;
                else if(matrixOld[i][j] == 2)
                    val = matrix[i][j];
                matrix[i][j] = val;
            }
        }
    }
}