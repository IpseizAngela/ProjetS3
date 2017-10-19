#ifndef OBJECT_BREAKOUT_H
#define OBJECT_BREAKOUT_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


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
/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     5
#define DEFAULT_WIDTH 32
#define DEFAULT_HEIGHT 16

/* number of different bricks */
#define NB_BRICKS 3
#define BRICK_HEIGHT    32
#define BRICK_WIDTH     64

/*******************  Structure of the sprite  *********************/
typedef struct Objet object_breakout;
struct Objet{
  int width;/*size of the sprite in width*/
  int height;/*and in height*/
  float x, y;/*position of the sprite on the screen*/
  float speed_x, speed_y;/*speed vector's*/
  SDL_Surface *sprite;/*picture of the sprite*/
  SDL_Rect picture, position;/*Rectangle of current picture and its position*/
  int c_frame;/*number of the current picture*/
  int n_frame;/*number total of picture of the sprite*/
  int counter;/*counter of the sprite to do differents things*/
};

/*******************  Prototype of function  ********************/
/*Management of keyboard key*/

void HandleEvent(SDL_Event event, int *quit,  SDL_Rect *position);
/*Count how many columns and row have in datafile*/
void count_dimension(FILE *file, int *row, int *col);
char** allocation2D (int l, int c);
char** read_data(FILE *file, int row, int col);
int max ( int a, int b);
object_breakout init_object (int type, float x_act, float y_act);
SDL_Surface *load(char *name_file);
void set_colorkey(SDL_Surface *screen,int R, int G, int B,SDL_Surface *sprite );
bool collide(sprite_t *sprite1,sprite_t *sprite2);
void draw(object_breakout *sprite,SDL_Surface *screen);
void erased(char T, int col);
float nb_random (float min, float max);
object_breakout** alloc (int l, int c);
//SDL_Surface* load_image(char *c);
#endif
