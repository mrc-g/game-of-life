#include <iostream>
#include <string>
#include <omp.h>
#include <chrono>
#include <thread>

#include <cstdlib>

using namespace std;
using namespace chrono;
using namespace this_thread;

#include "utimer.cpp"

#include "gol.hpp"

void init(int **__restrict__ &A,int n, int m) {
    A = new int*[n];
    for(int i=0; i<n; i++) {
        A[i] = new int[m];

        for(int j=0; j<m; j++) {
            if(i==0 || j==0 || i==n-1 || j==m-1)
                A[i][j] = 0;
            else
                A[i][j] = rand() % 2;
        }
    }
}

void clone(int **__restrict__ &Dst, int **__restrict__ &Src, int n, int m) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            Dst[i][j] = Src[i][j];
        }
    }
}

void init_filled(int **__restrict__ &A,int n, int m) {
    A = new int*[n];
    for(int i=0; i<n; i++) {
        A[i] = new int[m]();
    }
}

void print(int **__restrict__ A, int n, int m) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(A[i][j]) {
                cout << "O";
            }else{
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main(int argc, char * argv[]) {

    if(argc != 6) {
        cout << "Usage: /program nw seed n m iter" << endl;
        return 0;
    }

    int nw = atoi(argv[1]);
    int seed = atoi(argv[2]);
    int n = atoi(argv[3]);
    int m = atoi(argv[4]);
    int iter = atoi(argv[5]);

    srand(seed);

    int **__restrict__ serial_M, **__restrict__ omp_M, **__restrict__ thread_M;
    init_filled(serial_M, n,m);
    init(omp_M,n,m);
    clone(omp_M, serial_M, n,m);
    init(thread_M,n,m);
    clone(thread_M, serial_M, n,m);    
    int **__restrict__ tmpM;
    init_filled(tmpM, n,m);
    
    if(iter < 1000 && n<100 && m <100) {
        print(serial_M,n,m);
        for(int i = 0; i< iter; i++) {
            step_serial(serial_M,tmpM,n,m);
            print(serial_M,n,m);
            sleep_for(milliseconds(300));
        }
    }else {
        //serial
        {
            utimer u("serial");
            for(int i = 0; i< iter; i++) {
                step_serial(serial_M,tmpM,n,m);
            }
        }

        //omp
        {
            utimer u("omp   ");
            for(int i = 0; i< iter; i++) {
                step_omp(serial_M,tmpM,n,m,nw);
            }
        }

        //thread
    }

    return 0;
}