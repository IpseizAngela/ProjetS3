#include "Object_breakout.h"

/*************************  Management of keyboard key **************/
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

/**********  Count how many row and columns have in data file  ***************/
void count_dimension(FILE *file, int *row, int *col){
  char cursor;
  bool end = fasle;
  while (cursor != EOF){
    while (cursor != "\n" && !end){
      cursor = fgetc(file);/*read character*/
      col++;/*Count how many character have on one row*/
    }
    end = true;/*To count row and not sum columns*/
    cursor = fgetc(file);/*read character*/
    row++;/*Count how many \n have in file*/
  }
}