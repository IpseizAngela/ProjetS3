#include "object_breakout.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



/******************************************************************************
************************** handle_event fonctions ***************************
 *****************************************************************************/

/************** management of keyboard keys for the menu ************/
void handle_event_menu (SDL_Event event_menu, int *exit, int *begin, 
                        int *play,  int *enter_in_rule, int *credit, int *quit)  
 {
  switch (event_menu.type) {
    /*quit the game*/
    case SDL_QUIT:
      *begin = 1;
      *exit = 1;
      break;
			  
    /* the event is a touch of keyboard*/
    case SDL_KEYDOWN:
      switch (event_menu.key.keysym.sym) {
        /*quit the menu*/
        case SDLK_ESCAPE:
        case SDLK_q:
            *begin = 1;
            *exit = 1;
            break;
         
        /* choose what do*/    
        case SDLK_DOWN:
            /*if the play button is red*/
            if (*play) {
                /*put the play button in black*/
                *play = 0;
                /*and the rule button in red*/
                *enter_in_rule = 1;
            /*if the rule button is red*/
            } else if (*enter_in_rule) {
                /*put the rule button in black*/
                *enter_in_rule = 0;
                /*and the credit button in red*/
                *credit = 1;
            /*if the credit button is red*/
            } else if (*credit) {
                /*put the credit button in black*/
                *credit = 0;
                /*and the quit button in red*/
                *quit = 1;
            /*if the quit button is red*/
            } else {
                /*put the quit button in black*/
                *quit = 0;
                /*and the play button in red*/
                *play = 1;
            }
            break;
       
        /*like the SDLK_DOWN in reverse*/
        case SDLK_UP:
            if (*play) {
                *play = 0;
                *quit = 1;
            } else if (*enter_in_rule) {
                *enter_in_rule = 0;
                *play= 1;
            } else if (*credit) {
                *credit = 0;
                *enter_in_rule = 1;
            } else {
                *quit = 0;
                *credit = 1;
            }
            break;
       
        /*choose a menu or begin the game*/
       case SDLK_RETURN:
           *begin = 1;
            break; 
            
        default:
            break;				
            
      }
      break;
  }
}

/************** management of keyboard keys for the rules menu ************/
void handle_event_rule (SDL_Event event_rule, int *quit_rule, int *second_r, 
                        int rule_curr, int *go_out)
 {
     switch (event_rule.type) {
        /*quit the game*/
        case SDL_QUIT:
            * quit_rule = 1;
            *go_out = 1;
            break;
        
        case SDL_KEYDOWN :
            switch (event_rule.key.keysym.sym) {
                /*quit the menu*/
                case SDLK_ESCAPE :
                case SDLK_q:
                    *quit_rule = 1;
                    
                /*you chose*/    
                case SDLK_RETURN:
                    /*quit the menu*/
                    *quit_rule =  1;
                    break;
                
                /*press the right arrow*/
                case SDLK_RIGHT:
                    /*the current rule is the first rule*/
                    if (rule_curr == 0) {
                        /*put the arrow in red*/
                        *second_r = 1;
                    /*the current rule is the second rule*/
                    } else {
                        /*put the back button in red*/
                        *second_r = 0;
                    }
                    break;
               
                /*press the left arrow*/
                case SDLK_LEFT:
                     /*the current rule is the first rule*/
                    if (rule_curr == 0) {
                        /*put the back button in red*/
                        *second_r = 0;
                    /*the current rule is the second rule*/
                    } else {
                        /*put the arrow in red*/
                        *second_r = 1;
                    }
                default:
                    break;
    
            }
        default:
            break;
     }
 }
 
/************** management of keyboard keys for the credit menu ************/
void handle_event_credit (SDL_Event event_credit, int *quit, int * go_out)
{
    switch (event_credit.type) {
        /*quit the game*/
        case SDL_QUIT:
            * quit = 1;
            *go_out = 1;
            break;
            
        case SDL_KEYDOWN :
            switch (event_credit.key.keysym.sym) {
                /*quit the menu*/
                case SDLK_ESCAPE :
                case SDLK_RETURN:
                case SDLK_q:
                    *quit = 1;
                    break;

                default:
                    break;
            }
            break;
            
        default:
            break;
    }
 }
  
/************** management of keyboard keys for the break menu ************/
void handle_event_break (SDL_Event event_break, int *quit_break, int *go_out)
{
    switch (event_break.type) {
        /*quit the game*/
        case SDL_QUIT:
            *quit_break = 1;
            *go_out = 1;
            break;

        case SDL_KEYDOWN:
            switch (event_break.key.keysym.sym) {
                /*quit the menu*/
                case SDLK_p:
                case SDLK_ESCAPE:
                    *quit_break = 1;
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
             break;
    }    
}

/************** management of keyboard keys for all the game  *****************/
void HandleEvent(SDL_Event event, int *quit,  object_breakout *platform, 
                 bool *throw, object_breakout *ball, int *finish_level, int *go_out,
                 SDL_Surface *screen)
{
  switch (event.type) {
    /*quit the game*/
  case SDL_QUIT:
    *quit = 1;
    *go_out = 1;
    break;

    /* handle the keyboard */
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
        /*change the level*/
        case SDLK_ESCAPE:
        case SDLK_q:
            SDL_EnableKeyRepeat (0, 0);
            *finish_level = 1;
            /*quit the game (put after the presentation
              *quit = 1;
              * go_out = 1; */
            SDL_EnableKeyRepeat (10, 10);
            break;
            
            
        case SDLK_LEFT:
            /*the platform is slow*/
            if (platform -> activate) {
                platform->x -= SPRITE_STEP / 3;
            }
            /*the platform is speed up*/
            if (platform -> initiate) {
                platform->x -= SPRITE_STEP * 3;
            }
            /*the platform is normal*/
            if (!platform -> activate && !platform -> initiate) {
                platform->x -= SPRITE_STEP;
            }
            break;
            
        /*like the left*/    
        case SDLK_RIGHT:
            if (platform -> activate) {
                platform->x += SPRITE_STEP / 3;
            }
            if (platform -> initiate) {
                platform->x += SPRITE_STEP * 3;
            }
            if (!platform -> activate && !platform -> initiate) {
                platform->x += SPRITE_STEP;
            }
            break;
            
        /* you throw the ball*/    
        case SDLK_SPACE:
            if (!*throw) {
                ball -> speed_x = 0.;
                ball -> speed_y = -SPEEDY;
                *throw = true;
            } 
            break;
      
        /*put the break menu*/
        case SDLK_p:
            menu_break (screen, go_out);
            break;

        default:
            break;
        }
    break;
  }
}

/********* management of keyboard keys when the player must write his name *****/
void handle_event_name (SDL_Event event_name, int *end, char *name)
{
    int i = 0;
    switch (event_name.type) {
        /*quit the menu*/
        case SDL_QUIT:
            * end = 1;
            break;
        
        case SDL_KEYDOWN :
            switch (event_name.key.keysym.sym) {
                /*quit the menu*/
                case SDLK_ESCAPE :
                case SDLK_RETURN:
                    *end = 1;
                    break;
                    
                 /*write your name*/   
                case SDLK_BACKSPACE:
                    i = strlen (name);
                    if (i >0) {
                        name [i - 1] = '\0';
                    }
                    break;
                    
                case SDLK_SPACE:
                    strcat (name, " ");
                    break;
                
                case SDLK_MINUS:
                    strcat (name, "-");
                    break;
                    
                case SDLK_a :
		    strcat (name, "a");
                    break;
                case SDLK_b :
		    strcat (name, "b");
                    break;
                case SDLK_c :
		    strcat (name, "c");
                    break;
                case SDLK_d :
		    strcat (name, "d");
                    break;
                case SDLK_e :
		    strcat (name, "e");
                    break;
               case SDLK_f :
		    strcat (name, "f");
                    break;
                case SDLK_g :
		    strcat (name, "g");
                    break;
               case SDLK_h :
		    strcat (name, "h");
                    break;
                case SDLK_i :
		    strcat (name, "i");
                    break;
                case SDLK_j :
		    strcat (name, "j");
                    break;
                case SDLK_k :
		    strcat (name, "k");
                    break;
                case SDLK_l :
		    strcat (name, "l");
                   break;
                case SDLK_m :
		    strcat (name, "m");
                    break;
                case SDLK_n :
		    strcat (name, "n");
                    break;
                case SDLK_o :
		    strcat (name, "o");
                    break;
                case SDLK_p :
		    strcat (name, "p");
                    break;
                case SDLK_q :
		    strcat (name,  "q");
                    break;
                case SDLK_r :
		    strcat (name, "r");
                    break;
                case SDLK_s :
		    strcat (name,  "s");
                    break;
                case SDLK_t :
		    strcat (name, "t");
                    break;
                case SDLK_u :
		    strcat (name,  "u");
                    break;
                case SDLK_v :
		    strcat (name, "v");
                    break;
                case SDLK_w :
		    strcat (name, "w");
                    break;
                case SDLK_x :
		    strcat (name, "x");
                    break;
                case SDLK_y :
		    strcat (name,  "y");
                    break;
                case SDLK_z :
		    strcat (name,  "z");
                    break; 
                default:
                    break;
            }
            break;
    }
}

/************** management of keyboard keys for the lose menu ************/
void handle_event_lose (SDL_Event event_lose,  int *exit, int *gameover,
                        int *choose, int *replay, int *counter_level) 
 {
  switch (event_lose.type) {
    /*quit the game*/
    case SDL_QUIT:
        *choose = 1;
        break;
                            
    case SDL_KEYDOWN:
        switch (event_lose.key.keysym.sym) {
        /*quit the game*/
        case SDLK_ESCAPE:
        case SDLK_q:
        *choose = 1;
        break;
            
       /*select the replay menu*/ 
        case SDLK_LEFT:
            *replay = 1;
            break;
        
        /*select to quit*/
        case SDLK_RIGHT:
            *replay = 0;
            break;
            
        /*chose*/
        case SDLK_RETURN:
            /*the replay button is selected*/
            if (*replay ==  1) {
                /*quit the menu and replay the game*/
                *choose = 1;
                *exit = 0;
                *gameover = 0;
                *counter_level = 0;
            /*the quit button is selected*/
            } else if (*replay == 0) {
                /*quit the game*/
                *choose = 1;
            }        
        break;
                                                    
        default:
        break;				
            
        }
        break;
    }
}



  
/******************************************************************************
******************************* menu fonctions ********************************
 *****************************************************************************/
  
  /*  creation of the main menu */
void menu (int *exit, SDL_Surface *screen, SDL_Surface *background)
{
    /*put the SDL_EnableKeyRepeat at 0 fo don't repeat the key*/
    SDL_EnableKeyRepeat (0, 0);
    SDL_Event event_menu;
    /*main variable of the menu*/
    int begin = 0;
    /*for the play button*/
    int play = 1;
    /*for the rule menu*/
    int in_rule = 0;
    /*for the credit menu*/
    int credit = 0;
    /*for quit the game*/
    int quit = 0;

    draw_background (background, screen);
    print_text ("Breakout", -1, screen, 10, SCREEN_HEIGHT / 8, 190, 0);
    int i, j;
    for (i = 0; i<5; i++) {
        for (j = 0; j < 120; j++) {
            print_text("_", -1,screen, j * 5, SCREEN_HEIGHT/8 + i, 8, 2);
            print_text("_", -1,screen, 
            SCREEN_WIDTH/3 + 100 + j * 5, SCREEN_HEIGHT/8 + 200 + i, 8, 3);
        }
    }
    while (!begin)
    {
        /*if a key is pressed*/
        if (SDL_PollEvent(&event_menu)) {
            handle_event_menu (event_menu, exit, &begin, 
                               &play, &in_rule, &credit, &quit);
        } 
        /*print the button*/
        print_text ("Play", -1, screen, SCREEN_WIDTH / 3,  
                    2 * SCREEN_HEIGHT / 5, 90, play);
        print_text ("Rules", -1, screen, SCREEN_WIDTH / 3,  
                    2 * SCREEN_HEIGHT / 5 + 100, 90, in_rule);
        print_text ("Credits", -1, screen, SCREEN_WIDTH / 3,  
                    2 * SCREEN_HEIGHT / 5 + 200, 90, credit);
        print_text ("Quit", -1, screen, SCREEN_WIDTH /3 ,  
                    2 * SCREEN_HEIGHT / 5 + 300, 90, quit);
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
    /*return the enable key repeat at 10*/
    SDL_EnableKeyRepeat (10,10);
    /*if the rule button is activate when we quit the menu*/
    if (in_rule == 1) {
        rule (screen, background, exit);
    /*if the credit button is activate when we quit the menu*/
    } else if (credit == 1) {
        menu_credit (screen, background, exit);
    /*if the quit button is activate when we quit the menu*/
    } else if (quit == 1) {
        *exit = 1;
    }
    /*if the play button is selected, play the game*/

}

/* Explain the rules of the game */
void rule (SDL_Surface *screen, SDL_Surface *background, int *exit)
{
    /*the current rule menu is the first*/
    int curr = 0;
    SDL_Event event_rule;
    /*main variable of the menu*/
    int quit_rule = 0;
    /*for the second rule button (arrow)*/
    int second_rule = 0;
    /*for the back button*/
    int back = 1;
    /*coordonates of print*/
    int x = 75 ;
    int y = SCREEN_HEIGHT / 3 + 20;
    int i, j;
    
    /*print the text*/
    draw_background(background, screen);
    for (i = 0; i<5; i++) {
        for (j = 0; j < 120; j++) {
            print_text ("_", -1, screen,  j * 5,  SCREEN_HEIGHT/30 + i, 8, 2);
            print_text ("_", -1, screen, SCREEN_WIDTH/3 + 100 + j * 5,
                        SCREEN_HEIGHT / 60 + 220 + i, 8, 3);
        }
    }
    print_text("Rules", -1, screen, SCREEN_WIDTH/4, 
               SCREEN_HEIGHT/30, 190, 0);
    print_text ("* The blues and yellows bricks break with 1 hit", 
                -1, screen, x,  y, 32, 0);
    print_text ("* The greens and beiges bricks break with 2 hits",
                -1, screen, x, y + 40, 32, 0);
    print_text ("* The pinks and reds bricks break with 3 hits", -1,
                screen, x, y + 80, 32, 0);
    print_text ("* The darks brick don't break", -1, screen, x, 
                y + 120, 32, 0);
    print_text ("* The goal it's to break every bricks ", -1, screen,
                x, y + 160, 32, 0);
    print_text ("exept the darks.", -1, screen, x + 50, y + 200  , 
                32, 0);
    print_text ("* To throw the ball press the space button.", -1, 
                screen, x, y + 240, 32, 0);
    print_text ("* The platform move right and left", -1, screen, x, 
                y + 280, 32, 0);
    print_text (" with the arrows.", -1, screen, x + 50, y + 320, 
                32, 0);
    print_text ("* Press p for break.", -1, screen, x , y + 360, 
                32, 0);
    
    while (!quit_rule) {
        /*if a key is pressed*/
        if (SDL_PollEvent (&event_rule)) {
            handle_event_rule (event_rule, &quit_rule, &second_rule, 
                               curr,  exit);
        }
        /*put the right color of the button*/
        if (second_rule == 0) {
            back = 1;
        } else {
            back = 0;
        }
        /*print the button*/
        print_text ("Back", -1, screen, 50, SCREEN_HEIGHT - 70, 50, back);
        print_text ("--->", -1, screen, SCREEN_WIDTH - 150,  
                    SCREEN_HEIGHT - 70,  50, second_rule);
        
        SDL_UpdateRect (screen, 0, 0, 0, 0);
    }
    /*if we don't quit the game*/
    if (!*exit) {
        /*if the arrow is selected when we quit the menu*/
        if (second_rule)  {
            scd_rule (screen, background, exit);
        /*if the back button is selected when we qui the menu*/
        } else {
            menu (exit, screen, background);
        }
    }
}

/* Explain the functionality of the bonus */
void scd_rule (SDL_Surface *screen, SDL_Surface *background, int *exit)
{
    /*the curent menu is the secons*/
    int curr = 1;
    SDL_Event event_rule;
    /*main variable of the menu*/
    int quit_rule = 0;
    /*for the first rule button (arrow)*/
    int first_rule = 0;
    /*for the back button*/
    int back = 1;
    /*different coordonates for the print*/
    int x =30 ;
    int y_b = SCREEN_HEIGHT / 3 + 20;
    /*foot for the print*/
    int foot = 35;
    int  y = y_b - (foot * REDUC) - 15;
    
    /*print the text in the screen*/
    int i, j;
    draw_background(background, screen);
    for (i = 0; i<5; i++) {
	for (j = 0; j < 120; j++) {
	    print_text("_", -1,screen, j * 5, SCREEN_HEIGHT/30 + i, 8, 2);
	    print_text("_", -1,screen, SCREEN_WIDTH/3 + 100 + j * 5, 
                       SCREEN_HEIGHT / 60 + 220 + i, 8, 3);
	}
    }
    print_text("Rules", -1, screen, SCREEN_WIDTH/4, 
               SCREEN_HEIGHT/30, 190, 0);
    print_text ("Reduce the platform", -1, screen, x + 50, 
                y +(foot * REDUC), 32, 0);
    print_text ("Grow the platform", -1, screen, x + 50, 
                y + (foot * GROW) , 32, 0);
    print_text ("You lose immediatly the game", -1, 
                screen, x + 50, y+ (foot * LOST), 32, 0);
    print_text ("Win a life ", -1, screen, x + 50, 
                y+ (foot * LIFE), 32, 0);
    print_text ("Increase the score of 10", -1, screen, x + 50, 
                y+ (foot * SCORE), 32, 0);
    print_text ("The ball bounced at the bottom of the screen", -1, 
                screen, x + 50, y+ (foot * BOUNCE), 32, 0);
    print_text ("An other ball appears", -1, screen, x + 50,
                y+ (foot * MULTI), 32, 0);
    print_text ("Get through all the bricks", -1, screen, x + 50, 
                y+ (foot * CROSS), 32, 0);
    print_text ("Decrease the score of 5", -1, screen, x + 50,
                y+ (foot * MIN), 32, 0);
    print_text ("Slow the ball", -1, screen, x + 50,
                y+ (foot * SLOW_BALL), 32, 0);
    print_text ("Speed up the ball", -1, screen, x + 50, 
                y+ (foot * SPEED_BALL), 32, 0);
    print_text ("Slow the platform", -1, screen, x + 50, 
                y+ (foot * SLOW_PLAT), 32, 0);
    print_text ("Speed up the platform", -1, screen, x + 50,
                y+ (foot * SPEED_PLAT), 32, 0);
    
    /*print the sprite of the bonus in the screen*/
    for (i = 0; i<NB_TOTAL_BONUS; i++) {
        SDL_Surface *sprite = load_bonus (i+1);
        print_sprite (sprite, x, y_b+(foot*i), 17, 17, screen);
        /*remove the sprite its stay print while we don't draw the background*/
        SDL_FreeSurface(sprite);
    }
    
    while (!quit_rule) {
        /*if a key is pressed*/
        if (SDL_PollEvent (&event_rule)) {
            handle_event_rule (event_rule, &quit_rule, &first_rule, curr,  exit);
        }
        /*put the right color for the button*/
        if (first_rule == 1) {
            back = 0;
        } else {
            back = 1;
        }
        
        /*print the button*/
        print_text ("Back", -1, screen, SCREEN_WIDTH - 150,  
                    SCREEN_HEIGHT - 70,  50, back);
        print_text ("<---",-1, screen, 50, SCREEN_HEIGHT - 70, 50, first_rule);

        
        SDL_UpdateRect (screen, 0, 0, 0, 0);
    }
    /*if we don't exit the game*/
    if (!*exit) {
        /*if the arrow is selected*/
        if (first_rule) {
            rule (screen, background, exit);
        /*if the back button is selected*/
        } else {
            menu (exit, screen, background);
        }
    }
}

/* creation of the credit menu */
void menu_credit (SDL_Surface *screen, SDL_Surface *background, int *exit)
{
    /*main variable of the menu*/
    int quit_credit = 0;
    /*for the quit button*/
    int quit_button = 1;
    /*coordonates of the print in the screen*/
    int x = SCREEN_WIDTH / 3;
    int y = SCREEN_HEIGHT / 10;
    
    /*print of the text in the screen*/
    draw_background (background, screen);
    print_text ("A ", -1, screen, x + 80, y, 90, 0);
    print_text ("Dylan ", -1, screen, x - 20, y + 100, 90, 2);
    print_text ("and ", -1, screen, x + 30, y+ 200, 90, 0);
    print_text ("Angela ", -1, screen, x - 40, y + 300, 90, 3);
    print_text ("production ", -1, screen, x - 120, y + 400, 90, 0);
    print_text ("lien github : https://github.com/IpseizAngela/ProjetS3/branches ", 
                -1, screen, 100, y + 550, 24, 4);
    print_text ("Back", -1, screen, 50, SCREEN_HEIGHT - 70, 50, quit_button);
    
    SDL_Event event_credit;
    while (!quit_credit) {
        /*if the key is press*/
        if (SDL_PollEvent(&event_credit)) {
            handle_event_credit (event_credit, &quit_credit, exit);
        }
        SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
    /*if the back button was selected when we quit the menu*/
    if (!*exit) {
        menu (exit,screen, background);
    }
}

/* Put break during the game */
void menu_break (SDL_Surface *screen, int *go_out)
{
    /*put the enable key at 0 for no repeat the event*/
    SDL_EnableKeyRepeat(0,0);
    SDL_Event event_break;
    int quit_break = 0;
    while (!quit_break) {
        /*if is keybord is press*/
        if (SDL_PollEvent(&event_break)) {
            handle_event_break (event_break, &quit_break, go_out);
        }
        /*print the text of the menu*/
        print_text("| |", -1, screen, 3 *  SCREEN_WIDTH / 4 , 10, 90,0);
        SDL_UpdateRect (screen, 0, 0, 0, 0);
    }
    SDL_EnableKeyRepeat(10,10);
}

/******* creation of the lose menu ********/
void lose (int *exit, int *gameover, SDL_Surface *screen, 
           SDL_Surface *background,FILE *file, int score, int *counter_level)
 {
     /*main variable of the menu*/
    int choose = 0;
    /*for the replay button*/
    int replay = 1;
    /*for the quit button*/
    int quit = 0;
    
    /*print the text in the screen*/
    int i, j;
    draw_background (background, screen);
    print_text ("Game over", -1, screen, SCREEN_WIDTH / 60, 
                SCREEN_HEIGHT / 60, 170, 0);
        for (i = 0; i<5; i++) {
            for (j = 0; j < 120; j++) {
                print_text("_", -1,screen, j * 5, SCREEN_HEIGHT / 60 + i,
                           8, 2);
                print_text("_", -1,screen, SCREEN_WIDTH/3 + 100 + j * 5, 
                           SCREEN_HEIGHT / 60 + 200 + i, 8, 3);
            }
        }
        
     /*print the rank in the screen*/   
    ranking (screen, background, score, 0);
        
    while (!choose) {
        SDL_Event event_lose;
        /*if a key is pressed*/
        if (SDL_PollEvent (&event_lose)) {
            handle_event_lose (event_lose,  exit, gameover, &choose, 
                               &replay, counter_level);
        }
        /*for know which color use for the button*/
        if (replay) {
            quit = 0;
        } else {
            quit = 1;
        }
        /*print the text in the screen*/
        print_text ("Replay", -1, screen, SCREEN_WIDTH / 60,  
                    3 * SCREEN_HEIGHT / 4, 90, replay);
        print_text ("Quit", -1, screen, 2 * SCREEN_WIDTH / 3 -  50, 
                    3 * SCREEN_HEIGHT / 4, 90, quit);
        SDL_UpdateRect (screen, 0, 0, 0, 0);
    }
    /*return the cursor's file at the beginning of the file*/
    rewind (file);
}

/******* creation of the win menu ********/
void win (int *exit, int *finish_level,  SDL_Surface *screen, 
          SDL_Surface *background, FILE *file, int score, int *counter_level) 
{
    /*main variable of the menu*/
    int choose = 0;
    /*for the replay button*/
    int replay = 1;
    /*for the quit button*/
    int quit = 0;
    /*print the text in the screen*/
    int i,j;
    draw_background (background, screen);
    for (i = 0; i<5; i++) {
        for (j = 0; j < 120; j++) {
            print_text("_", -1,screen, j * 5, SCREEN_HEIGHT / 60 + i, 8, 2);
            print_text("_", -1,screen, 
                    SCREEN_WIDTH/3 + 100 + j * 5, 
                    SCREEN_HEIGHT / 60 + 200 + i, 8, 3);
        }
    }
    print_text ("Win", -1, screen, SCREEN_WIDTH / 4,
                SCREEN_HEIGHT / 60, 190, 0);
    
    /*print the rankng in the screen*/
    ranking (screen, background, score, 1);
    
    while (!choose) {
        SDL_Event event_win;
        /*if a key is pressed*/
        if (SDL_PollEvent (&event_win)) {
            handle_event_lose (event_win, exit, finish_level, &choose,
                               &replay, counter_level);
        }
        /*for print the button in the right color*/
        if (replay) {
            quit = 0;
        } else {
            quit = 1;
        }
        /*print the button in the screen*/
        print_text ("Replay", -1, screen, SCREEN_WIDTH / 60, 
                    SCREEN_HEIGHT - 100, 90, replay);
        print_text ("Quit", -1, screen, 3 * SCREEN_WIDTH / 4,  
                    SCREEN_HEIGHT - 100, 90, quit);
        SDL_UpdateRect (screen, 0, 0, 0, 0);
    }
    /*return the cursor's file at the beginning of the file*/
    rewind (file);
}

  


/******************************************************************************
******************************* allocation fonctions **************************
 *****************************************************************************/

/**********  give a memory for the 2D table  **********/
char** allocation2D (int l, int c)
{
  char ** Tab = malloc(l*sizeof(char*));
  int i;
  for (i=0; i<l; i++) {
    Tab[i] = malloc(c*sizeof(char));
  }
  return Tab;
}

/******* give a memoru fot the 2D object_breakout table *******/
object_breakout** alloc (int l, int c) 
{
  object_breakout** Tab = malloc(l*sizeof(object_breakout*));
  int i;
  for (i=0; i<l; i++) {
    Tab[i] = malloc(c*sizeof(object_breakout));
  }
  return Tab;
}



/******************************************************************************
******************************* data fonctions **************************
 *****************************************************************************/

/******** count the number of rows and columns in the file ********/
void count_dimension (FILE *file, int *row, int *col, int *nb_char) 
{
    /*take the current value on the file*/
    char cursor;     
    bool end_level = false;
    /*for know if we are in the pair and unpair ligne*/
    bool pair = false;  
    /*count the number of columns if it's a pair line*/
    /*initialized at 1 for count the \n */
    int col1 = 1;      
    /*count the number of colums if it's a unpair line*/
    /*initialized at 1 for count the \n */
    int col2 = 1;      
    /*take the maximum of the two numbers of columns*/
    int max_col = 0;       
    
    /*put the first character in this varible*/
    cursor = fgetc (file); 
    *nb_char += 1;
    while (cursor != EOF && !end_level) {

        /*if it's an impair line and the character is not a return line*/
        if ( !pair && (cursor != '\n') ) {
            /*if the character is the end level character*/
            if (cursor == '#') {
                end_level = true;
            }
            col1 += 1;
        }
        
        /*if it's a pair line and the character is not a return line*/
        if ( pair && (cursor != '\n') ) {
            /*if the character is the end level character*/
            if (cursor == '#') {
                end_level = true;
            }
            col2 += 1;
        } 
        
        /*if the character is a return line*/
        if ( cursor == '\n' ) {
            *row += 1;
            /*if the current line (before the return line) is pair*/
            if (pair) {
                /*put the pair at false (the line is impair)*/
                pair = false;
                /*col take the max between col1 and col2*/
                if (max_col <= max(col1,col2)){
                    max_col = max(col1, col2);
                }
                if (max_col > *col) {
                    /*we put the maximum of the number of columns*/
                    /*if  the max is superior at col*/
                    *col = max_col;      
                }
                /*put the numbers of columns at 1 otherwise we will have*/
                /*the number of all the character in the file*/
                col1 = 1;     
                col2 = 1;     
            }
            
            /**if the current line (before the return line) is impair*/
            else {
                /*put the pair at true (the line is pair)*/
                pair = true;
                 /*col take the max between col1 and col2*/
                if (max_col <= max(col1,col2)){
                    max_col = max(col1, col2);
                }
                if (max_col > *col) {
                    /*we put the maximum of the number of columns*/
                    /*if the max is superior at col*/
                    *col = max_col;      
                }
                /*put the numbers of columns at 1 otherwise we will have*/
                /*the number of all the character in the file*/
                col1 = 1;     
                col2 = 1;     
            }
        }
        /*put the next character of the file in the varible*/
        cursor = fgetc (file);
        /*increments the number total of character in the level*/
        *nb_char += 1;
    }
    /*if the caracter is the end file caracter*/
    if(cursor == EOF){
        /*decrements the number total of character in the level*/
        *nb_char = *nb_char -1;
    }
}

/********* return the maximum between two integers ***********/
int max ( int a, int b)
{
  int max_int = a;
  if ( b > a ) {
    max_int = b;
  }
  return max_int;
}

/********* return the minimum between two integers ***********/
int min (int a, int b) 
 {
  int min_int = a;
  if (b < a) {
    min_int = b;
  }
  return min_int;
}

/******* read the data text  ******/
char** read_data(FILE *file, int row, int col)
{  
    char ** T;
    /*array of 2 dimensions for take the database and declared*/
    /*thanks to the allocation2D function */
    T = allocation2D(row,col);  
    /*read the file only if the file is open*/
    if (file != NULL) {                
        /*variable which the current  character of the file */
        char cc;            
        /*variables to range the array*/
        int i,j;                            
        /*put all the contents of the file in the array*/
        for(i=0;i<row;i++){                 
            for(j=0;j<col;j++){                   
                cc = fgetc(file);
                if ( (j < (col)) && (cc == '\n')) {
                    /*if the number of character in the line is inferior*/
                    /*to the number max of columns in the data*/
                    while (j < (col-1)) {
                    T[i][j] = ' ';
                    j++;
                    }
                }
                T[i][j]=cc;
            }
        }
    /*print an error message if the file is not open*/
    } else  {
        printf("Impossible d'ouvrir le fichier breakout_data.txt");
    } 
    return T;
}

/***** read the data table to put them on an other table for the gestion of the bricks ****/
void read_table (object_breakout **table, char** tab_data, float *x, float  *y, 
                 int row, int col, int *nbI, int *nbII, int *nbIII, int *nbIV, int *nbV, 
                 int *nbVI, int *nbVII, SDL_Surface *screen) 
{
    int i,j;
    for (i=0; i<row; i++) {
        for (j=0; j<col; j++) {
            /*if the character is a brick blue character*/
            if ( tab_data[i][j] == '1' ) {
                table[0][*nbI] = init_object (1, *x, *y, screen, -1);
                *x += table[0][*nbI].width;
                *nbI += 1;
            /*if the character is a brick green character*/
            } else if ( tab_data[i][j] == '2' ) {
                table[1][*nbII] = init_object (2, *x, *y, screen, -1);
                *x += table[1][*nbII].width;
                *nbII += 1;
            /*if the character is a brick red character*/
            } else if ( tab_data[i][j] == '3' ) {
                table[2][*nbIII] = init_object (3, *x, *y, screen, -1);
                *x += table[2][*nbIII].width;
                *nbIII += 1;
            /*if the character is a brick black character*/
            } else if ( tab_data[i][j] == '4' ) {
                table[3][*nbIV] = init_object (4, *x, *y, screen, -1);
                *x += table[3][*nbIV].width;
                *nbIV += 1;
            /*if the character is a brick yellow character*/
            } else if ( tab_data[i][j] == '5' ) {
                table[4][*nbV] = init_object (5, *x, *y, screen, -1);
                *x += table[4][*nbV].width;
                *nbV += 1;
            /*if the character is a brick beige character*/
            } else if ( tab_data[i][j] == '6' ) {
                table[5][*nbVI] = init_object (6, *x, *y, screen, -1);
                *x += table[5][*nbVI].width;
                *nbVI += 1;
            /*if the character is a brick pink character*/
            } else if ( tab_data[i][j] == '7' ) {
                table[6][*nbVII] = init_object (7, *x, *y, screen,- 1);
                *x += table[6][*nbVII].width;
                *nbVII += 1;
            /*if the character is a return character*/
            } else  if (tab_data[i][j] == '\n') {
                *x = 0;
                *y += DEFAULT_HEIGHT;
            /*if the character is an other character*/
            } else {
                * x += DEFAULT_WIDTH;
            }
        }
    }
}



/******************************************************************************
******************************* load fonctions **************************
 *****************************************************************************/

/* load the good bonus for the rule menu */
SDL_Surface* load_bonus (int i)
 {
    SDL_Surface *s = load ("Brick1.bmp");
    switch (i) {
        case REDUC:
            s = load ("reduce.bmp");
            break;
        case GROW:
            s = load ("grow.bmp");
            break;
        case LOST:
            s = load ("lost.bmp");
            break;
        case LIFE:
            s = load ("life.bmp");
            break;
        case SCORE:
            s = load ("score.bmp");
            break;
        case BOUNCE:
            s = load ("bounce.bmp");
            break;
        case MULTI:
            s = load ("multiball.bmp");
            break;
        case CROSS:
            s = load ("cross.bmp");
            break;
        case MIN:
            s = load ("min.bmp");
            break;
        case SLOW_BALL:
            s = load ("slow_ball.bmp");
            break;
        case SPEED_BALL:
            s = load ("speed_ball.bmp");
            break;
        case SLOW_PLAT:
           s =  load ("slow_plat.bmp");
            break;
        case SPEED_PLAT :
           s =  load ("speed_plat.bmp");
            break;
        
        default:
            break;
    }
    return s;
}

/*** load the image ***/
SDL_Surface * load (char * name_file)
{
  SDL_Surface *temp, *picture_loaded;
  /*download in the temporair variable*/
  temp = SDL_LoadBMP(name_file);
  /*put the image in the good variable*/
  picture_loaded = SDL_DisplayFormat (temp);
  SDL_FreeSurface (temp);
  return picture_loaded;
}


/********** set the colokey of the image ********/
void set_colorkey (SDL_Surface *screen, int R, int G, int B, SDL_Surface *sprite) 
 {
  int colorkey;
  colorkey = SDL_MapRGB(screen -> format, R, G, B);
  SDL_SetColorKey (sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}




/******************************************************************************
***************************** initialization fonctions ************************
 *****************************************************************************/

/*initilize the briks, ball, platform and bonus (the object_breakout object) */
object_breakout init_object (int type, float x_act, float y_act, SDL_Surface *screen,
                             int type_bonus) 
 {
    /*creation of the object */
    object_breakout object; 
       
    /*same for all the objects*/
    object.x = x_act;
    object.y  = y_act;
    object.c_frame = 0;
    object.colorkey = SDL_MapRGB (screen -> format, 255, 0, 255);
        
    if (type == BRICKI) {
        object.width = 32;
        object.height = 16;
        object.sprite = load ("Brick1.bmp");
        object.n_frame = 1;
    }
        
    if (type == BRICKII) {
        object.width = 32;
        object.height = 16;
        object.sprite = load ("Brick2.bmp");
        object.n_frame = 2;
    }
        
    if (type == BRICKIII) {
        object.width = 32;
        object.height = 16;
        object.sprite = load ("Brick3.bmp");
        object.n_frame = 3;
        
    }
    
    if (type == BRICKIV) {
        object.width = 32;
        object.height = 16;
        object.sprite = load ("Brick4.bmp");
        object.n_frame = 1;
    }

    if (type == BRICKV) {
        object.width = 32;
        object.height = 16;
        object.sprite = load ("Brick5.bmp");
        object.n_frame = 1;
    }
    
    if (type == BRICKVI) {
        object.width = 32;
        object.height = 16;
        object.sprite = load ("Brick6.bmp");
        object.n_frame = 2;
    }
    
    if (type == BRICKVII) {
        object.width = 32;
        object.height = 16;
        object.sprite = load ("Brick7.bmp");
        object.n_frame = 3;
    }
    
        
    if (type == BALL) {
        object.width = 16;
        object.height = 16;
        object.sprite = load ("Ball.bmp");
        object.n_frame = 1;
    }

    if (type == PLAT) {
        object.width = 64;
        object.height = 16;
        object.sprite = load ("NormalPlatform.bmp");
        object.n_frame = 1;
    }
    
    
        
    if (type == BONUS){
        /*same for all the bonus*/
        object.t_bonus = type_bonus;
        object.activate = false;
        object.speed_y = 2;
        object.width = 17;
        object.height = 17;
        object.n_frame = 1;
        if (object.t_bonus == REDUC){
            object.sprite = load ("reduce.bmp");
        
        } else if (object.t_bonus == GROW){
            object.sprite = load ("grow.bmp");
        
        } else if (object.t_bonus == LOST) {
            object.sprite = load ("lost.bmp");
        
        } else if (object.t_bonus == LIFE) {
            object.sprite = load ("life.bmp");

        } else if (object.t_bonus == SCORE) {
            object.sprite = load ("score.bmp");
            
        } else if (object.t_bonus == MULTI) {
            object.sprite = load ("multiball.bmp");
            
        } else if (object.t_bonus == MIN) {
            object.sprite = load ("min.bmp");
            
        } else if (object.t_bonus == SLOW_BALL) {
            object.sprite = load ("slow_ball.bmp");
            
        } else if (object.t_bonus == SPEED_BALL) {
            object.sprite = load ("speed_ball.bmp");
            
        } else if (object.t_bonus == SLOW_PLAT) {
            object.sprite = load ("slow_plat.bmp");
            
        } else if (object.t_bonus == SPEED_PLAT) {
            object.sprite = load ("speed_plat.bmp");
            
        } else if (object.t_bonus == BOUNCE){
            object.sprite = load ("bounce.bmp");
            
        } else if (object.t_bonus == CROSS){
            object.sprite = load ("cross.bmp");
        }
        
    } else {
        /*only if the object is not a bonus*/
        set_colorkey(screen, 255, 0, 255, object.sprite);
    }

    /*same for all the object*/
    object.picture.x = 0;
    object.picture.y = 0;
    object.picture.h = object.height;
    object.picture.w = object.width;
    object.position.x = (int) (object.x);
    object.position.y = (int) (object.y);
    object.counter = 0;
    
    return object;
}




/******************************************************************************
********************************* move fonctions ****************************
 *****************************************************************************/

/********* move the platform in funcion of their position ********/
void move_plat (object_breakout *plat)
 {
  plat -> position.x = plat -> x;
  plat -> position.y = plat -> y;
}

/********  make move the ball ************/
void move_ball (object_breakout *ball, int *nb, object_breakout *platform, 
                object_breakout *power, int *nb_power, SDL_Surface *screen, 
                 bool *throw)

{
    int i;
    bool fall = false;
    for (i=0; i<*nb; i++) {
        /*if the ball is slow*/
        if (ball[i].activate) {
            ball[i].x += ball[i].speed_x / 5;
            ball[i].y += ball[i].speed_y / 5;
        }
        /*if the ball is speed up*/
        if (ball[i].initiate) {
            ball[i].x += ball[i].speed_x * 5;
            ball[i].y += ball[i].speed_y * 5;
        } 
        /*if the speed of the ball is normal*/
        if (!ball[i].activate && !ball[i].initiate) {
            ball[i].x += ball[i].speed_x;
            ball[i].y += ball[i].speed_y;
        }
        ball[i].position.x = ball[i].x;
        ball[i].position.y = ball[i].y;
        
        /*if the ball is in the left edge of the screen*/
        if (ball[i].x   <  0 ) {
            rebond(&ball[i], 0, true);
        }
        /*if the ball is in the right edge of the screen*/
        if (ball[i].x   > SCREEN_WIDTH - ball[i].width) {
            rebond(&ball[i], 0, true);
        }
        /*if the ball is in the top edge of the screen*/
        if (ball[i].y  <  0) {
            rebond(&ball[i], 1, true);
        }
        /*if the ball is in the bottom edge of the screen*/
        if (ball[i].y > SCREEN_HEIGHT - ball[i].height) {
            /*if the bounce bonus is not activate*/
            if (!ball[i].bounce) {
                int life = ball[i].life;
                int score = ball[i].score;
                /*if we have an only ball*/
                if (*nb <= 1) {
                    /*re initialization of the ball and the platform*/
                    *platform =  init_object (PLAT,(SCREEN_WIDTH - PLATFORM_WIDTH) / 2, 
                                        SCREEN_HEIGHT - (2 * PLATFORM_HEIGHT),
                                        screen, -1);
        
                    ball[i] = init_object (BALL, platform -> position.x + 
                            (PLATFORM_WIDTH / 3), platform -> position.y -      
                            (PLATFORM_HEIGHT), screen, -1);
                    
                    /*the ball is not throw*/
                    *throw = false;
            
                    /*take a life*/
                    ball[i].life = life - 1;
                    ball[i].score = score;
                    fall = true;
                
                /*if you have more than 2 balls*/
                } else {
                    /*the ball is fall, remove them*/
                    del (ball, nb, i);
                    /*put their score in an other ball*/
                    ball[0].score += score;
                }
                
            /*if bounce is activate*/
            } else {
                rebond(&ball[i], 1 , true);
            }
        }
    }
    /*if the last ball is fall*/
    if (fall) {
        /*remove all the bonus*/
        int nb_power_replace = *nb_power;
        for (i=0; i<nb_power_replace; i++) {
            del (power, nb_power, i);
        }
        *nb_power = 0;
    }
}

/********  make move the bonus ************/
void move_power (object_breakout *tab, int *n)
 {
    int i;
    for(i=0;i<*n;i++){
        /*if the tab is not already activate (no collision*/
        if (!tab[i].activate) {
            tab[i].y = tab[i].y + tab[i].speed_y;
            tab[i].position.x = tab[i].x;
            tab[i].position.y = tab[i].y;
            /*if the bonus is at the end of the screen*/
            if (tab[i].y > SCREEN_HEIGHT - tab[i].height) {
                /*remove them*/
                del(tab,n,i);
            }
        }
    }
}




/******************************************************************************
******************************** collide fonctions ****************************
 *****************************************************************************/

/* Collide between 2 objects */
bool collide(object_breakout *sprite1, object_breakout *sprite2)
{
    /*if we have a collision of the two sprites*/
    if ((max(sprite1->x,sprite2->x) < min (sprite1 -> x + sprite1 -> width,
                sprite2->x+sprite2->width))
        && (max(sprite1->y,sprite2->y) < min(sprite1->y+sprite1->height,
                                             sprite2->y+sprite2->height))){
        return true;
    /*if we don't have a collision of the two sprites*/
    }else{
        return false;
    }
}

/****** see with precision if we are a collision between two objects ****/
bool collide_precise (object_breakout *sprite1, object_breakout *sprite2,
                      SDL_PixelFormat *format, float *cu, float *cv)
{
  
  bool test = collide (sprite1, sprite2);

  if (test) {

    Uint32 *bmp1 = (Uint32 *) malloc (sizeof (Uint32) * sprite1 -> width * sprite1 -> height), 
                *sprite_it, *bmp_it;
    Uint32 *bmp2 = (Uint32 *) malloc (sizeof (Uint32) * sprite2 -> width * sprite2 -> height);
    int u, v, v1 = 0;
    
    /* Lock the image to make sure that the image isn't change during the execution of the fonction */
    SDL_LockSurface (sprite1 -> sprite);
    SDL_LockSurface (sprite2 -> sprite);
    bmp_it = bmp1;
    sprite_it = (Uint32 *) (sprite1 -> sprite -> pixels) + sprite1 -> n_frame * sprite1 -> width;
    
    for (v = 0; v < sprite1 -> sprite -> h; v++) {
      for (u = 0; u < sprite1 -> width; u++) {
	*bmp_it++ = *sprite_it++;
      }
      sprite_it += (sprite1 -> sprite -> w - sprite1 -> width);
    }
    
    bmp_it = bmp2;
    sprite_it = (Uint32 *) (sprite2 -> sprite -> pixels) + sprite2 -> n_frame * sprite2 ->width;
    for (v = 0; v < sprite2 -> sprite -> h; v++) {
      for (u = 0; u < sprite2 -> width; u++) {
	*bmp_it++ = *sprite_it++;
      }
    }
    
    SDL_UnlockSurface (sprite1 -> sprite);
    SDL_UnlockSurface (sprite2 -> sprite);
    
    bmp_it = bmp1;
    test = false;
    
    while (!test && v1 < sprite1 -> sprite -> h) {
      int u1 = 0;
      while (!test && u1 < sprite1 -> width) {
	int screen_u = u1 + sprite1 -> x;
	int screen_v = v1 + sprite1 -> y;
	
	if (screen_u >= sprite2 -> x &&
	      screen_u < sprite2 -> x + sprite2 -> width &&
	      screen_v >= sprite2 -> y &&
	      screen_v < sprite2 -> y + sprite2 -> sprite -> h) {
	  
	  Uint32 pixel1 = *bmp_it;
	  int col1;
	  Uint8 r, g, b;
	  
	  SDL_GetRGB (pixel1, format, &r, &g, &b);
	  col1 = SDL_MapRGB (format, r, g, b);
	  
	  if (col1 != sprite1 -> colorkey) {
	    Uint32 pixel2;
	    int col2;
	    Uint8 r, g, b;
	    int u2, v2;
	    
	    u2 = screen_u - sprite2 -> x;
	    v2 = screen_v - sprite2 -> y;
	    
	    pixel2 = *(bmp2 + u2 + v2 * sprite2 -> width);
	    SDL_GetRGB (pixel2, format, &r, &g, &b);
	    col2 = SDL_MapRGB (format, r, g, b);
	    
	    if (col2 != sprite2 -> colorkey) {
	      test = true;
	      *cu = screen_u;
	      *cv = screen_v;
	    }
	  }
	}
	u1 ++;
	bmp_it ++;
      }
     v1++;
    }
    free (bmp1);
    free (bmp2);
  }
  
  return test;
}

/*** look if we are a collision in a table ***/
bool collide_table (object_breakout ** table, int *n, int *m, int *l, int *p,
		    int *q, int *r, int *s, object_breakout *ball, int nb_ball,
		    SDL_PixelFormat *format, int nbtype, float *cx, float *cy)
{
    /*put true when we have a collision or we have browse all the table*/
    bool exit1 = false;  
    bool col = false;
    int *k = NULL, i = 0;
    while (!col && i < nbtype) {
        if (i == 0){
            /*number of brick blue*/
            k = n;
        }
        else if (i == 1){
            /*number of brick green*/
            k = m;
        }
        else if (i == 2){
            /*number of brick red*/
            k = l;
        }
        else if (i == 3){
            /*number of brick black*/
            k = p;
        }
        else if (i == 4){
            /*number of brick yellow*/
            k = q;
        }
        else  if (i == 5){
            /*number of brick beige*/
            k = r;
        } else {
            /*number of brick pink*/
            k = s;
        }
        col = collide_table_aux( table[i], k, ball, nb_ball, format, i+1, cx, cy, &exit1);
        i++; 
    }
    return exit1;
}



/***** look if we are a collision between a brick and the ball into the table ******/
bool collide_table_aux (object_breakout *table , int *n, object_breakout *ball, 
                int nb_ball, SDL_PixelFormat *format, int type, float *u, float *v, 
                bool *exit1)
{
    /*reb say if you make a bounce or not*/
    bool exit2 = false, reb = true;
    int i = 0, j, k;
    int pas = 2;
    bool g, d, h, b;
    for (k=0; k<nb_ball; k++) {
        /*you don't make a bounce*/
        if (ball[k].cross) {
            reb = false;
        }
        exit2 = false;
        i = 0;
        while (!exit2 && i < *n) {
            if (collide_precise (&ball[k], &table[i], format, u, v)) {
                /*the condition of the collision*/
                /*in the left edge of the brick*/
                g = (*u - pas <= table[i].x) 
                        && (table[i].x <= *u + pas);
                /*in the right edge of the brick*/
                d =  (*u - pas <= table[i].x + table[i].width) 
                        && (table[i].x + table[i].width <= *u + pas);
                /*in the top edge of the brick*/
                h =( *v - pas <= table[i].y) 
                        && (table[i].y <= *v + pas);
                /*in the bottom edge of the brick*/
                b = (*v - pas <= table[i].y + table[i].height) 
                        && (table[i].y + table[i].height <= *v + pas);

                /*the collision is in the right or left edge of the brick*/
                if (g || d)  {
                    rebond (&ball[k], 0, reb);
                    exit2 = true;
                /*the collision is in the top or bottom edge of the brick*/
                }
                if (b || h) {
                    rebond (&ball[k], 1, reb);
                    exit2 = true;
                }

                /*if we don't make  bounce*/
                if (!reb) {
                    /*we just remove the brick*/
                    SDL_FreeSurface (table[i].sprite);
                    for (j=i; j < *n-1; j++) {
                        table[j] = table[j+1];
                    }
                    *n = *n - 1;
                    if ( (type == BRICKI) || (type == BRICKV) ) {
                        ball[k].score += 1;
                    }
                    if ( (type == BRICKII) || (type == BRICKVI) ) {
                        ball[k].score += 3;
                    }
                    if  ( (type == BRICKIII) || (type == BRICKVII) ) {
                        ball[k].score += 5;
                    }
                    
                /*we make a bounce and the brick is not black*/
                } else if (type != BRICKIV) {
                    /*we change the frame of the brick*/
                    table[i].c_frame += 1;
                    /*if it's was the last frame we remove the brick*/
                    if (table[i].c_frame == table[i].n_frame) {
                        *exit1 = true;
                        SDL_FreeSurface (table[i].sprite);
                        for (j=i; j < *n-1; j++) {
                            table[j] = table[j+1];
                        }
                        *n = *n - 1;
                        /* increase in score */
                        if ( (type == BRICKI) || (type == BRICKV) ) {
                            ball[k].score += 1;
                        }
                        if ( (type == BRICKII) || (type == BRICKVI) ) {
                            ball[k].score += 3;
                        }
                        if  ( (type == BRICKIII) || (type == BRICKVII) ) {
                            ball[k].score += 5;
                        }
                    } else {
                        table[i].picture.x = table[i].c_frame * table[i].width;
                    }
                }
            }
            i++;
        }
    }
    return exit2;
}

/**** loke if we are a collision between the platform and the ball ******/
void collide_platform (object_breakout *plat, object_breakout *ball, int nb, 
                       SDL_PixelFormat *format)
{
    float mx, my, xa, ya;
    float dist;
    float cx = 0, cy = 0;
    bool g, d, h;
    int i;
    
    for (i=0; i<nb; i++) {
        if (collide_precise(&ball[i], plat, format, &cx, &cy)) {
            /*condition of collision of the platform*/
            /*in the left edge*/
            g = plat -> x == cx;
            /*in the right edge*/
            d = plat -> x + plat -> width >= cx;
            /*in the top edge*/
            h = plat -> y == cy;
            
            /*calcuation of the middle of the platform*/
            mx = plat -> x + (plat -> width / 2);
            my = plat -> y;
            /*calcuation of the distance between the collision and the middle*/
            dist = sqrt( ( (cx - mx) * (cx - mx) ) + ( (cy - my) * (cy - my) ) );
            
            /*if the collision is in the top edge*/
            if (h) {
                /*if the collision in the right part of the platform*/
                if (cx > mx){       
                    /*calulation of the news vectors*/
                    xa = cos (2 * M_PI / dist); 
                    ya = -sin (2 * M_PI / dist);
                    ball[i].speed_x = xa*SPEEDX;
                    ball[i].speed_y = ya*SPEEDY;
                /*if the collisison is in the left part of the platform*/
                }else if (cx < mx){
                    /*calulation of the news vectors*/
                    xa = -cos (2 * M_PI / dist); 
                    ya = -sin (2 * M_PI / dist);
                    ball[i].speed_x = xa*SPEEDX;
                    ball[i].speed_y = ya*SPEEDY;
                /*if the collision is in the middle of the platform*/
                } else {
                    ball[i].speed_y =  -ball[i].speed_y;
                }
            /*if the collision is in the left or right edge*/
            } else if (g || d) {
                rebond(&ball[i], 0, false);
            }
        } 
    }
}

/* look if there is a collision between the platform and the edges of the screen */
void collide_screen (object_breakout *platform)
{
    /*if the platform is in the left edge of the screen*/
    if (platform -> x <= 0) {
                platform -> x = 0; 
    }
    /*if the platform is in the right edge of the screen*/
    if (platform -> x >= SCREEN_WIDTH - PLATFORM_WIDTH)  {
                platform -> x = SCREEN_WIDTH - PLATFORM_WIDTH;
    }
}

/*******  handle the collide between bonus and platform  *************/
void collide_power (object_breakout *platform, object_breakout *power, 
                    object_breakout *ball, int *nb_ball, SDL_Surface *screen,
                    int *n, int *gameover)
{
    
    float x=0 ,y=0;
    int i, k;
    for (i=0; i<*n; i++){
        /*if the bonus is not already activate*/
        if (power[i].activate == false) {
            /*if we have a collison between the bonus and the pltform*/
            if (collide_precise(&power[i], platform, screen->format,&x,&y)){
                power[i].activate = true;
                /*look what is the bonus activate*/
                if (power[i].t_bonus == REDUC){
                    /*reduc the platform*/
                    platform -> width = 32;
                    platform -> sprite = load("LittlePlatform.bmp");
                    set_colorkey(screen, 255, 0, 255, platform->sprite);
                    power[i].counter = TIME_REDUCE;
                }else if (power[i].t_bonus == GROW){
                    /*grow a platform*/
                    platform -> width = 128;
                    platform->picture.w = platform->width;
                    platform -> sprite = load("BigPlatform.bmp");
                    set_colorkey(screen, 255, 0, 255, platform->sprite);
                    power[i].counter = TIME_GROW;
                } else if (power[i].t_bonus == LOST) {
                    /*lost the game*/
                    *gameover = 1;
                } else if (power[i].t_bonus == LIFE) {
                    /*win a life*/
                    ball[0].life += 1;
                    del (power, n, i);
                } else if (power[i].t_bonus == SCORE) {
                    /*win 10 points*/
                    ball[0].score += 10;
                    del (power, n, i);
                } else if (power[i].t_bonus == MULTI) {
                    /*have an other ball*/
                    if (*nb_ball < MAX_SIZE) {
                        ball[*nb_ball] = init_object (BALL, ball[0].x, ball[0].y, screen, -1);
                        ball[*nb_ball].speed_x = ball[0].speed_x;
                        ball[*nb_ball].speed_y = -ball[0].speed_y;
                        ball[*nb_ball].life = ball[0].life;
                        ball[*nb_ball].score = 0;
                        *nb_ball += 1;
                    }
                    del (power, n, i);
                } else if (power[i].t_bonus == MIN) {
                    /*lose a life*/
                    ball[0].score -= 5;
                    del (power, n, i);
                } else if (power[i].t_bonus == SLOW_BALL) {
                    /*slow the ball*/
                    power[i].counter = TIME_SLOW_BALL;
                    for (k=0; k<*nb_ball; k++) {
                        ball[k].activate = true;
                    }
                } else if (power[i].t_bonus == SPEED_BALL) {
                    /*speed up the ball*/
                    power[i].counter = TIME_SPEED_BALL;
                    for (k=0; k<*nb_ball; k++) {
                        ball[k].initiate = true;
                    }
                }else if (power[i].t_bonus == SLOW_PLAT) {
                    /*slow the platform*/
                    power[i].counter = TIME_SLOW_PLAT;
                    platform -> activate = true;
                }else if (power[i].t_bonus == SPEED_PLAT) {
                    /*speed up the platform*/
                    power[i].counter = TIME_SPEED_PLAT;
                    platform -> initiate = true;
                } else if (power[i].t_bonus == BOUNCE){
                    /*the ball can bounce at the bottom of the screen*/
                    power[i].counter = TIME_BOUNCE;
                    for (k=0; k<*nb_ball; k++) {
                        ball[k].bounce = true;
                    }
                } else if ( power[i].t_bonus == CROSS){
                    /*the ball can cross the bricks*/
                    power[i].counter = TIME_CROSS;
                    for (k=0; k<*nb_ball; k++) {
                        ball[k].cross = true;
                    }
                }
            }
        }
    } 
}

/*** make a rebond on the ball *****/
void rebond (object_breakout *ball, int side, bool collide_screen)
{
   /*if the cross bonus is activate*/
    if (!ball -> cross || collide_screen) {  
         /*if the collision is in the left or right edge of th objet*/
        if (side == 0) { 
            /*change the orientation of the speed x*/
            ball->speed_x = - ball -> speed_x ;
        }
         /*if the collision is in the top or bottom edge of th objet*/
        if (side == 1) { 
            /*change the orientation in the speed y*/
            ball->speed_y = - ball -> speed_y;
        }
    }
}



/******************************************************************************
******************************** power fonctions ****************************
 *****************************************************************************/

/*reduce the size of the platform*/
void power (object_breakout *power, int *n, SDL_Surface *screen, int cx, int cy)
{
    int lucky = nb_random();
    /*if the table is not complete*/
    if (*n < NB_BONUS_IN_SAME_TIME) {
        if (lucky == REDUC){
        add(power, n, cx, cy, screen,REDUC);
        }else if (lucky == GROW){
        add(power, n, cx, cy, screen,GROW);
        } else if (lucky == LOST) {
            add (power, n, cx, cy, screen, LOST);
        } else if (lucky == LIFE) { 
            add (power, n, cx, cy, screen, LIFE);
        } else if (lucky == SCORE) { 
            add (power, n, cx, cy, screen, SCORE);
        } else if (lucky == BOUNCE){
        add(power, n, cx, cy, screen,BOUNCE);
        }else if (lucky == MULTI) { 
            add (power, n, cx, cy, screen, MULTI);
        } else if (lucky == MIN) { 
            add (power, n, cx, cy, screen, MIN);
        } else if (lucky == CROSS){
        add(power, n, cx, cy, screen,CROSS);
        } else if (lucky == SLOW_BALL) { 
            add (power, n, cx, cy, screen, SLOW_BALL);
        } else if (lucky == SPEED_BALL) { 
            add (power, n, cx, cy, screen, SPEED_BALL);
        } else if (lucky == SLOW_PLAT) { 
            add (power, n, cx, cy, screen, SLOW_PLAT);
        } else if (lucky == SPEED_PLAT) { 
            add (power, n, cx, cy, screen, SPEED_PLAT);
        } 
    }
}

/*Handle the bonus time*/
void power_time (object_breakout *platform, object_breakout *ball, int nb_ball,
                 object_breakout *tab, int *n, SDL_Surface *screen)
{
    int i, k; 
    for (i=0; i<*n; i++) {
        /*if the bonus is activate*/
        if (tab[i].activate){
            tab[i].counter = tab[i].counter - 1;
            /*if the counter is finish*/
            if (tab[i].counter <= 0){
                /*look what is the bonus*/
                if ((tab[i].t_bonus == REDUC) || (tab[i].t_bonus == GROW)){
                    del(&tab[i],n,i);
                    platform -> width = 64;
                    platform -> sprite = load("NormalPlatform.bmp");
                    set_colorkey(screen, 255, 0, 255, platform->sprite);
                }
                if (tab[i].t_bonus == SLOW_BALL) {
                    del(&tab[i],n,i);
                    for (k=0; k<nb_ball; k++) {
                        ball[k].activate = false;
                    }
                }
                if (tab[i].t_bonus == SPEED_BALL) {
                    del(&tab[i],n,i);
                    for (k=0; k<nb_ball; k++) {
                        ball[k].initiate = false;
                    }
                }
                if (tab[i].t_bonus == SLOW_PLAT) {
                    del(&tab[i],n,i);
                    platform -> activate = false;
                }
                if (tab[i].t_bonus == SPEED_PLAT) {
                    del(&tab[i],n,i);
                    platform -> initiate = false;
                } 
                if (tab[i].t_bonus == BOUNCE){
                    del(&tab[i],n,i);
                    for (k=0; k<nb_ball; k++) {
                        ball[k].bounce = false;
                    }
                } 
                if ( tab[i].t_bonus == CROSS){
                    del(&tab[i],n,i);
                    for (k=0; k<nb_ball; k++) {
                        ball[k].cross = false;
                    }
                }
            }
        }
    }
}


/* Gives a random number between two ends to know which bonus print */
int nb_random ()
 {
  int nb;
  /*to have a random number*/
  nb = rand()%ALEA;
  return nb;
}



/******************************************************************************
******************************** update fonctions ****************************
 *****************************************************************************/

/*add an element in an array and initialize*/
void add (object_breakout *tab, int *n, int cx, int cy, SDL_Surface *screen,
          int type_bonus)
{
  tab[*n] = init_object (BONUS, cx, cy, screen, type_bonus);
  *n += 1;
}

/*delete an element in an array*/
void del (object_breakout *tab, int *n, int cur)
{
//    SDL_FreeSurface(tab[cur].sprite);
  for (int j = cur; j < *n-1; j++){
    tab[j] = tab[j+1];
  }
  *n -= 1;
}



/******************************************************************************
******************************** print fonctions ****************************
 *****************************************************************************/

/* draw the bakground on the screen */
void draw_background (SDL_Surface *background, SDL_Surface *screen) 
{
    for (int x = 0; x < SCREEN_WIDTH / BG_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT / BG_HEIGHT; y++) { 
            SDL_Rect position;
            position.x = x * BG_WIDTH;
            position.y = y * BG_HEIGHT;
            SDL_BlitSurface(background, NULL, screen, &position);
        }
    }
}

/*  print the contents of  a table */
void print_tab (object_breakout *table, int nb,  SDL_Surface *screen)
{
  int i;
  /*print the contents of the table in the screen*/
  for (i=0; i<nb; i++) {
    SDL_BlitSurface(table[i].sprite, &table[i].picture, screen,& table[i].position);
  }
}

/* print the sprite of the bonus fr the rule */
void print_sprite (SDL_Surface *sprite, float x, float y, int h, int w, 
                   SDL_Surface *screen) 
{
    SDL_Rect pict, pos;
    pict.x = 0;
    pict.y = 0;
    pict.h = h;
    pict.w = w;
    pos.x = (int) x;
    pos.y = (int) y;
    SDL_BlitSurface (sprite, &pict, screen, &pos);
}

/* print an object_breakout */
void print_object (object_breakout *object, SDL_Surface *screen)
{
    SDL_BlitSurface (object -> sprite, &object -> picture, screen, 
                     &object -> position);
}

/* print different text on the screen */
void print_text (const char *text, int val, SDL_Surface *screen, int pos_x, 
                 int pos_y, int size, int select) 
{
    /*open the font*/
    TTF_Font *font = TTF_OpenFont("A Love of Thunder.ttf", size);
    /*initialization of the black color*/
    SDL_Color color = {0,0,0,0};
    /*the desired color is red*/
    if (select == 1) {
        color.r = 255;
    /*the desired color is green*/
    } else if (select == 2) {
        color.g = 250;
    /*the desired color is blue*/
    } else if (select == 3) {
        color.b = 255;
    /*the desired color is purple*/
    } else if (select == 4) {
        color.r = 255;
        color.b = 255;
    }
    
    /*if we want to print an integer associate at the text*/ 
    if ( val != -1 ) {
        char text_val [50];
        SDL_Surface *sprite_text_val;
        SDL_Rect position_text_val;
        /*transform the integer to char*/
        sprintf (text_val, "%d", val);
        sprite_text_val = TTF_RenderUTF8_Solid (font, text_val, color);
        position_text_val.x = pos_x + 110;
        position_text_val.y = pos_y;
        SDL_BlitSurface (sprite_text_val, NULL, screen, &position_text_val);
        free(sprite_text_val);
    }
    
    SDL_Surface *sprite_text;
    SDL_Rect position_text; 
    sprite_text = TTF_RenderUTF8_Solid (font, text, color);    
    position_text.x = pos_x;
    position_text.y = pos_y;   
    
    SDL_BlitSurface (sprite_text, NULL, screen, &position_text);
    
    TTF_CloseFont(font);
    free(sprite_text);
}

/* print the name of the player */
void print_name (SDL_Surface *screen, SDL_Surface *background,  char *name)
{
    /*for don't repeat the key*/
    SDL_EnableKeyRepeat(0,0);
    /*the main variable of the fonction*/
    int end = 0;

    /*coordonates of the print*/
    int x = SCREEN_WIDTH / 2 + 30;
    int y = SCREEN_HEIGHT/3 + 30;

    while (!end) {
	
        SDL_Event event_name;
        /*if a key is pressed*/
        if (SDL_PollEvent (&event_name)) {
            handle_event_name (event_name, &end,  name);
        }
        /*print the text in the screen*/
	draw_background (background, screen);
        print_text (name, -1, screen, x, y, 32, 0);
        print_text ("What is your name ? ", -1, screen, SCREEN_WIDTH / 3, 
                    SCREEN_HEIGHT/3, 32, 0);
	print_text ("My name is ", -1, screen,   SCREEN_WIDTH / 3, 
                    SCREEN_HEIGHT/3 + 30, 32, 0);

        SDL_UpdateRect (screen, 0, 0, 0, 0);
    }
    /*returns the enable key repeat*/
    SDL_EnableKeyRepeat(10, 10);
}

/* print the ranking of the game */
void ranking (SDL_Surface *screen, SDL_Surface *background,
              int score_player, int win)
{
    /*the number of the player in the ranking*/
    int nb_in_rank = -1;
    /*for read the different tables*/
    int i = 0;
    /*for find the place of the player in the ranking*/
    int find = 0;
    /*open the ranking file*/
    FILE *file = fopen ("rank.txt", "r+");
    FILE *replace_file = fopen ("replace_rank.txt", "w+");
    
    /*ask the name of the player*/
    char name [MAX_SIZE] = "";
    print_name (screen, background, name);
    
    /*the table of name of the ranking*/
    char tab_rank [NB_RANK][MAX_SIZE]; 
    /*the table of score of the ranking*/
    char tab_score [NB_RANK][MAX_SIZE];
    /*the table of the integer of the table above*/
    int int_score [NB_RANK];
    /*the table of color for print the ranking*/
    int tab_colors [NB_RANK] = {0};
    
    /*the current character in the file*/
    char cursor[MAX_SIZE]; 

    /*if the file is correctly open*/
    if (file != NULL) {
        /*put the name in the name table*/
        for (i = 0; i < NB_RANK; i++) {
            if (fgets (cursor, MAX_SIZE, file) != NULL) {
                sprintf (tab_rank[i], "%s", cursor);
            }
        }
        /*put the score in the score table*/
        for (i = 0; i < NB_RANK; i++) {
            if (fgets (cursor, MAX_SIZE, file) != NULL) {
                sprintf (tab_score[i], "%s", cursor);
            }
        }
        /*transform the char table of score to a int table of score*/
        for (i = 0; i < NB_RANK; i++) {
            int_score [i] = atoi(tab_score[i]);
        }
        
        /*search the place of the player in the ranking*/
        i = 0;
        int j;
        while ( (i < NB_RANK) && !find) {
            if ( (score_player > int_score[i]) || (*tab_rank[i] == '#')) {
                nb_in_rank = i;
                tab_colors[i] = 3;
                for (j = NB_RANK ; j > i  ; j--) {
                    sprintf (tab_rank[j], "%s", tab_rank [j - 1]);
                    sprintf (tab_score[j], "%s", tab_score [j - 1]);
                    int_score[j] = int_score[j - 1];
                }
                int_score[i] = score_player;
                sprintf (tab_rank[i], "%s", name);
                strcat (tab_rank[i], "\n");
                sprintf (tab_score[i], "%d", score_player);
                strcat (tab_score[i], "\n");
                find = 1;
            }
            i++;
        }
        /*print the title*/
        draw_background (background, screen);
        for (i = 0; i<5; i++) {
            for (j = 0; j < 120; j++) {
                print_text("_", -1,screen, j * 5, 
                           SCREEN_HEIGHT / 60 + i, 8, 2);
                print_text("_", -1,screen, SCREEN_WIDTH/3 + 100 + j * 5, 
                           SCREEN_HEIGHT / 60 + 200 + i, 8, 3);
            }
        }
        if (win) {
            print_text ("Win", -1, screen, SCREEN_WIDTH / 3, 
                        SCREEN_HEIGHT / 60, 190, 0);
        } else {
            print_text ("Game over", -1, screen, SCREEN_WIDTH / 60, 
                        SCREEN_HEIGHT / 60, 170, 0);
        }
        
        /* the differents coordonates of print*/
        int x = (SCREEN_WIDTH / 3) + 25;
        int x1 = SCREEN_WIDTH / 3 + 75;
        int x2 = SCREEN_WIDTH / 3 + 275;
        int y = SCREEN_HEIGHT / 3 ;
        /*the multiple for the coordonates of the print*/
        int mult = 28;
        /*the size of the print*/
        int size = 24;
        /*print the ranking*/
        for (i = 0; i < NB_RANK; i++) {
            if (i == 0) {
                print_text("1 :", -1, screen, x,  y + mult * i , size, tab_colors[i]);
            } else if (i == 1) {
                print_text("2 :", -1, screen, x,  y + mult * i , size, tab_colors[i]);
            }else if (i == 2) {
                print_text("3 :", -1, screen, x,  y + mult * i , size, tab_colors[i]);
            }else if (i == 3) {
                print_text("4 :", -1, screen, x,  y + mult * i , size, tab_colors[i]);
            }else if (i == 4) {
                print_text("5 :", -1, screen, x,  y + mult * i , size, tab_colors[i]);
            }else if (i == 5) {
                print_text("6 :", -1, screen, x,  y + mult * i , size, tab_colors[i]);
            }else if (i == 6) {
                print_text("7 :", -1, screen, x,  y + mult * i , size, tab_colors[i]);
            }else if (i == 7) {
                print_text("8 :", -1, screen, x,  y + mult * i , size, tab_colors[i]);
            }else if (i == 8) {
                print_text("9 :", -1, screen, x,  y + mult * i , size, tab_colors[i]);
            }else if (i == 9) {
                print_text("10 :", -1, screen, x,  y + mult * i , size, tab_colors[i]);
            }
            print_text(tab_rank[i], -1, screen, x1,   y + mult * i , size, tab_colors[i]);
            print_text("", int_score[i], screen, x2,   y + mult * i , size, tab_colors[i]);
        }
        
        /*print the name and the score of the player if he isn't in the ranking*/
        if (nb_in_rank < 0) {
            print_text(name, -1, screen, x1,  y + mult * 12, size, 3);
            print_text("", score_player, screen, x2,  y + mult * 12, size, 3);
        }
        
        /*put the new ranking in an other file*/
        for (i = 0; i < NB_RANK; i++) {
            fputs (tab_rank[i], replace_file);
        }
        for (i = 0; i < NB_RANK; i++) {
            fputs (tab_score[i], replace_file);  
        }
        /*close the two files*/
        fclose(file);
        fclose(replace_file);
        /*remove the first*/
        remove("rank.txt");
        /*and rename the second like the first*/
        rename("replace_rank.txt","rank.txt");
        
    /*if the file is not correctly open*/
    } else {
        printf ("the file rank is not correctly open \n");
    }
  
}
