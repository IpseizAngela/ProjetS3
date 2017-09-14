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
