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
  char cursor;      //take the current value on the file
  bool end = false;  //for know if we are in the pair and unpair ligne
  int col1 = 1;      //count the number of columns if it's a pair line
  									//initialized at 1 for count the \n 
  int col2 = 1;      //count the number of colums if it's a unpair line
										//idem
  int max_col;       //take the maximum of the two numbers of columns
  cursor = fgetc (file); 
  while (cursor != EOF) {
  	if ( !end && (cursor != '\n') ) {
  		col1 += 1;
  	}
  	if ( end && (cursor != '\n') ) {
  		col2 += 1;
  	} 
  	if ( cursor == '\n' ) {
  		*row += 1;
  		if (end) {
  			end = false;
  			max_col = max(col1, col2);
  			if (max_col > *col) {
  				*col = max_col;      //we put the maximum of the number of columns if
  				                    // the max is superior at col
  			}
  			col1 = 1;     // put the numbers of columns at 1 otherwise we will have
  			col2 = 1;     // the number of all the character in the file
  		}
  		else {
  			end = true;
  		}
  	}
  	cursor = fgetc (file);
  }
  printf ("Row : %d, Col : %d \n", *row, *col);
}


/******* read the data text  ******/

char** read_data(FILE *file, int  row, int col) 
{  
  char ** T;
  T = allocation2D(row,col);   /*array of 2 dimensions for take the
                                             database and declared thanks
                                             to the allocation2D function */
  if (file != NULL) {                //read the file only if the file is open

    char cc;                            /*variable which the current 
					   character of the file */
    int i,j;                            //variables to range the array
    
    for(i=0;i<row;i++){                 //put all the contents of the file in 
      for(j=0;j<col;j++){                   //the array
	cc = fgetc(file);
	if ( (j < (col-1)) && (cc == '\n')) {
	  while (j < (col-1)) {
	    T[i][j] = ' ';
	    j++;
	  }
	}
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



/********* return the maximum between two integers ***********/
int max ( int a, int b) {
	int max_int = a;
	if ( b > a ) {
		max_int = b;
	}
	return max_int;
}



/******** initilize the briks **********/

object_breakout init_object (int type, float x_act, float y_act) {
    
    object_breakout object;  //creation of the object
    SDL_Surface *temp;       //temporaire variable to make the sprite of the object
    
    if (type == BRICKI) {
        object.width = 32;
        object.height = 16;
        object.x = x_act;
        object.y = y_act;
        temp = SDL_LoadBMP("Brick1.bmp");
        object.sprite = SDL_DisplayFormat (temp);
        SDL_FreeSurface (temp);
        object.c_frame = 1;
        object.n_frame = 1;
        object.picture.x = 0;
        object.picture.y = 0;
        object.picture.h = object.height;
        object.picture.w = object.width;
        object.position.x = (int) (object.x);
        object.position.y = (int) (object.y);
    }
    
    if (type == BRICKII) {
        object.width = 32;
        object.height = 16;
        object.x = x_act;
        object.y = y_act;
        temp = SDL_LoadBMP("Brick2.bmp");
        object.sprite = SDL_DisplayFormat (temp);
        SDL_FreeSurface (temp);
        object.c_frame = 1;
        object.n_frame = 2;
        object.picture.x = 0;
        object.picture.y = 0;
        object.picture.h = object.height;
        object.picture.w = object.width;
        object.position.x = (int) (object.x);
        object.position.y = (int) (object.y);
    }
    
    if (type == BRICKIII) {
        object.width = 32;
        object.height = 16;
        object.x = x_act;
        object.y = y_act;
        temp = SDL_LoadBMP("Brick3.bmp");
        object.sprite = SDL_DisplayFormat (temp);
        SDL_FreeSurface (temp);
        object.c_frame = 1;
        object.n_frame = 3;
        object.picture.x = 0;
        object.picture.y = 0;
        object.picture.h = object.height;
        object.picture.w = object.width;
        object.position.x = (int) (object.x);
        object.position.y = (int) (object.y);
    }
    
    return object;
}