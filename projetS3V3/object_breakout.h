#ifndef OBJECT_BREAKOUT_H
#define OBJECT_BREAKOUT_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

/******* define variables *******/
#define BRICKI 1
#define BRICKII 2
#define BRICKIII 3
#define BRICKIV 4


/* Size of the window */
#define SCREEN_WIDTH  1016
#define SCREEN_HEIGHT 792
/* Size of the background texture picture */
#define BG_WIDTH  254
#define BG_HEIGHT 198


/* Size of the platform: */
#define PLATFORM_WIDTH  64
#define PLATFORM_HEIGHT 16
/* Order of the different directions in the picture: */
//#define DIR_UP          0
#define DIR_RIGHT       1          //pas sûre d'en avoir besoin
//#define DIR_DOWN        2
#define DIR_LEFT        3          //idem

/* Number of pixels for one step of the sprite */
//#define SPRITE_STEP     5          //idem

#define DEFAULT_WIDTH 32
#define DEFAULT_HEIGHT 16

/* number of different bricks */
#define NB_BRICKS 3

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
object_breakout init_object (int type, float x_act, float y_act);

#endif
