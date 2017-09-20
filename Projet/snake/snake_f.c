//snake_f.c
#include "snake_f.h"

/************  Initialize sprite  *****************/
void sprite_init (sprite_t *sprite, SDL_Surface *sprite_picture,
		  int sprite_size_w, int sprite_size_h, float x,
		  float y, float ax, float ay,
		  float current_frame, int num_frame){
  sprite->x = x;
  sprite->y = y;
  sprite->ax = ax;
  sprite->ay = ay;
  sprite->picture = sprite_picture;
  sprite->size_w = sprite_size_w;
  sprite->size_h = sprite_size_h;
  sprite->current_frame = current_frame;
  sprite->num_frame = num_frame;
}

/************  Handle the player control  *****************/
void player_control (SDL_Event event, int *quit, sprite_t *player){
  switch (event.type){
  case SDL_QUIT:
    *quit = 1;
    break;
  
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_q:
      *quit = 1;
      break;
    case SDLK_LEFT:
      sprite_turn_left(player);
      break;
    case SDLK_RIGHT:
      sprite_turn_right(player);
      break;
    default:
      break;
    }
    break;
  }
}
/*****************  Handle the sprite left rotation  ***********************/
void sprite_turn_left(sprite_t *sprite);
{
  sprite->current_frame = sprite->current_frame + 0.5;
  while (sprite->current_frame >= sprite->num_frame){
    sprite->current_frame -= sprite->num_frame;
  }
}

/*****************  Handle the sprite right rotation  ***********************/
void sprite_turn_right(sprite_t *sprite){
  sprite->current_frame = sprite->current_frame - 0.05;
  while (sprite->current_frame < 0){
    sprite->current_frame += sprite->num_frame;
  }
}

/**************  Initialization of list   ****************/
liste Init(){
  liste *L = malloc(sizeof(*L));/*Allocation of memory for a list*/
  element *elem = malloc(sizeof(*elem));/*Allocation of memory for 
					  the first element*/
  if (L == NULL || elem == NULL){/*Look if the allocation work*/
    exit(EXIT_FAILURE);
  }
  elem->content = 0;
  elem->next = NULL;
  L->first = elem;
  return L;
}

/********  Insertion of a element in the list  ********/
liste insert(liste L, int elem){
  element *new = malloc(sizeof(*new));
  if (new == NULL){/*Look if the allocation work*/
    exit(EXIT_FAILURE);
  }
  new->content = elem;
  new->next = L->first;/*new pointed on the first element of the list*/
  L->first = new;/*new become the first element*/
}

/*********  Delete the first element of the list  *********/
liste delete(liste L){
  if (L == NULL){
    exit(EXIT_FAILURE);
  }else{
    element *del = L->first;
    L->first = liste->first->next;/*The second element of the list 
				    become the first element */
    free(del);
  }
}

/*********************  Delete the list  ********************/
liste eraseL(liste L){
  while (L->first != NULL){
    element *del = L->
