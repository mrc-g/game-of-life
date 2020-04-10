void step_serial(int **__restrict__ &matrix, int **__restrict__ &matrixOld, int n, int m);
void step_omp(int **__restrict__ &matrix, int **__restrict__ &matrixOld, int n, int m, int nw);
void step_thread(int **__restrict__ &matrix, int **__restrict__ &matrixOld, int n, int m);
