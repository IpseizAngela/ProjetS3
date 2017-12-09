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
#define BRICKI 1    //blue brick
#define BRICKII 2  //green brick
#define BRICKIII 3  //red break 
#define BRICKIV 4  //black brick
#define BRICKV 5  //yellow brick
#define BRICKVI 6  //beige brick
#define BRICKVII 7   //pink brick
#define BALL 8
#define PLAT 9
#define BONUS 10

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

#define DEFAULT_WIDTH 16
#define DEFAULT_HEIGHT 16

/* number of different bricks */
#define NB_BRICKS 7

#define SPEED 2

#define MAX_SIZE 30

#define NB_BONUS_IN_SAME_TIME 15

/*Type of the bonus*/
#define REDUC 1
#define GROW  2
#define LOST  3
#define LIFE   4
#define SCORE  5
#define BOUNCE 6
#define MULTI  7
#define CROSS 8
#define MIN 9  
#define SLOW_BALL 10
#define SPEED_BALL 11
#define SLOW_PLAT 12
#define SPEED_PLAT 13
/*Duration of the bonus when it was activated*/
#define TIME_REDUCE 5000
#define TIME_GROW  50
#define TIME_BOUNCE  100000
#define TIME_CROSS  100000000
#define TIME_SLOW_BALL 100
#define TIME_SPEED_BALL 100
#define TIME_SLOW_PLAT 200
#define TIME_SPEED_PLAT 2000000


#define SPEEDX 2
#define SPEEDY 2

#define ALEA 20


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
  int t_bonus;    //Give the type of the bonus
  bool activate;     //Use for the bonus 
  bool initiate;      //Use for the ball's bonus
  bool bounce;
  bool cross;
};


typedef struct objectBreakout object_breakout;



/********* Prototypes of the functions ***************/



/************** management of keyboard keys for all the game  *****************/
void HandleEvent(SDL_Event event, int *quit,  object_breakout *platform, bool *throw, object_breakout *ball, int *finish_level);

/************** management of keyboard keys for the menu ************/
void handle_event_menu (SDL_Event event_menu, int *exit, int *begin, SDL_Surface *screen, SDL_Surface *background, int *play) ;

/************** management of keyboard keys for the lose menu ************/
void handle_event_lose (SDL_Event event_lose,  int *exit, int *gameover, int *choose, int *replay) ;


void rule (SDL_Surface *screen, SDL_Surface *background);

/********* management of keyboard keys when the player must write his name *****/
void handle_event_name (SDL_Event event_name, int *end, char *name);

/********* move the platform in funcion of their position ********/
void move_plat (object_breakout *plat);

/**********  give a memory for the 2D table  **********/
char** allocation2D (int l, int c);

/******* give a memoru fot the 2D object_breakout table *******/
object_breakout** alloc (int l, int c) ;

/******** count the number of rows and columns in the file ********/
void count_dimension(FILE *file, int *row, int *col, int *nb_char);

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
//void set_colorkey (SDL_Surface *screen, int colorkey, SDL_Surface *sprite) ;

/******** initilize the briks **********/
object_breakout init_object (int type, float x_act, float y_act, SDL_Surface *screen, int type_bonus) ;

/*********  print the contents of  a table ***************/
void print_tab (object_breakout *table, int nb,  SDL_Surface *screen);

/********  make move the ball ************/
void move_ball (object_breakout *ball, int *nb, object_breakout *platform, object_breakout *tab_bonus, SDL_Surface *screen, bool *throw, int *nb_power);

/* Collide between 2 objects */
bool collide(object_breakout *sprite1, object_breakout *sprite2);

/*** make a rebond on the ball *****/
void rebond (object_breakout *ball, int side, bool collide_screen);

/***** read the data table to put them on an other table for the gestion of the bricks ****/
void read_table (object_breakout **table, char** tab_data, float *x, float  *y, int row, int col, 
		 int *nbI, int *nbII, int *nbIII, int *nbIV, int *nbV, int *nbVI, int *nbVII, SDL_Surface *screen) ;

/****** see with precision if we are a collision between two objects ****/
bool collide_precise (object_breakout *sprite1, object_breakout *sprite2, SDL_PixelFormat *format, float *cu, float *cv);

/*** look if we are a collision in a table ***/
bool collide_table (object_breakout ** table, int *n, int *m, int *l, int *p,
		    int *q, int *r, int *s, object_breakout *ball, int nb_ball,
		    SDL_PixelFormat *format, int nbtype, float *cx, float *cy);

/***** look if we are a collision between a brick and the ball into the table ******/
bool collide_table_aux (object_breakout *table , int *n, object_breakout *ball, int nb_ball, SDL_PixelFormat *format, int type, float *u, float *v);

/**** loke if we are a collision between the platform and the ball ******/
void collide_platform (object_breakout *plat, object_breakout *ball, int nb, SDL_PixelFormat *format);

/******* look if there is a collision between the platform and the edges of the screen ********/
void collide_screen (object_breakout *platform);

/****** draw the bakground on the screen **********/
void draw_background (SDL_Surface *background, SDL_Surface *screen) ;

/***** print an object_breakout *****/
void print_object (object_breakout *object, SDL_Surface *screen);

/**** print different text on the screen ****/
void print_text (const char *text, int val, SDL_Surface *screen, int pos_x, int pos_y, int size, int select) ;

/***** creation of the menu ***********/
void menu (int *exit, SDL_Surface *screen, SDL_Surface *background);

/******* creation of the lose menu ********/
void lose (int *exit, int *gameover, SDL_Surface *screen, SDL_Surface *background,FILE *file, int score);

/******* creation of the win menu ********/
void win (int *exit, int *finish_level,  SDL_Surface *screen, SDL_Surface *background, FILE *file, int score) ;


void print_name (SDL_Surface *screen, SDL_Surface *background, char *name, int win);


void ranking (SDL_Surface *screen, SDL_Surface *background, int score_player, int win) ;

void rule (SDL_Surface *screen, SDL_Surface *background);

/*add an element in an array and initialize*/
void add (object_breakout *tab, int *n, int cx, int cy, SDL_Surface *screen, int type_bonus);

/********  make move the ball ************/
void move_power (object_breakout *reduc, int *n);

/*reduce the size of the platform*/
void power (object_breakout *power, int *n, SDL_Surface *screen, int cx, int cy);

/*delete an element in an array*/
void del (object_breakout *tab, int *n, int cur);


/* Gives a random number between two ends */
int nb_random ();

/*******  handle the collide between bonus and platform  *************/
void collide_power (object_breakout *platform, object_breakout *power, 
                    object_breakout *ball, int *nb_ball, SDL_Surface *screen, int *n, int *gameover);

/*Handle the bonus time*/
void power_time (object_breakout *platform, object_breakout *ball, int nb_ball, object_breakout *tab, int *n, SDL_Surface *screen);

#endif
