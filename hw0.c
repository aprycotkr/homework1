/* Description:
     It finds a vector x of a equation Ax = b
     where 2 x 2 matrix A and vector b are given.
   Usage:
    ./hw0 A.dat b.dat x.dat
    A.dat and b.dat are inputs, x.dat is the output.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "wrapper.h"

void argCheck(int argc, char *argv[])
{
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <mat> <invec> <outvec>\n", argv[0]);
    exit(1);
  }
}

void sizeCheck(int argc, char *argv[])
{
  struct stat finfoA, finfoB;
  int noeleA, noeleB;

  Stat(argv[1], &finfoA);
  Stat(argv[2], &finfoB);
  noeleA= finfoA.st_size / sizeof(double);
  noeleB = finfoB.st_size / sizeof(double);
  if (noeleA != noeleB * noeleB){
    fprintf(stderr, "Error: no. elements(%d) of %s is not square of that(%d) of %s.\n", noeleA, argv[1], noeleB, argv[2]);
    exit(1);
  }
}

int main(int argc, char *argv[])
{
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
  /* 여기서 연립방정식을 풀어서 X[0]과 X[1]을 구한다. */
  dete = 1; /* 수정 필요 */
  X[0] = dete;  /* 수정 필요 */
  X[1] = dete;  /* 수정 필요 */
  xfd = Creat(argv[3], 0644);
  Write(xfd, X, sizeof(double) * 2);
  close(xfd);
  return 0;
}
