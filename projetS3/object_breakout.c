#include "object_breakout.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SPRITE_STEP 5

/************** management of keyboard keys *****************/

void HandleEvent(SDL_Event event, int *quit,  SDL_Rect *position)
{
    switch (event.type) {
        /* close button clicked */
        case SDL_QUIT:
            *quit = 1;
            break;

        /* handle the keyboard */
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    *quit = 1;
                    break;
                case SDLK_LEFT:
                    position->x -= SPRITE_STEP;
                    break;
                case SDLK_RIGHT:
                    position->x += SPRITE_STEP;
                    break;
                default:
                    break;
            }
            break;
    }
}



/**********  give a memory for the 2D table  **********/

char** allocation2D (int l, int c) {
  char ** Tab = malloc(l*sizeof(char*));
  int i;
  for (i=0; i<l; i++) {
    Tab[i] = malloc(c*sizeof(char));
  }
  return Tab;
}

/******** count the number of rows and columns in the file ********/


void count_dimension (FILE *file, int *row, int *col) 
{
  char cursor;
  bool end = false;
  cursor = fgetc (file);
  while (cursor != EOF) {
  	if ( (end == false) && (cursor != '\n') ) {
  		*col += 1;
  	}
  	if ( cursor == '\n' ) {
  		*row += 1;
  		end = true;
  	}
  	cursor = fgetc (file);
  }
}

/******* read the data text  ******/
char** read_data(FILE *file, int  row, int col) 
{
 /* FILE* file = NULL;                    //declaration of the file
  file = fopen("breakout_data.txt","r");  //to open the data file */
  
  char ** T;
  if (file != NULL) {                //read the file only if the file is open
    char cc;                            /*variable which the current 
					   character of the file */
    int i,j;                            //variables to range the array
    T = allocation2D(row,col);   /*array of 2 dimensions for take the
                                             database and declared thanks
                                             to the allocation2D function */
    for(i=0;i<row;i++){                 //put all the contents of the file in 
      for(j=0;j<col;j++){                   //the array
	cc = fgetc(file);
	T[i][j]=cc;
      }
    }
  }
  else                         //print an error message if the file is not open
  {
    printf("Impossible d'ouvrir le fichier breakout_data.txt");
  } 
  printf("\n");
  return T;
}
