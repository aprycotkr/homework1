#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "wrapper.h"

void gaussianElimination(double A[4], double B[2], double X[2]) {
    double factor;

    // Perform Gaussian elimination
    factor = A[2] / A[0];
    A[2] -= factor * A[0];
    B[1] -= factor * B[0];

    // Solve for X[1]
    X[1] = B[1] / A[3];

    // Substitute X[1] back into the first equation
    X[0] = (B[0] - A[1] * X[1]) / A[0];
}

void argCheck(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <mat> <invec> <outvec>\n", argv[0]);
        exit(1);
    }
}

void sizeCheck(int argc, char* argv[]) {
    struct stat finfoA, finfoB;
    int noeleA, noeleB;

    Stat(argv[1], &finfoA);
    Stat(argv[2], &finfoB);
    noeleA = finfoA.st_size / sizeof(double);
    noeleB = finfoB.st_size / sizeof(double);
    if (noeleA != noeleB * noeleB) {
        fprintf(stderr, "Error: no. elements(%d) of %s is not square of that(%d) of %s.\n", noeleA, argv[1], noeleB, argv[2]);
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    int afd, bfd, xfd;
    double A[4], B[2], X[2];
    double dete; /* 행렬 A의 determinant */

    argCheck(argc, argv);
    sizeCheck(argc, argv);
    afd = Open(argv[1], O_RDONLY);
    bfd = Open(argv[2], O_RDONLY);
    Read(afd, A, sizeof(double) * 4);
    Read(bfd, B, sizeof(double) * 2);
    close(afd);
    close(bfd);

    // Solve the system of linear equations
    gaussianElimination(A, B, X);

    xfd = Creat(argv[3], 0644);
    Write(xfd, X, sizeof(double) * 2);
    close(xfd);

    return 0;
}
