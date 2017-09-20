//snake_f.h
#ifndef SNAKE_F_H //For the include of that file just include one time
#define SNAKE_F_H

/**************************************************************
 *********  Feature of all functions and structure  ***********
 *************************************************************/
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_W 1024
#define SCREEN_H 800

/************  Creation of type list  *************/

typedef struct Element element;
struct Element{
int content;
Element *next;
};

typedef struct Liste liste;
struct Liste{
element *first;
};

/*************  Structure of different sprite  ************/

typedef struct Sprite_t sprite_t;
struct Sprite_t{
/*Position of sprite in game*/
float x;
float y;
/*Acceleration of sprite*/
float ax;
float ay;
/*Picture of sprite*/
SDL_Surface *picture;
/*Resolution of picture*/
int size_h;
int size_w;
/*Picture use*/
float current_fr ame;
/*Total of picture*/
int num_frame;
};

/************  Initialization of all sprites  ****************/
extern void sprite_init (sprite_t *sprite, SDL_Surface *sprite_picture,
			 int sprite_size_w, int sprite_size_h, float x,
			 float y, float ax, float ay,
			 float current_frame, int num_frame);

/*************  Handle the sprite rotation  **************/
extern void sprite_turn_left(sprite_t *sprite);
extern void sprite_turn_right(sprite_t *sprite);

/**************  Initialization of list   ****************/
extern Liste *initialization();
