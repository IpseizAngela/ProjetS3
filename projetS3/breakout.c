#include <SDL.h>
#include <stdio.h>
#include "object_breakout.h"

/* Size of the window */
#define SCREEN_WIDTH  1016
#define SCREEN_HEIGHT 792
/* Size of the background texture picture */
#define BG_WIDTH  254
#define BG_HEIGHT 198


/* Size of the platform: */
#define PLATFORM_WIDTH  64
#define PLATFORM_HEIGHT 16
/* Order of the different directions in the picture: */
//#define DIR_UP          0
#define DIR_RIGHT       1          //pas sûre d'en avoir besoin
//#define DIR_DOWN        2
#define DIR_LEFT        3          //idem

/* Number of pixels for one step of the sprite */
//#define SPRITE_STEP     5          //idem


int main(int argc, char* argv[])
{
    SDL_Surface *screen, *temp, *platform, *background;
    int colorkey;

    /* Information about the current situation of the sprite: */
    //int currentDirection = DIR_RIGHT;
    /* Walking in a direction is animated with 2 images; we use a boolean
     * that we flip after each movement to show them in turn and create
     * the illusion */
    //int animationFlip = 0;

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
    printf("\n");

    fclose(file);
    
    int gameover = 0;

    /* main loop: check events and re-draw the window until the end */
    while (!gameover)
    {
        SDL_Event event;

        /* look for an event; possibly update the position and the shape
         * of the sprite. */
        if (SDL_PollEvent(&event)) {
            HandleEvent(event, &gameover,
                   &platformPosition);
        }

        /* collide with edges of screen */
        if (platformPosition.x <= 0) {
            platformPosition.x = 0; }
        if (platformPosition.x >= SCREEN_WIDTH - PLATFORM_WIDTH)  {
            platformPosition.x = SCREEN_WIDTH - PLATFORM_WIDTH; }

       /* if (spritePosition.y <= 0)
            spritePosition.y = 0;
        if (spritePosition.y >= SCREEN_HEIGHT - SPRITE_SIZE) 
            spritePosition.y = SCREEN_HEIGHT - SPRITE_SIZE;*/
       
       
  

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
      //  {
            /* Define the source rectangle for the BlitSurface */
            SDL_Rect platformImage;
            platformImage.y = 0;
            platformImage.w = PLATFORM_WIDTH;
            platformImage.h = PLATFORM_HEIGHT;
            /* choose image according to direction and animation flip: */
            platformImage.x = PLATFORM_HEIGHT / 10; //SPRITE_SIZE*(2*currentDirection + animationFlip);

            SDL_BlitSurface(platform, &platformImage, screen, &platformPosition);
      //  }


        /* update the screen */
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }

    /* clean up */
    SDL_FreeSurface(platform);
    SDL_FreeSurface(background);
    SDL_Quit();

    return 0;
}

//Ligne de commande : gcc -Wall -g -std=c99 sdlanim.c `sdl-config --cflags --libs` -o sdlanim  -> le make fonctionne 

