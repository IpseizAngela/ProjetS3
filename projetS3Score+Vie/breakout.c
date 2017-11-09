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
    SDL_WM_SetCaption("SDL Animation", "SDL Animation");

    /* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    
    /* initialize the font and the color of the writing */


    /* load background */
    background = load ("bg.bmp");
    
    /*open the data file */
    FILE* file = NULL;                    //declaration of the file
    file = fopen("breakout_data.txt","r");  //to open the data file
    
    int exit = 0;  //make turn the game while we don't have lose or we don't have do all the level
     
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
        

        int row;                 //number of rows and columns
        int col;
        row = 0;                           //initialisation of row
        col = 1;                           /*intialisation of col (1 because in the function we forget the \n) */
                                            
        count_dimension(file, &row, &col);   //count the dimension of the current level in the data file for the data table

        fseek (file, - (row*col) + 1, SEEK_CUR);  //put the pointer in the begining of the current level
        
        char ** Tab = read_data(file, row, col);
        
        int i,j;    //enable for some things during the game
    
    /*print the contents of the data tab */
        for(i=0;i<row;i++){
            for(j=0;j<col;j++){
                printf(" %c", Tab[i][j]);
            } 
        }
        
        object_breakout ** tab_brick = alloc(3, (row * col) ) ;    //creation of the table of brick
        bool throw = false;  //it's false while we dont have throw the ball
        
        float x = 0.;    //coordinates of the first brick to print in x
        float y = 0.;    //and y
        
        
        int nbI = 0;        //number of bricks of type 1 in the table
        int nbII = 0;        //number of bricks of type 2 in the table
        int nbIII = 0;       //number of bricks of type 3 in the table
        
        read_table (tab_brick, Tab, &x, &y, row, col, &nbI, &nbII, &nbIII,  screen);
        
        int gameover = 0;      //play in the current level while we don't have lose...
        int finish_level = 0;     //... and the level is not finished
        printf ("nbi %d , nbii %d nbiii %d \n", nbI, nbII, nbIII);
        while (!gameover && !finish_level)
        {
            finish_level = (nbI == 0) && (nbII == 0) && (nbIII == 0);   //look if the level is finished
        
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
                move_ball (&ball);
            }

            /* collide with edges of screen */
            collide_screen (&platform);
                
            /* see if the content of the table is in collide with the ball */
            collide_table (tab_brick, &nbI, &nbII, &nbIII, &ball, screen -> format, NB_BRICKS);  
            collide_platform (&platform, &ball, screen->format); 

            /* draw the background */
            draw_background (background, screen);

           /*draw all the object breakout */     
            print_tab(tab_brick[0], nbI,  screen);
            print_tab(tab_brick[1], nbII, screen);
            print_tab(tab_brick[2], nbIII, screen);
            print_object (&platform, screen);
            print_object (&ball, screen);
            
            /* draw the text on the screen */
            print_text ("Life : ", ball.life, screen, 0, 25);
            print_text ("Score : ", ball.score, screen, 0, 0);

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
    TTF_Quit();

    return 0;
}

//Ligne de commande : gcc -Wall -g -std=c99 sdlanim.c `sdl-config --cflags --libs` -o sdlanim  -> le make fonctionne 

