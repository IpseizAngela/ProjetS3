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
#define BALL 5
#define PLAT 6 

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

#define SPEED 2


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

  int counter;   //counter of the sprite to do differents things
  int colorkey;
  
  int score;   //the score of the object (only for the ball)
  int life;      //the number of life (only for the ball too)
};


typedef struct objectBreakout object_breakout;



/********* Prototypes of the functions ***************/



/************** management of keyboard keys *****************/
void HandleEvent(SDL_Event event, int *quit,  object_breakout *platform, bool *throw, object_breakout *ball, int *finish_level);

/********* move the platform in funcion of their position ********/
void move_plat (object_breakout *plat);

/**********  give a memory for the 2D table  **********/
char** allocation2D (int l, int c);

/******* give a memoru fot the 2D object_breakout table *******/
object_breakout** alloc (int l, int c) ;

/******** count the number of rows and columns in the file ********/
void count_dimension(FILE *file, int *row, int *col);

/******* read the data text  ******/
char** read_data(FILE *file, int row, int col); 

/********* return the maximum between two integers ***********/
int max ( int a, int b);

/********* return the minimum between two integers ***********/
int min (int a, int b) ;

/*** load the image ***/
SDL_Surface * load (char * name_file);

/********** set the colokey of the image ********/
void set_colorkey (SDL_Surface *screen, int R, int G, int B, SDL_Surface *sprite) ;

/******** initilize the briks **********/
object_breakout init_object (int type, float x_act, float y_act, SDL_Surface *screen);

/*********  print the contents of  a table ***************/
void print_tab (object_breakout *table, int nb,  SDL_Surface *screen);

/********  make move the ball ************/
void move_ball (object_breakout *ball);

/* Collide between 2 objects */
bool collide(object_breakout *sprite1, object_breakout *sprite2);

/*** make a rebond on the ball *****/
void rebond (object_breakout *balle, int side);

/***** read the data table to put them on an other table for the gestion of the bricks ****/
void read_table (object_breakout **table, char** tab_data, float *x, float  *y, int row, int col, int *nbI, int *nbII, int *nbIII,  SDL_Surface *screen) ;

/****** see with precision if we are a collision between two objects ****/
bool collide_precise (object_breakout *sprite1, object_breakout *sprite2, SDL_PixelFormat *format, int *cu, int *cv);

/*** look if we are a collision in a table ***/
void collide_table (object_breakout ** table, int *n, int *m, int *l, object_breakout *ball, SDL_PixelFormat *format, int nbtype);

/***** look if we are a collision between a brick and the ball into the table ******/
bool collide_table_aux (object_breakout *table , int *n, object_breakout *ball, SDL_PixelFormat *format, int type);

/**** loke if we are a collision between the platform and the ball ******/
void collide_platform (object_breakout *plat, object_breakout *ball, SDL_PixelFormat *format);

/******* look if there is a collision between the platform and the edges of the screen ********/
void collide_screen (object_breakout *platform);

/****** draw the bakground on the screen **********/
void draw_background (SDL_Surface *background, SDL_Surface *screen) ;

/***** print an object_breakout *****/
void print_object (object_breakout *object, SDL_Surface *screen);

/**** print different text on the screen ****/
void print_text (const char *text, int val, SDL_Surface *screen, int pos_x, int pos_y);

#endif
