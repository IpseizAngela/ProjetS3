#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  FILE* fichier = NULL;
  fichier = fopen("ddd.txt","r");
  char cc;
  char T[2][7];
  int i,j;
  for(i=0;i<2;i++){
    for(j=0;j<7;j++){
      cc = fgetc(fichier);
      T[i][j]=cc;
    }
  }
  for(i=0;i<2;i++){
    for(j=0;j<7;j++){
      printf(" %c", T[i][j]);
    }
  }
  printf("\n");
  return 0;
}
