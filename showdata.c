/* 3개 이진 파일을 보여준다.
   첫 번째 파일은 n x n 의 형태로 보여주며, 다른 두 파일은 한 줄로 보여준다.
*/
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "wrapper.h"

#define FNLEN 512

int main(int argc, char *argv[])
{
  struct stat finfoA, finfoB, finfoX;
  int noeleA, noeleB, noeleX;
  int i, j, cnt;
  double *Ar;
  int fd;
  
  /* check no. arguments */
  if (argc != 4){
    fprintf(stderr, "Usage: %s <mat> <vec1> <vec2>\n", argv[0]);
    exit(1);
  }

  /* check no. elements in files */
  Stat(argv[1], &finfoA);
  Stat(argv[2], &finfoB);
  Stat(argv[3], &finfoX);
  noeleA = finfoA.st_size / sizeof(double);
  noeleB = finfoB.st_size / sizeof(double);
  noeleX = finfoX.st_size / sizeof(double);
  if (noeleB  != noeleX)
    printf("Warning: no. elements of %s(%d) and %s(%d) are different.\n", argv[2], noeleB, argv[3], noeleX);
  if (noeleA != noeleB * noeleB)
    printf("Warning: no. elements(%d) of %s is not square of that(%d) of %s.\n", noeleA, argv[1], noeleB, argv[2]);
  
  Ar = (double *)malloc(sizeof(double) * noeleB);
  assert(Ar);
  fd = Open(argv[1], O_RDONLY);
  printf("\n===Contents of %s===\n", argv[1]);
  cnt = 0;
  for (i = 0; i < noeleB; i++){
    int nor = Read(fd, Ar, sizeof(double) * noeleB);
    for (j = 0; j < noeleB; j++)
      printf("%7.2lf ", Ar[j]);
    printf("\n");
    cnt += nor / sizeof(double);
    if (cnt >= noeleA) break;
  }
  close(fd);

  fd = Open(argv[2], O_RDONLY);
  printf("\n===Contents of %s===\n", argv[2]);
  Read(fd, Ar, sizeof(double) * noeleB);
  for (i = 0; i < noeleB; i++)
    printf("%7.2lf ", Ar[i]);
  printf("\n");
  close(fd);

  fd = Open(argv[3], O_RDONLY);
  printf("\n===Contents of %s===\n", argv[3]);
  Read(fd, Ar, sizeof(double) * noeleX);
  for (i = 0; i < noeleX; i++)
    printf("%7.2lf ", Ar[i]);
  printf("\n");
  close(fd);

  free(Ar);
}
