#ifndef OBJECT_BREAKOUT_H
#define OBJECT_BREAKOUT_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>


/********* Définition de la structure ********************/

struct objectBreakout 
{
  int width;                    //size of the sprite in width
  int height;                   //and in height
  float x, y;                   //position of the sprite on the screen
  float speed_x, speed_y;       //speed's vectors
  
  SDL_Surface *sprite;          //picture of the sprite
  SDL_Rect picture, position;   //rectangle of current picture and its position
  
  int c_frame;                  //number of the current picture
  int n_frame;                  //number total of picture for the sprite

  int counter;                  //counter of the sprite to do differents things
};


typedef struct objectBreakout object_breakout;



/********* Prototypes of the functions ***************/

void HandleEvent(SDL_Event event, int *quit,  SDL_Rect *position);
char** allocation2D (int l, int c);
void count_dimension(FILE *file, int *row, int *col);
char** read_data(FILE *file, int row, int col); 
int max ( int a, int b);

#endif
