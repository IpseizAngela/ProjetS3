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
    SDL_EnableKeyRepeat(10, 10);

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
				  screen,-1);
      
      /* initialization of the ball */
      object_breakout ball [MAX_SIZE];
      ball[0] = init_object (BALL, platform.position.x + 
		      (PLATFORM_WIDTH / 3), platform.position.y -      
		      (PLATFORM_HEIGHT), screen,-1);
      int nb_ball = 1;
      
      ball[0].life = life;
      ball[0].score = score;
      
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
        
      int i;
      
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
      int nbV = 0;
      int nbVI = 0;
      int nbVII = 0;
      int nb_bonus = 0;
//       printf( " - ball life = %d\n", ball[0].life);
      read_table (tab_brick, Tab, &x, &y, row, col, &nbI, &nbII, &nbIII, &nbIV, &nbV, &nbVI, &nbVII, screen);
    
      while (!gameover && !finish_level)
      {
	//look if the level is finished  
	finish_level = (nbI == 0) && (nbII == 0) && (nbIII == 0) && (nbV == 0) && (nbVI == 0) && (nbVII == 0); 
	gameover = ball[0].life <= 0;
	
	SDL_Event event;

	/* look for an event; possibly update the position and the shape
	* of the sprite. */
	if (SDL_PollEvent(&event)) {
	    
	    HandleEvent(event, &gameover,
		&platform, &throw, &ball[0], &finish_level);
	}
	
	move_plat (&platform);
	
	/* collide with edges of screen */
	collide_screen (&platform);
	    
	/* see if the content of the table is in collide with the ball */
	object_breakout tab_bonus [NB_BONUS_IN_SAME_TIME];
	float cx = 0;
	float cy = 0;
	bool blit_bonus = false;
	blit_bonus = collide_table (tab_brick, &nbI, &nbII, &nbIII, &nbIV, &nbV, &nbVI, &nbVII, ball, nb_ball, screen -> format, NB_BRICKS, &cx, &cy);  
	
	if (blit_bonus) {
	  power (tab_bonus, &nb_bonus, screen, cx, cy);
	  blit_bonus = false;
	}
	
	collide_power (&platform, tab_bonus, ball, &nb_ball, screen,&nb_bonus, &gameover);
	move_power (tab_bonus, &nb_bonus);
	power_time (&platform, ball, nb_ball, tab_bonus, &nb_bonus, screen);

	
	collide_platform (&platform, ball,  nb_ball, screen->format); 

	/* draw the background */
	draw_background (background, screen);

	/*draw all the object breakout */     
	print_tab(tab_brick[0], nbI,  screen);
	print_tab(tab_brick[1], nbII, screen);
	print_tab(tab_brick[2], nbIII, screen);
	print_tab(tab_brick[3], nbIV, screen);
	print_tab(tab_brick[4], nbV, screen);
	print_tab(tab_brick[5], nbVI, screen);
        print_tab(tab_brick[6], nbVII, screen);
	print_object (&platform, screen);
	for (i=0; i<nb_ball; i++) {
	  print_object (&ball[i], screen);
	}
	for (i=0; i<nb_bonus; i++) {
	  if (!tab_bonus[i].activate){
	    print_object(&tab_bonus[i], screen);
	  }
	}

	/* if we don't have throw the ball, we put it in the middle of the platform
	 * else we move the ball */
	if (!throw) {
	  ball[0].x =  platform.position.x + (PLATFORM_WIDTH / 3);
	  ball[0].position.x = ball[0].x;
	} 
	else {
	  move_ball (ball, &nb_ball, &platform, tab_bonus, &nb_bonus, screen, &throw);
	}

	/* draw the text on the screen */
	score = 0;
	print_text ("Life : ", ball[0].life, screen, 0, 25, 20, 0);
	for (i=0; i<nb_ball; i++) {
	  score += ball[i].score;
	}
	print_text ("Score : ", score, screen, 0, 0, 20, 0);

	/* update the screen */
  	SDL_UpdateRect(screen, 0, 0, 0, 0);
	  
      }

      life = ball[0].life;
      //score = ball.score;
      
      char cursor = fgetc(file);
      if (gameover) {
	exit = 1;
	lose (&exit, &gameover, screen, background, file, score);
	life = 3;
	score = 0;
      }
      else if (cursor == EOF) {
	exit = 1;
	win (&exit, &finish_level, screen, background,file, score);
	life = 3;
	score = 0;
      }
      finish_level = 0;
    
      /* clean up */
      for (i=0; i<row; i++) {
	  free(Tab[i]);
      }          
      free(Tab);
  
      for ( i=0; i<nbI; i++) {
	SDL_FreeSurface (tab_brick[0][i].sprite);
      }
      for ( i=0; i<nbII; i++) {
	SDL_FreeSurface (tab_brick[1][i].sprite);
      }
      for ( i=0; i<nbIII; i++) {
	SDL_FreeSurface (tab_brick[2][i].sprite);
      }
      for ( i=0; i<nbIV; i++) {
	SDL_FreeSurface (tab_brick[3][i].sprite);
      }
      
      for (i=0; i<NB_BRICKS; i++) {
	free(tab_brick[i]);
      }
      free(tab_brick); 

      SDL_FreeSurface (platform.sprite);

    }   
    fclose (file);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(background);
    SDL_Quit();
    TTF_Quit();

    return 0;
}

//Ligne de commande : gcc -Wall -g -std=c99 sdlanim.c `sdl-config --cflags --libs` -o sdlanim  -> le make fonctionne 

