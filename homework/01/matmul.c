#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

const size_t N = 1024;

void ZeroMatrix(double *A, size_t N) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            A[i * N + j] = 0.0;
        }
    }
}

void RandomMatrix(double *A, size_t N) {
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)rand() / (double)RAND_MAX;
        }
    }
}

#ifndef NO_TEST_IJK
double CalcMatMulTime_ijk(double *A, double *B, double *C, size_t N) {
    struct timeval start, end;
    double r_time = 0.0;
    size_t i, j, k;

    ZeroMatrix(&C[0], N);

    gettimeofday(&start, NULL);

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++)
                C[i * N + j] = C[i * N + j] + A[i * N + k] * B[k * N + j];
        }
    gettimeofday(&end, NULL);

    r_time = end.tv_sec - start.tv_sec + ((double) (end.tv_usec - start.tv_usec)) / 1000000;

    return r_time;
}
#endif // NO_TEST_IJK

#ifndef NO_TEST_JIK
double CalcMatMulTime_jik(double *A, double *B, double *C, size_t N) {
    struct timeval start, end;
    double r_time = 0.0;
    size_t i, j, k;

    ZeroMatrix(&C[0], N);


    gettimeofday(&start, NULL);


    for (j = 0; j < N; j++)
        for (i = 0; i < N; i++) {
            for (k = 0; k < N; k++)
                C[i * N + j] = C[i * N + j] + A[i * N + k] * B[k * N + j];
        }
    gettimeofday(&end, NULL);

    r_time = end.tv_sec - start.tv_sec + ((double) (end.tv_usec - start.tv_usec)) / 1000000;

    return r_time;
}
#endif // NO_TEST_JIK

#ifndef NO_TEST_KIJ
double CalcMatMulTime_kij(double *A, double *B, double *C, size_t N) {
    struct timeval start, end;
    double r_time = 0.0;
    size_t i, j, k;

    ZeroMatrix(&C[0], N);

    gettimeofday(&start, NULL);

    for (k = 0; k < N; k++)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++)
                C[i * N + j] = C[i * N + j] + A[i * N + k] * B[k * N + j];
        }
    gettimeofday(&end, NULL);

    r_time = end.tv_sec - start.tv_sec + ((double) (end.tv_usec - start.tv_usec)) / 1000000;

    return r_time;
}
#endif // NO_TEST_KIJ

#ifndef NO_TEST_KIJ_OPT
double CalcMatMulTime_kij_opt(double *A, double *B, double *C, size_t N) {
    struct timeval start, end;
    double r_time = 0.0;
    size_t i, j, k;

    size_t dummy = 0;

    ZeroMatrix(&C[0], N);

    gettimeofday(&start, NULL);

    for (k = 0; k < N; k++)
        for (i = 0; i < N; i++) {
            dummy = i * N;
            for (j = 0; j < N; j++)
                C[dummy + j] = C[dummy + j] + A[dummy + k] * B[k * N + j];
        }
    gettimeofday(&end, NULL);

    r_time = end.tv_sec - start.tv_sec + ((double) (end.tv_usec - start.tv_usec)) / 1000000;

    return r_time;
}
#endif // NO_TEST_KIJ_OPT

#ifndef NO_TEST_KIJ_OPT2
double CalcMatMulTime_kij_opt2(double *A, double *B, double *C, size_t N) {
    struct timeval start, end;
    double r_time = 0.0;
    size_t i, j, k;

    size_t dummy = 0;
    size_t nSteps = N / 4;

    ZeroMatrix(&C[0], N);

    gettimeofday(&start, NULL);

    for (k = 0; k < N; k++)
        for (i = 0; i < N; i++) {
            dummy = i * N;

            for (j = 0; j < nSteps; ++j) {
                C[dummy + j * 4 + 0] = C[dummy + j * 4 + 0] + A[dummy + k] * B[k * N + j * 4 + 0];
                C[dummy + j * 4 + 1] = C[dummy + j * 4 + 1] + A[dummy + k] * B[k * N + j * 4 + 1];
                C[dummy + j * 4 + 2] = C[dummy + j * 4 + 2] + A[dummy + k] * B[k * N + j * 4 + 2];
                C[dummy + j * 4 + 3] = C[dummy + j * 4 + 3] + A[dummy + k] * B[k * N + j * 4 + 3];
            }
            for (j = 0; j < N % 4; ++j) {
                C[dummy + nSteps * 4 + j] = C[dummy + nSteps * 4 + j] + A[dummy + k] * B[k * N + nSteps * 4 + j];

            }
        }
    gettimeofday(&end, NULL);

    r_time = end.tv_sec - start.tv_sec + ((double) (end.tv_usec - start.tv_usec)) / 1000000;

    return r_time;
}
#endif // NO_TEST_KIJ_OPT2

int main() {

    int NRuns = 5;
    size_t i, j, k;

    double *runtimes;
    double *A, *B, *C;

    A = (double *) malloc(N * N * sizeof(double));
    B = (double *) malloc(N * N * sizeof(double));
    C = (double *) malloc(N * N * sizeof(double));
    runtimes = (double *) malloc(NRuns * sizeof(double));

    RandomMatrix(&A[0], N);
    RandomMatrix(&B[0], N);

    double average_runtime = 0.0;

#ifndef NO_TEST_IJK
// ijk ordering
    average_runtime = 0.0;
    printf("test ijk\n");
    for (int n = 0; n < NRuns; n++) {
        runtimes[n] = CalcMatMulTime_ijk(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n] / NRuns;
    }

    printf("average runtime ijk %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
#endif // NO_TEST_IJK

#ifndef NO_TEST_JIK
// jik ordering
    average_runtime = 0.0;
    printf("test jik\n");
    for (int n = 0; n < NRuns; n++) {
        runtimes[n] = CalcMatMulTime_jik(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n] / NRuns;
    }

    printf("average runtime jik %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
#endif // NO_TEST_JIK

#ifndef NO_TEST_KIJ
// kij ordering
    average_runtime = 0.0;
    printf("test kij\n");
    for (int n = 0; n < NRuns; n++) {
        runtimes[n] = CalcMatMulTime_kij(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n] / NRuns;
    }
    printf("average runtime kij %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
#endif // NO_TEST_KIJ

#ifndef NO_TEST_KIJ_OPT
// kij ordering naive optimization (useless for -O3)
    average_runtime = 0.0;
    printf("test kij opt\n");
    for (int n = 0; n < NRuns; n++) {
        runtimes[n] = CalcMatMulTime_kij_opt(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n] / NRuns;
    }
    printf("average runtime kij opt %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
#endif // NO_TEST_KIJ_OPT

#ifndef NO_TEST_KIJ_OPT2
// kij ordering step4 optimization
    average_runtime = 0.0;
    printf("test kij opt2\n");
    for (int n = 0; n < NRuns; n++) {
        runtimes[n] = CalcMatMulTime_kij_opt2(&A[0], &B[0], &C[0], N);
        printf("runtime %lf seconds\n", runtimes[n]);
        average_runtime += runtimes[n] / NRuns;
    }
    printf("average runtime kij opt %lf seconds\n", average_runtime);
    printf("---------------------------------\n");
#endif // NO_TEST_KIJ_OPT2

    free(A);
    free(B);
    free(C);
    return 0;
}
