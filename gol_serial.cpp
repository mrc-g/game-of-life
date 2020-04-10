#include "gol.hpp"

#include <iostream>
#include <cstdlib>

using namespace std;

void step_serial(int **__restrict__ & matrix, int ** __restrict__ & matrixOld, int n, int m) {
    for(int i=1; i<n-1; i++) {
        for(int j=1; j<m-1; j++) {
            matrixOld[i][j] = matrix[i-1][j-1]+matrix[i-1][j]+matrix[i-1][j+1];
            matrixOld[i][j] += matrix[i][j-1]+matrix[i][j+1];
            matrixOld[i][j] += matrix[i+1][j-1]+matrix[i+1][j]+matrix[i+1][j+1];
        }
    }

    for(int i=1; i<n-1; i++) {
        for(int j=1; j<m-1; j++) {
            bool val=0;
            if(matrixOld[i][j] == 3)
                val = 1;
            else if(matrixOld[i][j] == 2)
                val = matrix[i][j];
            matrix[i][j] = val;
        }
    }
}