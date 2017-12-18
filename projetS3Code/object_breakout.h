#ifndef OBJECT_BREAKOUT_H
#define OBJECT_BREAKOUT_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

/******************************************************************************
 ****************************** define variables ******************************
 *****************************************************************************/

/* blue brick */
#define BRICKI 1    
/* green brick */
#define BRICKII 2 
/* red brick */
#define BRICKIII 3  
/* black brick */
#define BRICKIV 4  
/* yellow brick */
#define BRICKV 5  
/* beige brick */
#define BRICKVI 6  
/* pink brick */
#define BRICKVII 7   
/* to initialize the ball */
#define BALL 8        
/* to initialize the platform */
#define PLAT 9     
/* to initialize a bonus */
#define BONUS 10    

/* Number of different bricks */
#define NB_BRICKS 7

/*Size of the platform */
#define PLATFORM_WIDTH 64
#define PLATFORM_HEIGHT 16

/* Speed of the ball in x and y */
#define SPEEDX 3
#define SPEEDY 3

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

/*Number total of bonus*/
#define NB_TOTAL_BONUS 13

/* For the apparition of the bonus, there is a 
 random's number  between 0 and this number */
#define ALEA 40

/*Duration of the bonus when it was activated*/
#define TIME_REDUCE 2000
#define TIME_GROW  2000
#define TIME_BOUNCE  2000
#define TIME_CROSS  2000
#define TIME_SLOW_BALL 1000
#define TIME_SPEED_BALL 1000
#define TIME_SLOW_PLAT 1000
#define TIME_SPEED_PLAT 1000

/*Number of bonus which can be in same time */
#define NB_BONUS_IN_SAME_TIME 15

/*Size of a empty in the datafile */
#define DEFAULT_WIDTH 16
#define DEFAULT_HEIGHT 16

/* Size of the window */
#define SCREEN_WIDTH  1016
#define SCREEN_HEIGHT 792

/* Size of the background texture picture */
#define BG_WIDTH  254
#define BG_HEIGHT 198

/* Number of pixels for one step of the sprite */
#define SPRITE_STEP     5         

/* Duration for the print of the level's number */
#define NEXT_LEVEL 100

/* Number max of different tables */
#define MAX_SIZE 30

/* Number of people in the rank */
#define NB_RANK 10


/******************************************************************************
 ************************** definition of the structure  **************************
 *****************************************************************************/

struct objectBreakout 
{
    /*size of the sprite in width */
  int width;                    
  /*and in height */
  int height;                   
  /* position of the sprite on the screen*/
  float x, y;                   
  /*speed's vectors*/
  float speed_x, speed_y;       
  
  /*picture of the sprite*/
  SDL_Surface *sprite;          
  /*rectangle of current picture and its position*/
  SDL_Rect picture, position;   
  
  /*number of the current picture*/
  int c_frame;                  
  /*number total of picture for the sprite*/
  int n_frame;                  

  /*counter of the sprite to do differents things*/
  int counter;   
  /*the color to erase*/
  int colorkey;
  
  /*the score of the object (only for the ball)*/
  int score;   
  /*the number of life (only for the ball too)*/
  int life;      
  /*Give the type of the bonus*/
  int t_bonus;    
  /*Use to activate the bonus */
  bool activate;     
  /*Use for the ball's bonus*/
  bool initiate;      
  /*use for the bounce bonus*/
  bool bounce;
  /*use for the cross bonus*/
  bool cross;
};

/* put the structure to a type*/
typedef struct objectBreakout object_breakout;


/******************************************************************************
************************* PROTOTYPES OF FONCTIONS ************************
 *****************************************************************************/


/******************************************************************************
************************** handle_event fonctions ***************************
 *****************************************************************************/

/************** management of keyboard keys for the menu ************/
void handle_event_menu (SDL_Event event_menu, int *exit, int *begin, 
                        int *play, int *enter_in_rule, int *credit, int *quit)  ;

/************** management of keyboard keys for the rules menu ************/
void handle_event_rule (SDL_Event event_rule, int *quit_rule, int *second_r,
                        int rule_curr,  int *go_out);
 
/************** management of keyboard keys for the credit menu ************/
void handle_event_credit (SDL_Event event_credit, int *quit, int * go_out);
  
/************** management of keyboard keys for the break menu ************/
void handle_event_break (SDL_Event event_break, int *quit_break, 
                         int *go_out); 

/************** management of keyboard keys for all the game  *****************/
void HandleEvent(SDL_Event event, int *quit,  object_breakout *platform
                , bool *throw, object_breakout *ball, int *finish_level, 
                 int *go_out, SDL_Surface *screen);

/********* management of keyboard keys when the player must write his name *****/
void handle_event_name (SDL_Event event_name, int *end, char *name);

/************** management of keyboard keys for the lose menu ************/
void handle_event_lose (SDL_Event event_lose,  int *exit, int *gameover, 
                        int *choose, int *replay, int *counter_level) ;



  
/******************************************************************************
******************************* menu fonctions ********************************
 *****************************************************************************/
  
  /*  creation of the main menu */
void menu (int *exit, SDL_Surface *screen, SDL_Surface *background);

/* Explain the rules of the game */
void rule (SDL_Surface *screen, SDL_Surface *background, int *exit);

/* Explain the functionality of the bonus */
void scd_rule (SDL_Surface *screen, SDL_Surface *background, int *exit);

/* creation of the credit menu */
void menu_credit (SDL_Surface *screen, SDL_Surface *background, int *exit);

/* Put break during the game */
void menu_break (SDL_Surface *screen, int *go_out);

/******* creation of the lose menu ********/
void lose (int *exit, int *gameover, SDL_Surface *screen,
           SDL_Surface *background,FILE *file, int score, int *counter_level);

/******* creation of the win menu ********/
void win (int *exit, int *finish_level,  SDL_Surface *screen, 
          SDL_Surface *background, FILE *file, int score, int *counter_level) ;
  


/******************************************************************************
******************************* allocation fonctions **************************
 *****************************************************************************/

/**********  give a memory for the 2D table  **********/
char** allocation2D (int l, int c);

/******* give a memoru fot the 2D object_breakout table *******/
object_breakout** alloc (int l, int c) ;



/******************************************************************************
******************************* data fonctions **************************
 *****************************************************************************/

/******** count the number of rows and columns in the file ********/
void count_dimension (FILE *file, int *row, int *col, int *nb_char) ;

/********* return the maximum between two integers ***********/
int max ( int a, int b);

/********* return the minimum between two integers ***********/
int min (int a, int b) ;

/******* read the data text  ******/
char** read_data(FILE *file, int row, int col); 

/***** read the data table to put them on an other table for the gestion of the bricks ****/
void read_table (object_breakout **table, char** tab_data, float *x, float  *y,
                 int row, int col,  int *nbI, int *nbII, int *nbIII, int *nbIV,
                 int *nbV, int *nbVI, int *nbVII, SDL_Surface *screen) ;



/******************************************************************************
******************************* load fonctions **************************
 *****************************************************************************/

/* load the good bonus for the rule menu */
SDL_Surface* load_bonus (int i);

/*** load the image ***/
SDL_Surface * load (char * name_file);

/********** set the colokey of the image ********/
void set_colorkey (SDL_Surface *screen, int R, int G, int B, SDL_Surface *sprite) ;




/******************************************************************************
***************************** initialization fonctions ************************
 *****************************************************************************/

/******** initilize the briks, ball, platform and bonus (the object_breakout object) **********/
object_breakout init_object (int type, float x_act, float y_act, SDL_Surface *screen, 
                             int type_bonus) ;




/******************************************************************************
********************************* move fonctions ****************************
 *****************************************************************************/

/********* move the platform in funcion of their position ********/
void move_plat (object_breakout *plat);

/********  make move the ball ************/
void move_ball (object_breakout *ball, int *nb, object_breakout *platform, 
                object_breakout *power, int *nb_power, SDL_Surface *screen, 
                 bool *throw);

/********  make move the bonus ************/
void move_power (object_breakout *tab, int *n);



/******************************************************************************
******************************** collide fonctions ****************************
 *****************************************************************************/

/* Collide between 2 objects */
bool collide(object_breakout *sprite1, object_breakout *sprite2);

/****** see with precision if we are a collision between two objects ****/
bool collide_precise (object_breakout *sprite1, object_breakout *sprite2, 
                      SDL_PixelFormat *format, float *cu, float *cv);

/*** look if we are a collision in a table ***/
bool collide_table (object_breakout ** table, int *n, int *m, int *l, int *p,
		    int *q, int *r, int *s, object_breakout *ball, int nb_ball,
		    SDL_PixelFormat *format, int nbtype, float *cx, float *cy);

/***** look if we are a collision between a brick and the ball into the table ******/
bool collide_table_aux (object_breakout *table , int *n, object_breakout *ball, 
                        int nb_ball, SDL_PixelFormat *format, int type, float *u, float *v,
                       bool *exit1);

/**** loke if we are a collision between the platform and the ball ******/
void collide_platform (object_breakout *plat, object_breakout *ball, int nb, 
                       SDL_PixelFormat *format);

/******* look if there is a collision between the platform and the edges of the screen ********/
void collide_screen (object_breakout *platform);

/*******  handle the collide between bonus and platform  *************/
void collide_power (object_breakout *platform, object_breakout *power, 
                    object_breakout *ball, int *nb_ball, SDL_Surface *screen,
                    int *n, int *gameover);

/*** make a rebond on the ball *****/
void rebond (object_breakout *ball, int side, bool collide_screen);



/******************************************************************************
******************************** power fonctions ****************************
 *****************************************************************************/

/*reduce the size of the platform*/
void power (object_breakout *power, int *n, SDL_Surface *screen, int cx, int cy);

/*Handle the bonus time*/
void power_time (object_breakout *platform, object_breakout *ball, int nb_ball, 
                 object_breakout *tab, int *n, SDL_Surface *screen);

/* Gives a random number between two ends to know which bonus print */
int nb_random ();



/******************************************************************************
******************************** update fonctions ****************************
 *****************************************************************************/

/*add an element in an array and initialize*/
void add (object_breakout *tab, int *n, int cx, int cy, SDL_Surface *screen,
          int type_bonus);

/*delete an element in an array*/
void del (object_breakout *tab, int *n, int cur);



/******************************************************************************
******************************** print fonctions ****************************
 *****************************************************************************/

/* draw the bakground on the screen */
void draw_background (SDL_Surface *background, SDL_Surface *screen) ;

/*  print the contents of  a table */
void print_tab (object_breakout *table, int nb,  SDL_Surface *screen);

/* print the sprite of the bonus fr the rule */
void print_sprite (SDL_Surface *sprite, float x, float y, int h, int w, 
                            SDL_Surface *screen) ;

/* print an object_breakout */
void print_object (object_breakout *object, SDL_Surface *screen);

/* print different text on the screen */
void print_text (const char *text, int val, SDL_Surface *screen, int pos_x, 
                 int pos_y, int size, int select) ;

/* print the name of the player */
void print_name (SDL_Surface *screen, SDL_Surface *background,  char *name);

/* print the ranking of the game */
void ranking (SDL_Surface *screen, SDL_Surface *background,
              int score_player, int win) ;


#endif
