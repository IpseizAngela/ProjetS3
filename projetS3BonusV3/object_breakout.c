#include "object_breakout.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SPRITE_STEP 5



/************** management of keyboard keys *****************/
void HandleEvent(SDL_Event event, int *quit,  object_breakout *platform, bool *throw, object_breakout *ball, int *finish_level)
{
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    *quit = 1;
    break;

    /* handle the keyboard */
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_q:
      *finish_level = 1;
      break;
    case SDLK_LEFT:
      platform->x -= SPRITE_STEP;
      //printf("plat pos x %d \n", platform->position.x);
      break;
    case SDLK_RIGHT:
      platform->x += SPRITE_STEP;
      //printf("plat pos x %d \n", platform->position.x);
      break;
    case SDLK_SPACE:
      if (!*throw) {
       /* ball -> x =  225;
	ball -> y = 300; */
	ball -> speed_x = 0.;
	ball -> speed_y = -10;
	*throw = true;
      } 

    default:
      break;
    }
    break;
  }
}

/************** management of keyboard keys for the menu ************/
void handle_event_menu (SDL_Event event_menu, int *exit, int *begin, SDL_Surface *screen, SDL_Surface *background, int *play) {
  switch (event_menu.type) {
    case SDL_QUIT:
      *begin = 1;
      *exit = 1;
      break;
			  
    case SDL_KEYDOWN:
      switch (event_menu.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
            *begin = 1;
            *exit = 1;
            break;
                 
        case SDLK_LEFT:
            *play = 1;
            break;
        
        case SDLK_RIGHT:
            *play = 0;
            break;
            
        case SDLK_RETURN:
            if (*play == 1) {
                *begin = 1;
            } else if (*play == 0) {
                rule (screen, background);
            }
            break;
            
        default:
            break;				
            
      }
      break;
  }
}
   
   
/************** management of keyboard keys for the lose menu ************/
void handle_event_lose (SDL_Event event_lose,  int *exit, int *gameover, int *choose, int *replay) {
  switch (event_lose.type) {
  case SDL_QUIT:
    *choose = 1;
    break;
			
  case SDL_KEYDOWN:
    switch (event_lose.key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_q:
      *choose = 1;
      break;
	
    case SDLK_LEFT:
        *replay = 1;
        break;
    
    case SDLK_RIGHT:
        *replay = 0;
        break;
        
    case SDLK_RETURN:
        if (*replay ==  1) {
            *choose = 1;
            *exit = 0;
            *gameover = 0;
        } else if (*replay == 0) {
            *choose = 1;
        }        
      break;
						
    default:
      break;				
	
    }
    break;
  }
}

/********* management of keyboard keys when the player must write his name *****/
void handle_event_name (SDL_Event event_name, int *end,  char *name)
{
    int i = 0;
    switch (event_name.type) {
        case SDL_QUIT:
            * end = 1;
            break;
        
        case SDL_KEYDOWN :
            switch (event_name.key.keysym.sym) {
                case SDLK_ESCAPE :
                case SDLK_RETURN:
                    *end = 1;
                    break;
                    
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
                    
 void handle_event_rule (SDL_Event event_rule, int *quit_rule)
 {
     switch (event_rule.type) {
        case SDL_QUIT:
            * quit_rule = 1;
            break;
        
        case SDL_KEYDOWN :
            switch (event_rule.key.keysym.sym) {
                case SDLK_ESCAPE :
                case SDLK_q:
                case SDLK_RETURN:
                    *quit_rule = 1;
                    break;
                    
                default:
                    break;
    
            }
        default:
            break;
     }
 }
                

   

/********* move the platform in funcion of their position ********/
void move_plat (object_breakout *plat) {
    plat -> position.x = plat -> x;
    plat -> position.y = plat -> y;
}

/**********  give a memory for the 2D char table  **********/
char** allocation2D (int l, int c) {
  char ** Tab = malloc(l*sizeof(char*));
  int i;
  for (i=0; i<l; i++) {
    Tab[i] = malloc(c*sizeof(char));
  }
  return Tab;
}


/******* give a memoru fot the 2D object_breakout table *******/
object_breakout** alloc (int l, int c) {
  object_breakout** Tab = malloc(l*sizeof(object_breakout*));
  int i;
  for (i=0; i<l; i++) {
    Tab[i] = malloc(c*sizeof(object_breakout));
  }
  return Tab;
}



/******** count the number of rows and columns in the file ********/
void count_dimension (FILE *file, int *row, int *col, int *nb_char) 
{
  char cursor;      //take the current value on the file
  bool end_level = false;
  bool end = false;  //for know if we are in the pair and unpair ligne
  int col1 = 1;      //count the number of columns if it's a pair line
  //initialized at 1 for count the \n 
  int col2 = 1;      //count the number of colums if it's a unpair line
  //idem
  int max_col;       //take the maximum of the two numbers of columns
  cursor = fgetc (file); 
  *nb_char += 1;
  while (cursor != EOF && !end_level) {
    if ( !end && (cursor != '\n') ) {
      if (cursor == '#') {
	end_level = true;
      }
     
	col1 += 1;

    }
    if ( end && (cursor != '\n') ) {
      if (cursor == '#') {
	end_level = true;
      }
      
	col2 += 1;
      
    } 
    if ( cursor == '\n' ) {
      *row += 1;
      if (end) {
	end = false;
	max_col = max(col1, col2);
	if (max_col > *col) {
	  *col = max_col;      //we put the maximum of the number of columns if
	  // the max is superior at col
	}
	col1 = 1;     // put the numbers of columns at 1 otherwise we will have
	col2 = 1;     // the number of all the character in the file
      }
      else {
	end = true;
      }
    }
    cursor = fgetc (file);
    *nb_char += 1;
  }
}


/******* read the data text  ******/
char** read_data(FILE *file, int  row, int col) 
{  
  char ** T;
  T = allocation2D(row,col);   /*array of 2 dimensions for take the
				 database and declared thanks
				 to the allocation2D function */
  if (file != NULL) {                //read the file only if the file is open

    char cc;                            /*variable which the current 
					  character of the file */
    int i,j;                            //variables to range the array
    
    for(i=0;i<row;i++){                 //put all the contents of the file in 
      for(j=0;j<col;j++){                   //the array
	cc = fgetc(file);
	if ( (j < (col-1)) && (cc == '\n')) {
	  while (j < (col-1)) {
	    T[i][j] = ' ';
	    j++;
	  }
	}
	T[i][j]=cc;
      }
    }

  }
  
  else                         //print an error message if the file is not open
    {
      printf("Impossible d'ouvrir le fichier breakout_data.txt");
    } 
  printf("\n");
  return T;
}



/********* return the maximum between two integers ***********/
int max ( int a, int b) {
  int max_int = a;
  if ( b > a ) {
    max_int = b;
  }
  return max_int;
}

/********* return the minimum between two integers ***********/
int min (int a, int b) {
  int min_int = a;
  if (b < a) {
    min_int = b;
  }
  return min_int;
}


/*** load the image ***/
SDL_Surface * load (char * name_file) {
  SDL_Surface *temp, *picture_loaded;
  temp = SDL_LoadBMP(name_file);
  picture_loaded = SDL_DisplayFormat (temp);
  SDL_FreeSurface (temp);
  return picture_loaded;
}


/********** set the colokey of the image ********/
void set_colorkey (SDL_Surface *screen, int R, int G, int B, SDL_Surface *sprite) {
  int colorkey;
  colorkey = SDL_MapRGB(screen -> format, R, G, B);
  SDL_SetColorKey (sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}


/******** initilize the briks **********/
object_breakout init_object (int type, float x_act, float y_act, SDL_Surface *screen, int type_bonus) {
    
  object_breakout object;  //creation of the object  
    
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
    object.t_bonus = type_bonus;
    object.print = true;
    
    if (object.t_bonus == REDUC){
      object.speed_y = 2;
      object.width = 17;
      object.height = 17;
      object.sprite = load ("reduce.bmp");
      object.n_frame = 1;
      object.colorkey = SDL_MapRGB(screen->format,0, 0, 162);
      
    }else if (object.t_bonus == GROW){
      object.speed_y = 2;
      object.width = 17;
      object.height = 17;
      object.sprite = load ("grow.bmp");
      object.n_frame = 1;
      object.colorkey = SDL_MapRGB(screen->format,0, 0, 162);
      
    }else if (object.t_bonus == LOST) {
      object.speed_y = 2;
      object.width = 17;
      object.height = 17;
      object.sprite = load ("lost.bmp");
      object.n_frame = 1;
      object.colorkey = SDL_MapRGB(screen->format,0, 0, 162);
      
    } else if (object.t_bonus == LIFE) {
        object.speed_y = 2;
        object.width = 17;
        object.height = 17;
        object.sprite = load ("life.bmp");
        object.n_frame = 1;
        object.colorkey = SDL_MapRGB(screen->format,0, 0, 162);

    } else if (object.t_bonus == SCORE) {
        object.speed_y = 2;
        object.width = 17;
        object.height = 17;
        object.sprite = load ("score.bmp");
        object.n_frame = 1;
        object.colorkey = SDL_MapRGB(screen->format,0, 0, 162);
    }
  }

  
  set_colorkey(screen, 255, 0, 255, object.sprite);
  object.picture.x = 0;
  object.picture.y = 0;
  object.picture.h = object.height;
  object.picture.w = object.width;
  object.position.x = (int) (object.x);
  object.position.y = (int) (object.y);
  object.counter = 0;


       
  return object;
}


/*********  print the contents of  a table ***************/
void print_tab (object_breakout *table, int nb, SDL_Surface *screen) {
  int i;
  for (i=0; i<nb; i++) {
    SDL_BlitSurface(table[i].sprite, &table[i].picture, screen,& table[i].position);
  }
}



/********  make move the ball ************/
void move_ball (object_breakout *ball, object_breakout *platform, SDL_Surface *screen, bool *throw){
  ball -> x += ball -> speed_x;
  ball -> y += ball -> speed_y;
  ball -> position.x = ball -> x;
  ball -> position.y = ball -> y;
    
  if (ball -> x   <  0 ) {
    rebond(ball, 0);
  }
  if (ball -> x   > SCREEN_WIDTH - ball -> width) {
    rebond(ball, 0);
  }
  if (ball -> y  <  0) {
    rebond(ball, 1);
  }
  if (ball -> y > SCREEN_HEIGHT - ball -> height) {
    int life = ball -> life - 1;
    int score = ball -> score;
    *platform =  init_object (PLAT,(SCREEN_WIDTH - PLATFORM_WIDTH) / 2, 
				  SCREEN_HEIGHT - (2 * PLATFORM_HEIGHT),
				  screen, -1);
    
    *ball = init_object (BALL, platform -> position.x + 
		      (PLATFORM_WIDTH / 3), platform -> position.y -      
		      (PLATFORM_HEIGHT), screen, -1);
    *throw = false;
    
    ball -> life = life;
    ball -> score = score;
  }
}


/* Collide between 2 objects */
bool collide(object_breakout *sprite1,object_breakout *sprite2){
  if ((max(sprite1->x,sprite2->x) < min (sprite1 -> x + sprite1 -> width, sprite2->x+sprite2->width))
      && (max(sprite1->y,sprite2->y) < min(sprite1->y+sprite1->height,sprite2->y+sprite2->height))){
    return true;
  }else{
    return false;
  }
}


/***** read the data table to put them on an other table for the gestion of the bricks ****/
void read_table (object_breakout **table, char **tab_data, float *x, float  *y,
		 int row, int col, int *nbI, int *nbII, int *nbIII, int*nbIV, int *nbV, int *nbVI, int *nbVII,
		 SDL_Surface *screen) {
  int i,j;
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      if ( tab_data[i][j] == '1' ) {
	table[0][*nbI] = init_object (1, *x, *y, screen, -1);
	*x += table[0][*nbI].width;
	*nbI += 1;
      }
      else if ( tab_data[i][j] == '2' ) {
	  table[1][*nbII] = init_object (2, *x, *y, screen, -1);
	  *x += table[1][*nbII].width;
	  *nbII += 1;
      }
      else if ( tab_data[i][j] == '3' ) {
	table[2][*nbIII] = init_object (3, *x, *y, screen, -1);
	*x += table[2][*nbIII].width;
	*nbIII += 1;
      }
      else if ( tab_data[i][j] == '4' ) {
	table[3][*nbIV] = init_object (4, *x, *y, screen, -1);
	*x += table[3][*nbIV].width;
	*nbIV += 1;
      }
      else if ( tab_data[i][j] == '5' ) {
	table[4][*nbV] = init_object (5, *x, *y, screen, -1);
	*x += table[4][*nbV].width;
	*nbV += 1;
      }
      else if ( tab_data[i][j] == '6' ) {
	table[5][*nbVI] = init_object (6, *x, *y, screen, -1);
	*x += table[5][*nbVI].width;
	*nbVI += 1;
      }
    else if ( tab_data[i][j] == '7' ) {
	table[6][*nbVII] = init_object (7, *x, *y, screen,- 1);
	*x += table[6][*nbVII].width;
	*nbVII += 1;
      }
      else  if (tab_data[i][j] == '\n') {
	*x = 0;
	*y += DEFAULT_HEIGHT;
      }
      else {
	* x += DEFAULT_WIDTH;
      }
    }
  }
}


/*** make a rebond on the ball *****/
void rebond (object_breakout *ball, int side){
    
  if (side == 1) { 
    ball->speed_y = - ball -> speed_y ;
  }
  if (side == 0) { 
    ball->speed_x = - ball -> speed_x;
  }
  
}


/****** see with precision if we are a collision between two objects ****/
bool collide_precise (object_breakout *sprite1, object_breakout *sprite2, SDL_PixelFormat *format, float *cu, float *cv) {
  
  bool test = collide (sprite1, sprite2);

  if (test) {

    Uint32 *bmp1 = (Uint32 *) malloc (sizeof (Uint32) * sprite1 -> width * sprite1 -> height), *sprite_it, *bmp_it;
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
		    int *q, int *r, int *s, object_breakout *ball,
		    SDL_PixelFormat *format, int nbtype, float *cx, float *cy) {
  bool exit1 = false;  //put true when we have a collision or we have browse all the table 
  int *k = NULL, i = 0;
  while (!exit1 && i < nbtype) {
    
     if (i == 0){
      k = n;
     }
     else if (i == 1){
      k = m;
     }
    else if (i == 2){
      k = l;
    }
    else if (i == 3){
      k = p;
    }
    else if (i == 4){
      k = q;
    }
    else  if (i == 5){
      k = r;
    } else {
        k = s;
    }
        
    
    exit1 = collide_table_aux( table[i], k, ball, format, i+1, cx, cy);
    i++; 
  }
  return exit1;
}
   
/***** look if we are a collision between a brick and the ball into the table ******/
bool collide_table_aux (object_breakout *table , int *n, object_breakout *ball, SDL_PixelFormat *format, int type, float *u, float *v) {
  bool exit2 = false;
  int i = 0, j;
  int pas = 0.005;
  bool g, d, h, b;
  while (!exit2 && i < *n) {
    if (collide_precise (ball, &table[i], format, u, v)) {
      g = (*u - pas <= table[i].x) && (table[i].x <= *u + pas);
      d =  table[i].x + table[i].width >= *u ;
      h =( *v - pas <= table[i].y) && (table[i].y <= *v + pas);
      b = table[i].y + table[i].height >= *v;
      if (b || h) {
	rebond (ball, 1);
	exit2 = true;
      }
       if (g || d)  {
	rebond (ball, 0);
	exit2 = true;
      }
      
      if (type != BRICKIV) {
	table[i].c_frame += 1;
	if (table[i].c_frame == table[i].n_frame) {
	  for (j=i; j < *n-1; j++) {
	    table[j] = table[j+1];
	  }
	  *n = *n - 1;
	  /* increase in score */
	  if ( (type == BRICKI) || (type == BRICKV) ) {
	      ball -> score += 1;
	  }
	  if ( (type == BRICKII) || (type == BRICKVI) ) {
	      ball -> score += 3;
	  }
	  if  ( (type == BRICKIII) || (type == BRICKVII) ) {
	      ball -> score += 5;
	  }
	 
	}
	else {
	  table[i].picture.x = table[i].c_frame * table[i].width;
	}
      }
    }
    i++;
  }
  return exit2;
}
      

/**** loke if we are a collision between the platform and the ball ******/
void collide_platform (object_breakout *plat, object_breakout *ball, SDL_PixelFormat *format) {
  
  float mx, my, xa, ya;
  float dist;
  float cx = 0, cy = 0;
  bool g, d, h;
  
  if (collide_precise(ball, plat, format, &cx, &cy)) {
    g = plat -> x == cx;
    d = plat -> x + plat -> width >= cx;
    h = plat -> y == cy;
    
    mx = plat -> x + (plat -> width / 2);
    my = plat -> y;
    dist = sqrt( ( (cx - mx) * (cx - mx) ) + ( (cy - my) * (cy - my) ) );
    
    if (h) {
      if (cx > mx){          //collide after the half of the platform
	xa = cos (2 * M_PI / dist); 
	ya = -sin (2 * M_PI / dist);
	ball -> speed_x = xa*SPEEDX;
	ball -> speed_y = ya*SPEEDY;
      }else {
	xa = -cos (2 * M_PI / dist); 
	ya = -sin (2 * M_PI / dist);
	ball -> speed_x = xa*SPEEDX;
	ball -> speed_y = ya*SPEEDY;
      }
    } 
    else if (g || d) {
      rebond(ball, 0);
    }
  } 
}
      
/******* look if there is a collision between the platform and the edges of the screen ********/
void collide_screen (object_breakout *platform) {
    if (platform -> x <= 0) {
                platform -> x = 0; 
    }
    if (platform -> x >= SCREEN_WIDTH - PLATFORM_WIDTH)  {
                platform -> x = SCREEN_WIDTH - PLATFORM_WIDTH;
    }
}


/****** draw the bakground on the screen **********/
void draw_background (SDL_Surface *background, SDL_Surface *screen) {
    for (int x = 0; x < SCREEN_WIDTH / BG_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT / BG_HEIGHT; y++) { 
            SDL_Rect position;
            position.x = x * BG_WIDTH;
            position.y = y * BG_HEIGHT;
            SDL_BlitSurface(background, NULL, screen, &position);
        }
    }
}

/***** print an object_breakout *****/
void print_object (object_breakout *object, SDL_Surface *screen) {
    SDL_BlitSurface (object -> sprite, &object -> picture, screen, &object -> position);
}


/**** print different text on the screen ****/
void print_text (const char *text, int val, SDL_Surface *screen, int pos_x, int pos_y, int size, int select) {
  
    TTF_Font *font = TTF_OpenFont("A Love of Thunder.ttf", size);
     SDL_Color color = {0,0,0,0};
    if (select == 1) {
        color.r = 255;
    } else if (select == 2) {
        color.g = 250;
    } else if (select == 3) {
        color.b = 255;
    }
    
    if ( val != -1 ) {
      char text_val [50];
      SDL_Surface *sprite_text_val;
      SDL_Rect position_text_val;
      sprintf (text_val, "%d", val);
      sprite_text_val = TTF_RenderUTF8_Solid (font, text_val, color);
      position_text_val.x = pos_x + 100;
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


/***** creation of the menu ***********/
void menu (int *exit, SDL_Surface *screen, SDL_Surface *background) {
  int begin = 0;
  int play = 1;
  int rule = 0;
  while (!begin)
  {
    SDL_Event event_menu;
    if (SDL_PollEvent(&event_menu)) {
      handle_event_menu (event_menu, exit, &begin, screen, background, &play);
    }
    if (!play) {
        rule = 1;
    } else {
        rule = 0;
    }
    draw_background (background, screen);
    int i;
    for (i = 0; i<5; i++) {
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 0, SCREEN_HEIGHT/8 + i, 8, 2);
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 
                SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/8 + 200 + i, 8, 3);
    }
    print_text ("Breakout", -1, screen, SCREEN_WIDTH / 60, SCREEN_HEIGHT / 8, 190, 0);
    print_text ("Play", -1, screen, SCREEN_WIDTH / 20,  2 * SCREEN_HEIGHT / 3, 150, play);
    print_text ("Rules", -1, screen, SCREEN_WIDTH / 2,  2 * SCREEN_HEIGHT / 3, 150, rule);
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
}


/******* creation of the lose menu ********/
void lose (int *exit, int *gameover, SDL_Surface *screen, SDL_Surface *background, FILE *file, int score) {
   int choose = 0;
   int replay = 1;
   int quit = 0;
   int i;
   draw_background (background, screen);
   print_text ("Game over", -1, screen, SCREEN_WIDTH / 60, SCREEN_HEIGHT / 60, 170, 0);
    for (i = 0; i<5; i++) {
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 0, SCREEN_HEIGHT / 60 + i, 8, 2);
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 
                SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT / 60 + 200 + i, 8, 3);
    }
    ranking (screen, background, score, 0);
   while (!choose) {
     SDL_Event event_lose;
     if (SDL_PollEvent (&event_lose)) {
       handle_event_lose (event_lose,  exit, gameover, &choose, &replay);
     }
     if (replay) {
         quit = 0;
     } else {
         quit = 1;
     }
     draw_background (background, screen);
    for (i = 0; i<5; i++) {
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 0, SCREEN_HEIGHT / 60 + i, 8, 2);
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 
                SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT / 60 + 200 + i, 8, 3);
    }
     print_text ("Game over", -1, screen, SCREEN_WIDTH / 60, SCREEN_HEIGHT / 60, 170, 0);
    print_text ("Replay", -1, screen, SCREEN_WIDTH / 60,  2 * SCREEN_HEIGHT / 3, 150, replay);
    print_text ("Quit", -1, screen, 2 * SCREEN_WIDTH / 3 -  50,  2 * SCREEN_HEIGHT / 3, 150, quit);
     SDL_UpdateRect (screen, 0, 0, 0, 0);
   }
   rewind (file);
}

/******* creation of the win menu ********/
void win (int *exit, int *finish_level,  SDL_Surface *screen, SDL_Surface *background, FILE *file, int score) {
  int choose = 0;
  int replay = 1;
  int quit = 0;
  int i;
  draw_background (background, screen);
  for (i = 0; i<5; i++) {
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 0, SCREEN_HEIGHT / 60 + i, 8, 2);
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 
                SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT / 60 + 200 + i, 8, 3);
    }
  print_text ("Win", -1, screen, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 60, 190, 0);
  ranking (screen, background, score, 1);
  while (!choose) {
    SDL_Event event_win;
    if (SDL_PollEvent (&event_win)) {
      handle_event_lose (event_win, exit, finish_level, &choose, &replay);
    }
    if (replay) {
         quit = 0;
     } else {
         quit = 1;
     }
    for (i = 0; i<5; i++) {
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 0, SCREEN_HEIGHT / 60 + i, 8, 2);
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 
                SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT / 60 + 200 + i, 8, 3);
    }
    print_text ("Win", -1, screen, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 60, 190, 0);
    print_text ("Replay", -1, screen, SCREEN_WIDTH / 60,  2 * SCREEN_HEIGHT / 3, 150, replay);
    print_text ("Quit", -1, screen, 2 * SCREEN_WIDTH / 3 -  50,  2 * SCREEN_HEIGHT / 3, 150, quit);
    //ranking (screen);
    SDL_UpdateRect (screen, 0, 0, 0, 0);
  }
  rewind (file);
}


void print_name (SDL_Surface *screen, SDL_Surface *background, char *name, int win)
{
    draw_background (background, screen);
    SDL_EnableKeyRepeat(0,0);
    int end = 0;
    int i;
    int x = SCREEN_WIDTH / 2 + 30;
    int y = SCREEN_HEIGHT/3 + 30;
    while (!end) {
	
        SDL_Event event_name;
        if (SDL_PollEvent (&event_name)) {
            handle_event_name (event_name, &end,  name);
        }
        draw_background (background, screen);
        for (i = 0; i<5; i++) {
            print_text("_________________________________________________________________________________________________________________________", -1,screen, 0, SCREEN_HEIGHT / 60 + i, 8, 2);
            print_text("_________________________________________________________________________________________________________________________", -1,screen, 
                    SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT / 60 + 200 + i, 8, 3);
    }
        if (win) {
            print_text ("Win", -1, screen, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 60, 190, 0);
        } else {
             print_text ("Game over", -1, screen, SCREEN_WIDTH / 60, SCREEN_HEIGHT / 60, 170, 0);
        }
        print_text (name, -1, screen, x, y, 32, 0);
        print_text ("What is your name ? ", -1, screen, SCREEN_WIDTH / 3, SCREEN_HEIGHT/3, 32, 0);
	print_text ("My name is ", -1, screen,   SCREEN_WIDTH / 3, SCREEN_HEIGHT/3 + 30, 32, 0);

        SDL_UpdateRect (screen, 0, 0, 0, 0);
    }
    SDL_EnableKeyRepeat(10, 10);
}


void ranking (SDL_Surface *screen, SDL_Surface *background, int score_player, int win) 
{
  FILE *file = fopen ("rank.txt", "r+");
  FILE *replace_file = fopen ("replace_rank.txt", "w+");
  
  char name [MAX_SIZE] = "";
  
  print_name (screen, background, name, win);
  
  char first [MAX_SIZE];
  char second [MAX_SIZE];
  char third [MAX_SIZE];
  char score_f [MAX_SIZE];
  char score_s [MAX_SIZE];
  char score_t [MAX_SIZE];

  int sc_f, sc_s, sc_t;
  
  char cursor[MAX_SIZE]; 
  
  if (file != NULL) {
    
    if (fgets (cursor, MAX_SIZE, file) != NULL) {
      sprintf (first, "%s", cursor);
    }
    if (fgets (cursor, MAX_SIZE, file) != NULL) {
      sprintf  (second, "%s", cursor);
    }
    if (fgets (cursor, MAX_SIZE, file) != NULL) {
      sprintf  (third, "%s",cursor);
    }
    if (fgets (cursor, MAX_SIZE, file) != NULL) {
      sprintf  (score_f, "%s",cursor);
    }
    if (fgets (cursor, MAX_SIZE, file) != NULL) {
      sprintf  (score_s, "%s", cursor);
    }
    if (fgets (cursor, MAX_SIZE, file) != NULL) {
      sprintf  (score_t, "%s", cursor);
    }
    
    sc_f = atoi (score_f);
    sc_s = atoi (score_s);
    sc_t = atoi (score_t);
    if ( (score_player > sc_f) || (*first == '#') ) {
      sprintf(third, "%s", second);
      sprintf(second, "%s", first);
      sprintf(first, "%s", name);
      strcat (first, "\n");
      sc_t = sc_s;
      sc_s = sc_f;
      sc_f = score_player;
      
      
    } else if ( (score_player > sc_s) || (*second == '#')  ) {
      sprintf(third, "%s", second);
      sprintf(second, "%s", name);
      strcat (second, "\n");
      sc_t = sc_s;
      sc_s = score_player;
      
    } else if ( (score_player > sc_t) ||(*third == '#')  ) {
      sprintf(third, "%s", name);
      strcat (third, "\n");
      sc_t = score_player;
  
    }
    sprintf(score_f, "%d", sc_f);
    sprintf(score_s, "%d", sc_s);
    sprintf(score_t, "%d", sc_t);
    
    
    draw_background (background, screen);
    print_text("1 : ", -1, screen, (SCREEN_WIDTH / 3) + 25,  SCREEN_HEIGHT / 3 + 50, 32, 0);
    print_text(first, -1, screen, SCREEN_WIDTH / 3 + 75,   SCREEN_HEIGHT / 3 + 50, 32, 0);
    print_text("", sc_f, screen, SCREEN_WIDTH / 3 + 275,   SCREEN_HEIGHT / 3 + 50, 32, 0);
    print_text("2 : ", -1, screen, (SCREEN_WIDTH / 3) + 25,  SCREEN_HEIGHT / 3 + 85, 32, 0);
    print_text(second, -1, screen, SCREEN_WIDTH / 3 + 75,  SCREEN_HEIGHT / 3 + 85, 32, 0);
    print_text("", sc_s, screen, SCREEN_WIDTH / 3 + 275 ,  SCREEN_HEIGHT / 3 + 85, 32, 0);
    print_text("3 : ", -1, screen, (SCREEN_WIDTH / 3) + 25 ,  SCREEN_HEIGHT / 3 + 120, 32, 0);
    print_text(third, -1, screen, SCREEN_WIDTH / 3 + 75,  SCREEN_HEIGHT / 3 + 120, 32, 0);
    print_text("", sc_t, screen, SCREEN_WIDTH / 3 + 275,  SCREEN_HEIGHT / 3 + 120, 32, 0);
    
    strcat (score_f, "\n");
    strcat (score_s, "\n");
    strcat (score_t, "\n");
    
    fputs (first, replace_file);
    fputs (second, replace_file);
    fputs (third, replace_file);
    fputs (score_f, replace_file);
    fputs (score_s, replace_file);
    fputs (score_t, replace_file);
    
    fclose(file);
    fclose(replace_file);
    remove("rank.txt");
    rename("replace_rank.txt","rank.txt");
    
    
  } else {
    printf ("the file rank is not correctly open \n");
  }
  
}


void rule (SDL_Surface *screen, SDL_Surface *background)
{
    SDL_Event event_rule;
    int quit_rule = 0;
    int x = 75 ;
    int i;
    int y = SCREEN_HEIGHT / 3 + 20;
    draw_background(background, screen);
    for (i = 0; i<5; i++) {
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 0, SCREEN_HEIGHT/30 + i, 8, 2);
        print_text("_________________________________________________________________________________________________________________________", -1,screen, 
                SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT / 60 + 220 + i, 8, 3);
    }
    print_text("Rules", -1, screen, SCREEN_WIDTH/4, SCREEN_HEIGHT/30, 190, 0);
    print_text ("* The blues and yellows bricks break with 1 hit", -1, screen, x,  y, 32, 0);
    print_text ("* The greens and beiges bricks break with 2 hits", -1, screen, x, y + 40, 32, 0);
    print_text ("* The pinks and reds bricks break with 3 hits", -1, screen, x, y + 80, 32, 0);
    print_text ("* The darks brick don't break", -1, screen, x, y + 120, 32, 0);
    print_text ("* The goal it's to break every bricks ", -1, screen, x, y + 160, 32, 0);
    print_text ("exept the darks.", -1, screen, x + 50, y + 200  , 32, 0);
    print_text ("* To throw the ball press the space button.", -1, screen, x, y + 240, 32, 0);
    print_text ("* The platform move right and left", -1, screen, x, y + 280, 32, 0);
    print_text (" with the arrows.", -1, screen, x + 50, y + 320, 32, 0);
    print_text ("To go back in the menu, press ", -1, screen, 2, y + 380, 60, 0);
    print_text ("the escape or return button", -1, screen, x, y + 440, 60, 0);
    SDL_UpdateRect (screen, 0, 0, 0, 0);
    
    while (!quit_rule) {
        if (SDL_PollEvent (&event_rule)) {
            handle_event_rule (event_rule, &quit_rule);
        }
    }
}


/* Gives a random number between two ends */
int nb_random () {
  int nb;
  /*to have a random number*/
  nb = rand()%ALEA;
  return nb;
}

/*add an element in an array and initialize*/
void add (object_breakout *tab, int *n, int cx, int cy, SDL_Surface *screen, int type_bonus){
  tab[*n] = init_object (BONUS, cx, cy, screen, type_bonus);
  *n += 1;
}

/*delete an element in an array*/
void del (object_breakout *tab, int *n, int cur){
  for (int j = cur; j < *n-1; j++){
    SDL_FreeSurface(tab[j].sprite);
    tab[j] = tab[j+1];
  }
  *n -= 1;
}

/* Handle the POWER */
/*reduce the size of the platform*/
void power (object_breakout *power, int *n, SDL_Surface *screen, int cx, int cy)
{
  /*int lucky = nb_random();
  if (lucky == REDUC){
    add(power, n, cx, cy, screen,REDUC);
    }else if (lucky == GROW){
    add(power, n, cx, cy, screen,GROW);
    } else if (luck == LOST) {
        add (power, n, cx, cy, screen, LOST);
    } else if (luck == LIFE) { 
        add (power, n, cx, cy, screen, LIFE);
    } else if (luck == SCORE) { */
        add (power, n, cx, cy, screen, SCORE);
    //}
}


/********  make move the ball ************/
void move_power (object_breakout *reduc, int *n) {
  int i;
  for(i=0;i<*n;i++){
    if (reduc[i].print) {
      reduc[i].y = reduc[i].y + reduc[i].speed_y;
      reduc[i].position.x = reduc[i].x;
      reduc[i].position.y = reduc[i].y;
      if (reduc[i].y > SCREEN_HEIGHT - reduc[i].height) {
	del(reduc,n,i);
	}
    }
  }
}


/*******  handle the collide between bonus and platform  *************/
void collide_power (object_breakout *platform, object_breakout *power, 
                    object_breakout *ball, SDL_Surface *screen, int *n, int *gameover){
  float x=0 ,y=0;
  int i;
  for (i=0; i<*n; i++){
      if (collide_precise(&power[i], platform, screen->format,&x,&y)){
      power[i].print = false;
      if (power[i].t_bonus == REDUC){
	platform -> width = 32;
	platform -> sprite = load("LittlePlatform.bmp");
	set_colorkey(screen, 255, 0, 255, platform->sprite);
	power[i].counter = TIME_REDUCE;
      }else if (power[i].t_bonus == GROW){
	  platform -> width = 128;
	  platform->picture.w = platform->width;
	  printf("platform -> width = %d \n",platform -> width);
	  platform -> sprite = load("BigPlatform.bmp");
	  set_colorkey(screen, 255, 0, 255, platform->sprite);
	  power[i].counter = TIME_GROW;
      } else if (power[i].t_bonus == LOST) {
          *gameover = 1;
      } else if (power[i].t_bonus == LIFE) {
          ball -> life += 1;
          del (power, n, i);
      } else if (power[i].t_bonus == SCORE) {
          ball -> score += 10;
          del (power, n, i);
      }
    }
  } 
}

/*Handle the bonus time*/
void power_time (object_breakout *platform, object_breakout *tab, int *n, SDL_Surface *screen){
  int i;
  for (i=0; i<*n; i++) {
    if (! tab[i].print){
      tab[i].counter = tab[i].counter - 1;
      if (tab[i].counter <= 0){
	if ((tab[i].t_bonus == REDUC) || (tab[i].t_bonus == GROW)){
	  del(&tab[i],n,i);
	  platform -> width = 64;
	  platform -> sprite = load("NormalPlatform.bmp");
	  set_colorkey(screen, 255, 0, 255, platform->sprite);
	}
      }
    }
  }
}
