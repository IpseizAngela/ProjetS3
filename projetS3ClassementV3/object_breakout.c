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
	ball -> speed_y = -2;
	*throw = true;
      } 
    default:
      break;
    }
    break;
  }
}

/************** management of keyboard keys for the menu ************/
void handle_event_menu (SDL_Event event_menu, int *exit, int *begin) {
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
						  
      case SDLK_RETURN:
	*begin = 1;
	break;
						  
      default:
	break;				
	  
      }
      break;
  }
}
   
   
/************** management of keyboard keys for the lose menu ************/
void handle_event_lose (SDL_Event event_lose,  int *exit, int *gameover, int *choose) {
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
						
    case SDLK_RETURN:
      *choose = 1;
      *exit = 0;
      *gameover = 0;
      break;
						
    default:
      break;				
	
    }
    break;
  }
}

/********* management of keyboard keys when the player must write his name *****/
void handle_event_name (SDL_Event event_name, int *end,  int *x, int y, SDL_Surface *screen, char *name)
{
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
                    
                case SDLK_a :
                    print_text("a", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "a");
                    break;
                case SDLK_b :
                    print_text("b", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "b");
                    break;
                case SDLK_c :
                    print_text("c", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "c");
                    break;
                case SDLK_d :
                    print_text("d", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "d");
                    break;
                case SDLK_e :
                    print_text("e", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "e");
                    break;
               case SDLK_f :
                    print_text("f", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "f");
                    break;
                case SDLK_g :
		    *x += 5;
                    print_text("g", -1, screen,  *x, y , 32);
		    *x += 25;
		    sprintf (name, "%s", "g");
                    break;
               case SDLK_h :
                    print_text("h", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "h");
                    break;
                case SDLK_i :
                    print_text("i", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "i");
                    break;
                case SDLK_j :
                    print_text("j", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "j");
                    break;
                case SDLK_k :
                    print_text("k", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "k");
                    break;
                case SDLK_l :
                    print_text("l", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "l");
                   break;
                case SDLK_m :
                    print_text("m", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "m");
                    break;
                case SDLK_n :
                    print_text("n", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "n");
                    break;
                case SDLK_o :
                    print_text("o", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "o");
                    break;
                case SDLK_p :
                    print_text("p", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "p");
                    break;
                case SDLK_q :
                    print_text("q", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "q");
                    break;
                case SDLK_r :
                    print_text("r", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "r");
                    break;
                case SDLK_s :
                    print_text("s", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "s");
                    break;
                case SDLK_t :
                    print_text("t", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "t");
                    break;
                case SDLK_u :
                    print_text("u", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "u");
                    break;
                case SDLK_v :
                    print_text("v", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "v");
                    break;
                case SDLK_w :
                    print_text("w", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "w");
                    break;
                case SDLK_x :
                    print_text("x", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "x");
                    break;
                case SDLK_y :
                    print_text("y", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "y");
                    break;
                case SDLK_z :
                    print_text("z", -1, screen,  *x, y , 32);
		    *x += 20;
		    sprintf (name, "%s", "z");
                    break; 
                default:
                    break;
            }
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
/*void set_colorkey (SDL_Surface *screen, int colorkey, SDL_Surface *sprite) {
  SDL_SetColorKey (sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}*/



/******** initilize the briks **********/
object_breakout init_object (int type, float x_act, float y_act, SDL_Surface *screen) {
    
  object_breakout object;  //creation of the object  
    
  object.x = x_act;
  object.y  = y_act;
  object.c_frame = 0;
  object.colorkey = SDL_MapRGB (screen -> format, 255, 0, 255);
    
  if (type == BRICKI) {
    object.width = 32;
    object.height = 16;
    object.sprite = load ("Brick1.bmp");
    //set_colorkey(screen, 255, 0, 255, object.sprite);
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
  //set_colorkey(screen, object.colorkey, object.sprite);
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
    //ball -> y = 0;
    *platform =  init_object (PLAT,(SCREEN_WIDTH - PLATFORM_WIDTH) / 2, 
				  SCREEN_HEIGHT - (2 * PLATFORM_HEIGHT),
				  screen);
    
    *ball = init_object (5, platform -> position.x + 
		      (PLATFORM_WIDTH / 3), platform -> position.y -      
		      (PLATFORM_HEIGHT), screen);
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
		 int row, int col, int *nbI, int *nbII, int *nbIII, int*nbIV,
		 SDL_Surface *screen) {
  int i,j;
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      if ( tab_data[i][j] == '1' ) {
	table[0][*nbI] = init_object (1, *x, *y, screen);
	*x += table[0][*nbI].width;
	*nbI += 1;
      }
      else if ( tab_data[i][j] == '2' ) {
	  table[1][*nbII] = init_object (2, *x, *y, screen);
	  *x += table[1][*nbII].width;
	  *nbII += 1;
      }
      else if ( tab_data[i][j] == '3' ) {
	table[2][*nbIII] = init_object (3, *x, *y, screen);
	*x += table[2][*nbIII].width;
	*nbIII += 1;
      }
      else if ( tab_data[i][j] == '4' ) {
	table[3][*nbIV] = init_object (4, *x, *y, screen);
	*x += table[3][*nbIV].width;
	*nbIV += 1;
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
void collide_table (object_breakout ** table, int *n, int *m, int *l, int *p, object_breakout *ball, SDL_PixelFormat *format, int nbtype) {
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
    else {
      k = p;
    }
    exit1 = collide_table_aux( table[i], k, ball, format, i+1);
    i++; 
  }
}
   
/***** look if we are a collision between a brick and the ball into the table ******/
bool collide_table_aux (object_breakout *table , int *n, object_breakout *ball, SDL_PixelFormat *format, int type) {
  bool exit2 = false;
  int i = 0, j;
  float u = 0., v = 0.;
  int pas = 0.005;
  bool g, d, h, b;
  while (!exit2 && i < *n) {
    if (collide_precise (ball, &table[i], format, &u, &v)) {
      g = (u - pas <= table[i].x) && (table[i].x <= u + pas);
      d =  table[i].x + table[i].width >= u ; //(u + pas >= table[i].x + table[i].width) && ( table[i].x + table[i].width >= u - pas);
      h =( v - pas <= table[i].y) && (table[i].y <= v + pas);
      b = table[i].y + table[i].height >= v; //(v + pas >= table[i].y + table[i].height ) && (table[i].y + table[i].height >= v - pas);
      printf("tab x %f, u %f\n", table[i].x, u);
      printf("tab y %f, v %f\n", table[i].y, v);
      if (b || h) {
	printf("b ou h\n");
	rebond (ball, 1);
	exit2 = true;
      }
       if (g || d)  {
	printf("g ou d\n");
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
	  if (type == BRICKI) {
	      ball -> score += 1;
	  }
	  if (type == BRICKII) {
	      ball -> score += 3;
	  }
	  if  (type == BRICKIII) {
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
  int pas = 0.05;
 
  if (collide_precise(ball, plat, format, &cx, &cy)) {
    g = (cx - pas <= plat -> x) &&  (plat -> x <= cx + pas);
    d = plat -> x + plat -> width >= cx ; //(cx + pas >= plat -> x + plat -> width) && (plat -> x + plat -> width >= cx - pas);
    h =( cy - pas <= plat -> y) &&  (plat -> y  <= cy + pas);
  
      mx = plat -> x + (plat -> width / 2);
      my = plat -> y;
      dist = sqrt( ( (cx - mx) * (cx - mx) ) + ( (cy - my) * (cy - my) ) );
   
      if (h) {
	xa = cos (2 * M_PI / dist);
	ya = -sin (2 * M_PI / dist);
	ball -> speed_x = xa;
	ball -> speed_y = ya;
      } 
      else if (g || d) {
	rebond(ball, 0);
      }
    } 
}
      
/******* look if there is a collision between the platform and the edges of the screen ********/
void collide_screen (object_breakout *platform) {
    if (platform -> position.x <= 0) {
                platform -> position.x = 0; 
    }
    if (platform -> position.x >= SCREEN_WIDTH - PLATFORM_WIDTH)  {
                platform -> position.x = SCREEN_WIDTH - PLATFORM_WIDTH;
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
void print_text (const char *text, int val, SDL_Surface *screen, int pos_x, int pos_y, int size) {
  
    TTF_Font *font = TTF_OpenFont("A Love of Thunder.ttf", size);
    SDL_Color color = {0,0,0,0};
    
    if ( val != -1 ) {
      char text_val [50];
      SDL_Surface *sprite_text_val;
      SDL_Rect position_text_val;
      sprintf (text_val, "%d", val);
      sprite_text_val = TTF_RenderUTF8_Solid (font, text_val, color);
      position_text_val.x = pos_x + 75;
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
  while (!begin)
  {
    SDL_Event event_menu;
    if (SDL_PollEvent(&event_menu)) {
      handle_event_menu (event_menu, exit, &begin);
    }
      draw_background (background, screen);
      print_text ("Breakout", -1, screen, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 3, 150);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
}


/******* creation of the lose menu ********/
void lose (int *exit, int *gameover, SDL_Surface *screen, SDL_Surface *background, FILE *file) {
   int choose = 0;
   while (!choose) {
     SDL_Event event_lose;
     if (SDL_PollEvent (&event_lose)) {
       handle_event_lose (event_lose,  exit, gameover, &choose);
     }
     draw_background (background, screen);
     print_text ("Gameover", -1, screen, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 3, 150);
     print_text ("Press the return key for replay or escape for exit", -1, screen, (SCREEN_WIDTH / 4)   ,  (2*SCREEN_HEIGHT) / 3, 20);
     //ranking (screen);
     SDL_UpdateRect (screen, 0, 0, 0, 0);
   }
   rewind (file);
}

/******* creation of the win menu ********/
void win (int *exit, int *finish_level,  SDL_Surface *screen, SDL_Surface *background, FILE *file, int score) {
  int choose = 0;
  draw_background (background, screen);
      ranking (screen, background, score);
  while (!choose) {
    SDL_Event event_win;
    if (SDL_PollEvent (&event_win)) {
      handle_event_lose (event_win, exit, finish_level, &choose);
    }
    
    print_text ("Win", -1, screen, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 150);
    print_text ("Press the return key for replay or escape for exit", -1, screen, (SCREEN_WIDTH / 4)   ,  (2*SCREEN_HEIGHT) / 3, 20);
    
    //ranking (screen);
    SDL_UpdateRect (screen, 0, 0, 0, 0);
  }
  rewind (file);
}


void print_name (SDL_Surface *screen, SDL_Surface *background, char *name)
{
    draw_background (background, screen);
    SDL_EnableKeyRepeat(0,0);
    int end = 0;
    int x = 2 * SCREEN_WIDTH / 3;
    int y = 30;
    while (!end) {
	
        SDL_Event event_name;
        if (SDL_PollEvent (&event_name)) {
            handle_event_name (event_name, &end, &x, y, screen, name);
        }
        
        print_text ("Quel est votre nom ? ", -1, screen, SCREEN_WIDTH / 2, 2, 32);
        print_text ("Win", -1, screen, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3, 150);
        print_text ("Press the return key for replay or escape for exit", -1, screen, (SCREEN_WIDTH / 4)   ,  (2*SCREEN_HEIGHT) / 3, 20);
	print_text ("My name is ", -1, screen,  SCREEN_WIDTH / 3, 30, 32);

        SDL_UpdateRect (screen, 0, 0, 0, 0);
    }
    SDL_EnableKeyRepeat(10, 10);
}

/*void ranking (SDL_Surface *screen)
{
    FILE *file_replacement_ranking = fopen("replacement_ranking.txt", "r+");
    //char player [MAX_SIZE];
    
    char first[MAX_SIZE];
    sprintf (first, "%s", "1 : ");
    char second[MAX_SIZE];
    sprintf (second, "%s", "2 : ");
    char third[MAX_SIZE];
    sprintf (third, "%s", "3 : ");
    //char Nom[MAX_SIZE];
    
    char classement [3][TAILLE_MAX];
    sprintf(classement[0], "%s", "1 : ");
    sprintf(classement[1], "%s", "2 : ");
    sprintf(classement[2], "%s", "3 : ");


   SDL_Rect positionPrem, positionDeux, positionTrois;
    positionPrem.x = 0;
    positionPrem.y = SCREEN_HEIGHT - 105;
    positionDeux.x = 0;
    positionDeux.y = SCREEN_HEIGHT - 70;
    positionTrois.x = 0;
    positionTrois.y = SCREEN_HEIGHT - 35;
   
    int ask = 0;

    if (!ask) {
        printf ("What is your name ? \n");
        scanf ("%s", Nom);
        ask = true;
    }
    scanf(player, "%d", ball -> score);
    strcat (Nom, player);
    printf("Player : %c \n", Nom);
					
	  int i = 0;
	  while ( fgets(classScore, TAILLE_MAX, fichierScore) != NULL) {
	    fgets(classNom, TAILLE_MAX, fichierNom);
	    if (Tab_Vaisseau[0].score > atoi(classScore)) {
	      temp = Tab_Vaisseau[0].score ;
	      Tab_Vaisseau[0].score = atoi(classScore);
	      sprintf (classScore, "%d", temp);
	      strcat (classScore, "\n");  //concatène 2 chaine de caracteres
	      sprintf (tempNom, "%s", Nom);
	      sprintf (Nom, "%s", classNom);
	      sprintf (classNom, "%s", tempNom);
	      strcat (classNom,  "\n");
	    }	
	    fputs(classScore, fichierRemplacementScore); 
	    fputs(classNom, fichierRemplacementNom);
	    strcat (classement[i], classNom);
	    strcat (classement[i], classScore);
		 				
	    i += 1;
		 				
	  }
    int i = 1;
    char cursor;
    if (file_ranking != NULL) {
        cursor = fgetc(file_ranking);
       // fputs (cursor, file_replacement_ranking);
        while (cursor != EOF) {
            while (cursor != '\n') {
                if (i == 1) {
                    strcat (first, cursor);
                } else if (i == 2) {
                    strcat (second, cursor);
                }else if (i == 3) {
                    strcat (third, cursor);
                }
                cursor = fgetc(file_ranking);
               // fputs(cursor, file_replacement_ranking);
            }
            i++;
        }                
    } else {
        printf ("Le fichier ranking n'existe pas \n");
    }
   // remove (file_ranking);
    //rename (file_replacement_ranking, file_ranking);
    close (file_replacement_ranking);
    close (file_ranking);
    print_text (&first, -1, screen, 0,  SCREEN_HEIGHT - 105, 32);
    print_text (&second, -1, screen , 0,  SCREEN_HEIGHT - 70, 32);
    print_text (&third, -1, screen , 0,  SCREEN_HEIGHT - 35, 32);
}*/
                    
/*void ranking (SDL_Surface *screen) 
{
    FILE *file_score = NULL;
    file_score = fopen("ranking_score.txt", "r+");
    FILE *file_name = NULL;
    file_name = fopen("ranking_name.txt", "r+");
    FILE *file_replacement_score = NULL;
    file_replacement_score = fopen("remplacementScore.txt", "w+");
    FILE *file_replacement_name = NULL;
    file_replacement_name = fopen("replacement_name.txt", "w+");

    char ranking_score[MAX_SIZE];
    char ranking_name[MAX_SIZE];
	 	
    //demande du nom du joueur dans le terminal
    char name[MAX_SIZE];	 	
    int temp; 
    //pour faire une sauvegarde du score pendant l'echanger de deux variables
    char temp_name[MAX_SIZE]; //idem pour le nom
	 	
    bool ask = false;  
    //faux si l'on a pas encore demander le nom sinon vrai
    //}
	 	
    //Variables de l'affichage
    char first[MAX_SIZE];
    sprintf (first, "%s", "1 : ");
    char second[MAX_SIZE];
    sprintf (second, "%s", "2 : ");
    char third[MAX_SIZE];
    sprintf (third, "%s", "3 : "); */
	 	
   /* char classement [3][TAILLE_MAX];
    sprintf(classement[0], "%s", "1 : ");
    sprintf(classement[1], "%s", "2 : ");
    sprintf(classement[2], "%s", "3 : ");*/
	 	
    /*TTF_Font *fontClassement;
    fontClassement = TTF_OpenFont ("A Love of Thunder.ttf", 32);

    SDL_Rect positionPrem, positionDeux, positionTrois;
    positionPrem.x = 0;
    positionPrem.y = SCREEN_HEIGHT - 105;
    positionDeux.x = 0;
    positionDeux.y = SCREEN_HEIGHT - 70;
    positionTrois.x = 0;
    positionTrois.y = SCREEN_HEIGHT - 35;*/

/*	if (!ask) {
	  printf ("What is your name ? \n");
	  scanf ("%s", name);
	  ask = true;
        		
	  int i = 1;
 	  while ( fgets(ranking_score, MAX_SIZE, file_score) != NULL)  {//&& (i <= 3)) {
	    fgets(file_name,MAX_SIZE, file_name);*/
	   /* if (Tab_Vaisseau[0].score > atoi(classScore)) {
	      temp = Tab_Vaisseau[0].score ;
	      Tab_Vaisseau[0].score = atoi(classScore);
	      sprintf (classScore, "%d", temp);
	      strcat (classScore, "\n");  //concatène 2 chaine de caracteres
	      sprintf (tempNom, "%s", Nom);
	      sprintf (Nom, "%s", classNom);
	      sprintf (classNom, "%s", tempNom);
	      strcat (classNom,  "\n");
	    }	*/
            /*fputs(ranking_score, file_replacement_score); 
            fputs(ranking_name, file_replacement_name);
           if (i == 1) {
                strcat (first, ranking_name);
                strcat (first, ranking_score);
           }  else if (i == 2) {
                strcat (second, ranking_name);
                strcat (second, ranking_score);
           } else if (i == 3) {
                strcat (third, ranking_name);
                strcat (third, ranking_score);
           }               
	    i += 1;
	 }
		 			printf("sortit\n");
	  remove ("ranking_score.txt");
	  remove ("ranking_name.txt");
	  rename ("file_replacement_score.txt", "ranking_score.txt");
	  rename ("file_replacement_name.txt", "ranking_name.txt");
	  fclose (file_replacement_score);
	  fclose (file_replacement_name);
          fclose (file_score);
	  fclose (file_name);
		 			
        }*/
 				
 				
	/*SDL_Surface *textPrem =
	TTF_RenderUTF8_Solid (fontClassement, classement[0], couleur);
	SDL_Surface *textDeux =
	TTF_RenderUTF8_Solid (fontClassement, classement[1], couleur);
	SDL_Surface *textTrois =
	TTF_RenderUTF8_Solid (fontClassement, classement[2], couleur);
 				
	SDL_BlitSurface (textPrem, NULL, screen, &positionPrem);
	SDL_BlitSurface (textDeux, NULL, screen, &positionDeux);
	SDL_BlitSurface (textTrois, NULL, screen, &positionTrois);
 			  
	SDL_FreeSurface (textPrem);
	SDL_FreeSurface (textDeux);
	SDL_FreeSurface (textTrois);*/
        /*print_text (&first, -1, screen, 0,  SCREEN_HEIGHT - 105, 32);
        print_text (&second, -1, screen , 0,  SCREEN_HEIGHT - 70, 32);
        print_text (&third, -1, screen , 0,  SCREEN_HEIGHT - 35, 32);
 			 
      }*/
void ranking (SDL_Surface *screen, SDL_Surface *background, int score_player) 
{
  FILE *file = fopen ("rank.txt", "r+");
  FILE *replace_file = fopen ("replace_rank.txt", "w+");
  
  char name [MAX_SIZE];
  print_name (screen, background, name);
  
  char first [MAX_SIZE];
  char second [MAX_SIZE];
  char third [MAX_SIZE];
  char score_f [MAX_SIZE];
  char score_s [MAX_SIZE];
  char score_t [MAX_SIZE];

  int sc_f, sc_s, sc_t;
  
  char cursor[MAX_SIZE]; 
  
  if (file != NULL) {
    /*fgets (cursor, MAX_SIZE, file);
    strcat (first, cursor);
    fgets (cursor, MAX_SIZE, file);
    strcat (second, cursor);
    fgets (cursor, MAX_SIZE, file);
    strcat (third,cursor);
    fgets (cursor, MAX_SIZE, file);
    strcat (score_f,cursor);
    fgets (cursor, MAX_SIZE, file);
    strcat (score_s, cursor);
    fgets (cursor, MAX_SIZE, file);
    strcat (score_t, cursor);*/
    fgets (cursor, MAX_SIZE, file);
    sprintf (first, "%s", cursor);
    fgets (cursor, MAX_SIZE, file);
    sprintf  (second, "%s", cursor);
    fgets (cursor, MAX_SIZE, file);
    sprintf  (third, "%s",cursor);
    fgets (cursor, MAX_SIZE, file);
    sprintf  (score_f, "%s",cursor);
    fgets (cursor, MAX_SIZE, file);
    sprintf  (score_s, "%s", cursor);
    fgets (cursor, MAX_SIZE, file);
    sprintf  (score_t, "%s", cursor);
    
    sc_f = atoi (score_f);
    sc_s = atoi (score_s);
    sc_t = atoi (score_t);
    
    if (score_player > sc_f) {
        sprintf(third, "%s", second);
        sprintf(second, "%s", first);
        sprintf(first, "%s", name);
      sc_t = sc_s;
      sc_s = sc_f;
      sc_f = score_player;
      
      
    } else if (score_player > sc_s) {
        sprintf(third, "%s", second);
        sprintf(second, "%s", name);
      sc_t = sc_s;
      sc_s = score_player;
      
    } else if (score_player > sc_t) {
        sprintf(third, "%s", name);
      sc_t = score_player;
  
    }
    sprintf(score_f, "%d", sc_f);
    sprintf(score_s, "%d", sc_s);
    sprintf(score_t, "%d", sc_t);
    
   print_text("1 : ", -1, screen, 0, SCREEN_HEIGHT - 105, 32);
    print_text(first, sc_f, screen, 50, SCREEN_HEIGHT - 105, 32);
   print_text("2 : ", -1, screen, 0, SCREEN_HEIGHT - 70, 32);
    print_text(second, sc_s, screen, 50, SCREEN_HEIGHT - 70, 32);
   print_text("3 : ", -1, screen, 0, SCREEN_HEIGHT - 35, 32);
    print_text(third, sc_t, screen, 50, SCREEN_HEIGHT - 35, 32);
    
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
  
  //printf ("first %s \nsecond %s \nthird %s\nscore_f %s \nscore_s %s\nscore_t %s\n", first, second, third, score_f, score_s, score_t);
}
  