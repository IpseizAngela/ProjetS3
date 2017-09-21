//snake.c

/**************************************************************
 ***********************  Snake game   ************************
 *************************************************************/
#include <snake_f.h>

int main(){
 
  /*************  Sprite initialize  *************************/
  
  /*Player*/
  sprite_t *s_head;
  sprite_t *s_body;
  sprite_t *s_tail;
  liste player;
  
  /****************  Variable initialize  ********************/
  
  /*Position of player*/
  float head_x = 0.0;
  float head_y = 0.0;
  float body_x = ;
  /*Acceleration of player*/
  float ax = 0.0;
  float ay = 0.0;
  
  /*Size of sprite picture*/
  int snake_w = SNAKE_SIZE_W;
  int snake_h = SNAKE_SIZE_H;

  /*Total number and the current picture of sprite*/
  int n_frame = 1;
  int c_frame = 1;
  
  /*End of game*/
  bool gameover = false;

  /*Score of player*/
  int *score = 0;
  
  /* Table of char to print the score */
  //char score_tab[60] = "Score : ";
  //char gameover_tab[60] = "Gameover";
  
  /****************  Initialize of SDL  ***************/

  SDL_Surface *screen, *temp, *snake_pic, *background;
  /*background of a picture*/
  int colorkey;

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);
  /*initialize  SDL_ttf*/
  //TTF_Init();
  
  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");
  
  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  
  /*
  /*load the font
  TTF_Font *font_score = TTF_OpenFont("transamericagrad.ttf", 30);
  TTF_Font *font_gameover = TTF_OpenFont("transamericagrad.ttf", 90);

*/
  /*********  Load all image and position of player  *********/

  
  
  /* set player position in the middle of the screen */
  snake_x = (float)(SCREEN_W - SNAKE_SIZE_W)/2;
  snake_y = (float)(SCREEN_H - SNAKE_SIZE_H)/2;

  /**************  Initialization of sprites  ****************/

  sprite_init(&s_head, &head_picture, head_w, head_h, head_x,
	      head_y, head_ax, head_ay, n_frame, c_frame);
  sprite_init(&s_body, &body_picture, body_w, body_h, body_x,
	      body_y, body_ax, body_ay, n_frame, c_frame);
  sprite_init(&s_tail, &tail_picture, tail_w, tail_h, tail_x,
	      tail_y, tail_ax, tail_ay, n_frame, c_frame);
  /*************  Loop where the game run  *******************/
  while (!gameover){
    /******* Handle event ******/
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      player_control(event, &gameover,&snake);
    }
    
    /******  Handle collision of snake with screen  *********/
    if (ship_x < 0.0){
      gameover = false;
    }
    if(ship_x > SCREEN_WIDTH - SPRITE_SIZE){ 
      gameover = false;
    }
    if (ship_y < 0.0){
      gameover = false;
    }
    if (ship_y > SCREEN_HEIGHT - SPRITE_SIZE){ 
      gameover = false;
    }

    /* draw the background */
    SDL_BlitSurface(background, NULL, screen,NULL);
    /*
    if(!gameover){
      snprintf(gameover_tab, 90, "Game over");
      SDL_BlitSurface(t_gameover, NULL, screen, &gameover_position);
    }
    */
    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);
    //SDL_FreeSurface(t_gameover);
  }
  /*
  TTF_CloseFont(font_score);
  TTF_CloseFont(font_gameover);*/
}






/*Tableau/file capturant toutes les positions lorsque la tete change de "dir" et lorsque la queue touche cette position on l'efface*/
/*carte = tableau d'entier la case tete=1, corps=2, 
