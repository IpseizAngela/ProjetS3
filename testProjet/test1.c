#include <stdlib.h>
#include <stdio.h>

char** allocation2D (int l, int c) {
  char ** Tab = malloc(l*sizeof(char*));
  int i;
  for (i=0; i<l; i++) {
    Tab[i] = malloc(c*sizeof(char));
  }
  return Tab;
}

int main(int argc, char* argv[])
{
  FILE* fichier = NULL;
  fichier = fopen("ddd.txt","r");
  char cc;
  int i,j;
  char** T = allocation2D(2,8);
  for(i=0;i<2;i++){
    for(j=0;j<8;j++){
      cc = fgetc(fichier);
      T[i][j]=cc;
    }
  }
  for(i=0;i<2;i++){
    for(j=0;j<8;j++){
      printf(" %c", T[i][j]);
    }
  }
  printf("\n");
  return 0;
}