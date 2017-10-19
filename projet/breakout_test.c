#include "object_breakout.h"


int main(int argc, char* argv[])
{
  SDL_Surface *screen, *platform, *background;
    int colorkey;

    /* Rectangle to store the position of the sprite in the window.
     * Only the x and y coordinates are used. */
    SDL_Rect platformPosition;

    //coordinates of the first brick to print in x
    float x = 0.0;
    //and y
    float y = 0.0;
    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO);

    /* set the title bar */
    SDL_WM_SetCaption("SDL Animation", "SDL Animation");

    /* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    /* set keyboard repeat */
    SDL_EnableKeyRepeat(10, 10);

    /* load platform */
    platform = load("NormalPlatform.bmp");

    /* setup sprite colorkey and turn on RLE 
    colorkey = SDL_MapRGB(screen->format, 238, 21, 225);
    SDL_SetColorKey(platform, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);*/
    set_colorkey(screen, 238,21,225,platform);

    /* load background */
    background = load("bg.bmp");

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
    int nbI;
    int nbII;
    int nbIII;
    int i,j,ii,jj;
    
    for(i=0;i<row;i++){
      for(j=0;j<col;j++){
	printf(" %c", Tab[i][j]);
      }
    }

    fclose(file);
    
    int gameover = 0;
    object_breakout **tab_brick;
    tab_brick = alloc(3,row * col);
    /* main loop: check events and re-draw the window until the end */
    /*
    while (!gameover)
    {
      
      nbI = 0;
      nbII = 0;
      nbIII = 0;
      for (i=0; i<row; i++) {
	for (j=0; j<col; j++) {
	  if ( Tab[i][j] == '1' ) {
	    tab_brick[0][nbI] = init_object (1, x, y);
	    x += tab_brick[0][nbI].width;
	    nbI ++;
	  }
	  else {
	    if ( Tab[i][j] == '2' ) {
	      tab_brick[1][nbII] = init_object (2, x, y);
	      x += tab_brick[1][nbII].width;
	      nbII ++;
	    }
	    else { 
	      if ( Tab[i][j] == '3' ) {
		tab_brick[2][nbIII] = init_object (3, x, y);
		x += tab_brick[2][nbIII].width;
		nbIII ++;
	      }
	      else {
		if ( Tab[i][j] == '\n') {
		  x = 0;
		  y += DEFAULT_HEIGHT;
		}
		else {
		  x += DEFAULT_WIDTH;
		}
	      }
	    }
	  }
	}
      }
      x = 0.;
      y = 0.;
      
      SDL_Event event;
      
      /* look for an event; possibly update the position and the shape
       * of the sprite. 
      if (SDL_PollEvent(&event)) {
	HandleEvent(event, &gameover,
		    &platformPosition);
      }

      /* collide with edges of screen 
      if (platformPosition.x <= 0) {
	platformPosition.x = 0; }
      if (platformPosition.x >= SCREEN_WIDTH - PLATFORM_WIDTH) {
	platformPosition.x = SCREEN_WIDTH - PLATFORM_WIDTH; 
      }
      
      /* draw the background 
      for (ii = 0; ii < SCREEN_WIDTH / BG_WIDTH; ii++) {
	for (jj = 0; jj < SCREEN_HEIGHT / BG_HEIGHT; jj++) { 
	  SDL_Rect position;
	  position.x = ii * BG_WIDTH;
	  position.y = jj * BG_HEIGHT;
	  SDL_BlitSurface(background, NULL, screen, &position);
	}
      }

      /* Draw the selected image of the sprite at the right position 
      /* Define the source rectangle for the BlitSurface 
      SDL_Rect platformImage;
      platformImage.y = 0;
      platformImage.w = PLATFORM_WIDTH;
      platformImage.h = PLATFORM_HEIGHT;
      /* choose image according to direction and animation flip: 
      platformImage.x = PLATFORM_HEIGHT / 10; //SPRITE_SIZE*(2*currentDirection + animationFlip);
      
      SDL_BlitSurface(platform, &platformImage, screen, &platformPosition);
      //int i;
      for (i=0; i<nbI; i++) {
	SDL_BlitSurface(tab_brick[0][i].sprite, &tab_brick[0][i].picture, screen, &tab_brick[0][i].position);
      }
      for (i=0; i<nbII; i++) {
	SDL_BlitSurface(tab_brick[1][i].sprite, &tab_brick[1][i].picture, screen, &tab_brick[1][i].position);
      }
      for (i=0; i<nbIII; i++) {
	SDL_BlitSurface(tab_brick[2][i].sprite, &tab_brick[2][i].picture, screen, &tab_brick[2][i].position);
      }
      
      /* update the screen 
      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
      */    

    /* clean up*/ 
    /*free columns per row*/
    for(i=0;i<row;i++){
      free(Tab[i]);
    }
    free(Tab);
    for(i=0;i<3;i++){
      free(tab_brick[i]);
    }
    free(tab_brick);
    SDL_FreeSurface(platform);
    SDL_FreeSurface(background);
    SDL_FreeSurface(screen);
    SDL_Quit();
    
    return 0;
}
