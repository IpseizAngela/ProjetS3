#include <SDL.h>
#include <stdio.h>
#include "object_breakout.h"

int main(int argc, char* argv[])
{
    SDL_Surface *screen, *background;

    /* initialize SDL and SDL_ttf */
    SDL_Init (SDL_INIT_VIDEO);
    TTF_Init ();

    /* set the title bar */
    SDL_WM_SetCaption("Breakout", "SDL Animation");
    
    /* set keyboard repeat */
    //SDL_EnableKeyRepeat(10, 10);

    /* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    
    /* load background */
    background = load ("bg.bmp");
    
    /*open the data file */
    //declaration of the file
    FILE* file = NULL;   
    //to open the data file
    file = fopen("breakout_data.txt","r");  
    
    int life = 3;
    int score = 0;
    
    //make turn the game while we don't have lose or we don't have do all the level
    int exit = 0;
    //play in the current level while we don't have lose and the level is not finished
     int gameover = 0;      
    int finish_level = 0; 
 
    menu (&exit, screen, background);
     
    while ( !exit ) 
    {

      /* initialize and set the platform position in the middle of the window */
      object_breakout platform = init_object (PLAT,
				  (SCREEN_WIDTH - PLATFORM_WIDTH) / 2, 
				  SCREEN_HEIGHT - (2 * PLATFORM_HEIGHT),
				  screen);
      
      /* initialization of the ball */
      object_breakout ball = init_object (5, platform.position.x + 
		      (PLATFORM_WIDTH / 3), platform.position.y -      
		      (PLATFORM_HEIGHT), screen);
      
      ball.life = life;
      ball.score = score;
      
      //number of rows and columns
      int row;    
      int col;
      /*initialisation of row and col (1 because in the function we forget the \n) */
      row = 0;    
      col = 1;
      
      //number of charactere meet by the cursor for the fseek
      int nb_char = 0;  
	    
      //count the dimension of the current level in the data file for the data table
      count_dimension(file, &row, &col, &nb_char);   

      fseek (file, -nb_char + 1, SEEK_CUR);
      
      char ** Tab = read_data(file, row, col);
      
      //usefull for some things during the game
      int i,j;   
  
      /*print the contents of the data tab */
      for(i=0;i<row;i++){
	  for(j=0;j<col;j++){
	      printf(" %c", Tab[i][j]);
	  } 
      }
      
      //creation of the table of brick
      object_breakout ** tab_brick = alloc(NB_BRICKS, (row * col) ) ; 
      
      //it's false while we dont have throw the ball
      bool throw = false;  
      
      //coordinates of the first brick to print in x and y
      float x = 0.;    
      float y = 50.;    
      
      //number of bricks of type 1, 2, 3, 4 in the table
      int nbI = 0;        
      int nbII = 0;        
      int nbIII = 0;      
      int nbIV = 0;        
      
      read_table (tab_brick, Tab, &x, &y, row, col, &nbI, &nbII, &nbIII, &nbIV, screen);
    
      while (!gameover && !finish_level)
      {
	//look if the level is finished  
	finish_level = (nbI == 0) && (nbII == 0) && (nbIII == 0);   
	gameover = ball.life <= 0;
	
	SDL_Event event;

	/* look for an event; possibly update the position and the shape
	* of the sprite. */
	if (SDL_PollEvent(&event)) {
	    
	    HandleEvent(event, &gameover,
		&platform, &throw, &ball, &finish_level);
	}
	
	move_plat (&platform);
	
	/* if we don't have throw the ball, we put it in the middle of the platform
	* else we move the ball */
	if (!throw) {
	    ball.x =  platform.position.x + (PLATFORM_WIDTH / 3);
	    ball.position.x = ball.x;
	} 
	else {
	    move_ball (&ball, &platform, screen, &throw);
	}

	/* collide with edges of screen */
	collide_screen (&platform);
	    
	/* see if the content of the table is in collide with the ball */
	collide_table (tab_brick, &nbI, &nbII, &nbIII, &nbIV, &ball, screen -> format, NB_BRICKS);  
	collide_platform (&platform, &ball, screen->format); 

	/* draw the background */
	draw_background (background, screen);

	/*draw all the object breakout */     
	print_tab(tab_brick[0], nbI,  screen);
	print_tab(tab_brick[1], nbII, screen);
	print_tab(tab_brick[2], nbIII, screen);
	print_tab(tab_brick[3], nbIV, screen);
	print_object (&platform, screen);
	print_object (&ball, screen);
	
	/* draw the text on the screen */
	print_text ("Life : ", ball.life, screen, 0, 25, 20);
	print_text ("Score : ", ball.score, screen, 0, 0, 20);

	/* update the screen */
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	  
      }

    life = ball.life;
    score = ball.score;
      /* clean up */
      for (i=0; i<row; i++) {
	  free(Tab[i]);
      }
  
      char cursor = fgetc(file);
      if (gameover) {
        life = 3;
        score = 0;
	exit = 1;
        lose (&exit, &gameover, screen, background, file);
      }
      else if (cursor == EOF) {
        life = 3;
        score = 0;
	exit = 1;
	win (&exit, &finish_level, screen, background,file);
      }
      finish_level = 0;
    
      free(Tab);
    }   
    //SDL_FreeSurface(platform);
    SDL_FreeSurface(background);
    SDL_Quit();
    TTF_Quit();

    return 0;
}

//Ligne de commande : gcc -Wall -g -std=c99 sdlanim.c `sdl-config --cflags --libs` -o sdlanim  -> le make fonctionne 

