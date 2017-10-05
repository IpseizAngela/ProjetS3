#include "Object_breakout.h"

int main(int argc, char* argv[])
{
    SDL_Surface *screen, *temp, *platform, *background;
    int colorkey;

    /* Rectangle to store the position of the sprite in the window.*/
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


        /* update the screen */
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }

    /* clean up */
    SDL_FreeSurface(platform);
    SDL_FreeSurface(background);
    SDL_Quit();

    return 0;
}
