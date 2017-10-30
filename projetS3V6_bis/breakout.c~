
#include <SDL.h>
#include <stdio.h>
#include "object_breakout.h"
//#include "object_breakout.h"



int main(int argc, char* argv[])
{
    SDL_Surface *screen, *temp, *platform, *background;
    int colorkey;
  

    /* Rectangle to store the position of the sprite in the window.
     * Only the x and y coordinates are used. */
    SDL_Rect platformPosition;


    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO);

    /* set the title bar */
    SDL_WM_SetCaption("SDL Animation", "SDL Animation");

    /* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    /* set keyboard repeat */
    SDL_EnableKeyRepeat(10, 10);

    /* load platform */
    temp   = SDL_LoadBMP("NormalPlatform.bmp");
    platform = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

 

    /* setup sprite colorkey and turn on RLE */
    colorkey = SDL_MapRGB(screen->format, 238, 21, 225);
    SDL_SetColorKey(platform, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    /* load background */
    temp  = SDL_LoadBMP("bg.bmp");
    background = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    /* set platform position in the middle of the window */
    platformPosition.x = (SCREEN_WIDTH - PLATFORM_WIDTH) / 2;
    platformPosition.y = SCREEN_HEIGHT - (2 * PLATFORM_HEIGHT);
    
    /* initialization of the ball */
    object_breakout ball = init_object (5, platformPosition.x + 
                       (PLATFORM_WIDTH / 3), platformPosition.y - (PLATFORM_HEIGHT), screen);
    

    int row;                 //number of rows and columns
    int col;
    row = 0;                           //initialisation of row
    col = 1;                           /*intialisation of col (1 because 
    					   in the function we forget the \n) */

    FILE* file = NULL;                    //declaration of the file
    file = fopen("breakout_data.txt","r");  //to open the data file
  
    count_dimension(file, &row, &col);

    rewind(file);
    
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

    /* main loop: check events and re-draw the window until the end */
    while (!gameover)
    {
	
      
        SDL_Event event;

        /* look for an event; possibly update the position and the shape
         * of the sprite. */
        if (SDL_PollEvent(&event)) {
            HandleEvent(event, &gameover,
                   &platformPosition, &throw, &ball);
        }
        
        if (!throw) {
            ball.x =  platformPosition.x + (PLATFORM_WIDTH / 3);
	   ball.position.x = ball.x;
	} 
	else {
            move_ball (&ball);
        }

        /* collide with edges of screen */
        if (platformPosition.x <= 0) {
            platformPosition.x = 0; }
        if (platformPosition.x >= SCREEN_WIDTH - PLATFORM_WIDTH)  {
            platformPosition.x = SCREEN_WIDTH - PLATFORM_WIDTH; }
            
        /* see if the content of the table is in collide with the ball */
        collide_table (tab_brick, &nbI, &nbII, &nbIII, &ball, screen -> format, 3);  

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
            SDL_Rect platformImage;
            platformImage.y = 0;
            platformImage.w = PLATFORM_WIDTH;
            platformImage.h = PLATFORM_HEIGHT;
            /* choose image according to direction and animation flip: */
            platformImage.x = PLATFORM_HEIGHT / 10; //SPRITE_SIZE*(2*currentDirection + animationFlip);

            SDL_BlitSurface(platform, &platformImage, screen, &platformPosition);
            
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
    free(Tab);
    
    SDL_FreeSurface(platform);
    SDL_FreeSurface(background);
    SDL_Quit();

    return 0;
}

//Ligne de commande : gcc -Wall -g -std=c99 sdlanim.c `sdl-config --cflags --libs` -o sdlanim  -> le make fonctionne 

