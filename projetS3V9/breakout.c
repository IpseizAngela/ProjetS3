
#include <SDL.h>
#include <stdio.h>
#include "object_breakout.h"
//#include "object_breakout.h"



int main(int argc, char* argv[])
{
    SDL_Surface *screen, *temp,*background;
    //int colorkey;
  

    /* Rectangle to store the position of the sprite in the window.
     * Only the x and y coordinates are used. */
    //SDL_Rect platformPosition;
		

    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO);

    /* set the title bar */
    SDL_WM_SetCaption("SDL Animation", "SDL Animation");

    /* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    /* set keyboard repeat */
    SDL_EnableKeyRepeat(10, 10);
    

    /* load platform */
    /*temp   = SDL_LoadBMP("NormalPlatform.bmp");
    platform = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);*/

 

    /* setup sprite colorkey and turn on RLE */
    /*colorkey = SDL_MapRGB(screen->format, 238, 21, 225);
    SDL_SetColorKey(platform, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey); */

    /* load background */
    /*temp  = SDL_LoadBMP("bg.bmp");
    background = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);*/
    background = load ("bg.bmp");

    /* set platform position in the middle of the window */
    /*platformPosition.x = (SCREEN_WIDTH - PLATFORM_WIDTH) / 2;
    platformPosition.y = SCREEN_HEIGHT - (2 * PLATFORM_HEIGHT);*/
    FILE* file = NULL;                    //declaration of the file
    file = fopen("breakout_data.txt","r");  //to open the data file
    
    int exit = 0;
     
    while ( !exit ) 
    {
    
    /* initialization of the ball */
     object_breakout platform = init_object (PLAT,
		                 (SCREEN_WIDTH - PLATFORM_WIDTH) / 2, 
		                 SCREEN_HEIGHT - (2 * PLATFORM_HEIGHT),
		                 screen);
     
    object_breakout ball = init_object (5, platform.position.x + 
                       (PLATFORM_WIDTH / 3), platform.position.y -      (PLATFORM_HEIGHT), screen);
    

    int row;                 //number of rows and columns
    int col;
    row = 0;                           //initialisation of row
    col = 1;                           /*intialisation of col (1 because 
    					   in the function we forget the \n) */


    count_dimension(file, &row, &col);

    //rewind(file);
    fseek (file, - row*col, SEEK_CUR);
    
    char ** Tab = read_data(file, row, col);
    
    
    
    int i,j;
    
    for(i=0;i<row;i++){
      for(j=0;j<col;j++){
	printf(" %c", Tab[i][j]);
      } 
    }
    
    object_breakout ** tab_brick = alloc(3, (row * col) ) ;    //creation of the table of brick
    bool throw = false;  //it's false while we dont have throw the ball
    
    float x = 0.;    //coordinates of the first brick to print in x
    float y = 0.;    //and y
    
    
    int nbI = 0;        //number of bricks in the table
    int nbII = 0;
    int nbIII = 0;
    
    read_table (tab_brick, Tab, &x, &y, row, col, &nbI, &nbII, &nbIII,  screen);
    
    int gameover = 0;
    int finish_level = 0;

    /* main loop: check events and re-draw the window until the end */
    while (!gameover && !finish_level)
    {
	  finish_level = (nbI == 0) && (nbII == 0) && (nbIII == 0);
      
        SDL_Event event;

        /* look for an event; possibly update the position and the shape
         * of the sprite. */
        if (SDL_PollEvent(&event)) {
	    
            HandleEvent(event, &gameover,
                   &platform, &throw, &ball, &finish_level);
        }
        
        move_plat (&platform);
        
        if (!throw) {
            ball.x =  platform.position.x + (PLATFORM_WIDTH / 3);
	   ball.position.x = ball.x;
	} 
	else {
            move_ball (&ball);
        }

        /* collide with edges of screen */
        if (platform.position.x <= 0) {
            platform.position.x = 0; }
        if (platform.position.x >= SCREEN_WIDTH - PLATFORM_WIDTH)  {
            platform.position.x = SCREEN_WIDTH - PLATFORM_WIDTH; }
            
        /* see if the content of the table is in collide with the ball */
        collide_table (tab_brick, &nbI, &nbII, &nbIII, &ball, screen -> format, NB_BRICKS);  
        collide_platform (&platform, &ball, screen->format); 

        /* draw the background */
        for (int x = 0; x < SCREEN_WIDTH / BG_WIDTH; x++) {
            for (int y = 0; y < SCREEN_HEIGHT / BG_HEIGHT; y++) { 
                SDL_Rect position;
                position.x = x * BG_WIDTH;
                position.y = y * BG_HEIGHT;
                SDL_BlitSurface(background, NULL, screen, &position);
         }
       }
        /* Draw the selected image of the sprite at the right position */
   
            /* Define the source rectangle for the BlitSurface */
            
            /*SDL_Rect platformImage;
            platformImage.y = 0;
            platformImage.w = PLATFORM_WIDTH;
            platformImage.h = PLATFORM_HEIGHT;*/
            /* choose image according to direction and animation flip: */
            //platformImage.x = PLATFORM_HEIGHT / 10; //SPRITE_SIZE*(2*currentDirection + animationFlip);

            SDL_BlitSurface(platform.sprite, &platform.picture, screen, &platform.position);
            
            print_tab(tab_brick[0], nbI,  screen);
            print_tab(tab_brick[1], nbII, screen);
            print_tab(tab_brick[2], nbIII, screen);

	    SDL_BlitSurface(ball.sprite, &ball.picture, screen, &ball.position);

        /* update the screen */
        SDL_UpdateRect(screen, 0, 0, 0, 0);
	
    }

    /* clean up */
    for (i=0; i<row; i++) {
      free(Tab[i]);
    }
    
    if (gameover) {
      exit = 1;
    }
    
      
    free(Tab);
    }   
    //SDL_FreeSurface(platform);
    SDL_FreeSurface(background);
    SDL_Quit();

    return 0;
}

//Ligne de commande : gcc -Wall -g -std=c99 sdlanim.c `sdl-config --cflags --libs` -o sdlanim  -> le make fonctionne 

