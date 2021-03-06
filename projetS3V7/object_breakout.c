#include "object_breakout.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SPRITE_STEP 5

/************** management of keyboard keys *****************/

void HandleEvent(SDL_Event event, int *quit,  SDL_Rect *position, bool *throw, object_breakout *ball)
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
      *quit = 1;
      break;
    case SDLK_LEFT:
      position->x -= SPRITE_STEP;
      break;
    case SDLK_RIGHT:
      position->x += SPRITE_STEP;
      break;
    case SDLK_SPACE:
      if (!*throw) {
	ball -> x = 10;
	ball -> y = 50;
	ball -> speed_x = 0.2;
	ball -> speed_y = 0;
	*throw = true;
      } 
    default:
      break;
    }
    break;
  }
}



/**********  give a memory for the 2D table  **********/

char** allocation2D (int l, int c) {
  char ** Tab = malloc(l*sizeof(char*));
  int i;
  for (i=0; i<l; i++) {
    Tab[i] = malloc(c*sizeof(char));
  }
  return Tab;
}

object_breakout** alloc (int l, int c) {
  object_breakout** Tab = malloc(l*sizeof(object_breakout*));
  int i;
  for (i=0; i<l; i++) {
    Tab[i] = malloc(c*sizeof(object_breakout));
  }
  return Tab;
}


/******** count the number of rows and columns in the file ********/

void count_dimension (FILE *file, int *row, int *col) 
{
  char cursor;      //take the current value on the file
  bool end = false;  //for know if we are in the pair and unpair ligne
  int col1 = 1;      //count the number of columns if it's a pair line
  //initialized at 1 for count the \n 
  int col2 = 1;      //count the number of colums if it's a unpair line
  //idem
  int max_col;       //take the maximum of the two numbers of columns
  cursor = fgetc (file); 
  while (cursor != EOF) {
    if ( !end && (cursor != '\n') ) {
      col1 += 1;
    }
    if ( end && (cursor != '\n') ) {
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
  }
  printf ("Row : %d, Col : %d \n", *row, *col);
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

int min (int a, int b) {
  int min_int = a;
  if (b < a) {
    min_int = b;
  }
  return min_int;
}

/******** initilize the briks **********/

object_breakout init_object (int type, float x_act, float y_act, SDL_Surface *screen) {
    
  object_breakout object;  //creation of the object
  SDL_Surface *temp;       //temporaire variable to make the sprite of the object
  
    
  object.x = x_act;
  object.y  = y_act;
  object.c_frame = 0;
    
  if (type == BRICKI) {
    object.width = 32;
    object.height = 16;
    temp = SDL_LoadBMP("Brick1.bmp");
    object.sprite = SDL_DisplayFormat (temp);
    SDL_FreeSurface (temp);
    object.n_frame = 1;
  }
       
  if (type == BRICKII) {
    object.width = 32;
    object.height = 16;
    temp = SDL_LoadBMP("Brick2.bmp");
    object.sprite = SDL_DisplayFormat (temp);
    SDL_FreeSurface (temp);
    object.n_frame = 2;
  }
    
  if (type == BRICKIII) {
    object.width = 32;
    object.height = 16;
    temp = SDL_LoadBMP("Brick3.bmp");
    object.sprite = SDL_DisplayFormat (temp);
    SDL_FreeSurface (temp);
    object.n_frame = 3;
      
  }
    
  if (type == BALL) {
    object.width = 16;
    object.height = 16;
    temp = SDL_LoadBMP("Ball.bmp");
    object.sprite = SDL_DisplayFormat (temp);
    SDL_FreeSurface (temp);
    object.n_frame = 1;
  }

  object.picture.x = 0;
  object.picture.y = 0;
  object.picture.h = object.height;
  object.picture.w = object.width;
  object.position.x = (int) (object.x);
  object.position.y = (int) (object.y);
  object.counter = 0;
  object.colorkey = SDL_MapRGB (screen -> format, 255, 0, 255);
  SDL_SetColorKey (object.sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, object.colorkey);

       
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
void move_ball (object_breakout *ball) {
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
    ball -> y = 0;
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


void read_table (object_breakout **table, char **tab_data, float *x, float  *y, int row, int col, int *nbI, int *nbII, int *nbIII,  SDL_Surface *screen) {
  int i,j;
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      if ( tab_data[i][j] == '1' ) {
	table[0][*nbI] = init_object (1, *x, *y, screen);
	*x += table[0][*nbI].width;
	*nbI += 1;
      }
      else {
	if ( tab_data[i][j] == '2' ) {
	  table[1][*nbII] = init_object (2, *x, *y, screen);
	  *x += table[1][*nbII].width;
	  *nbII += 1;
	}
	else { 
	  if ( tab_data[i][j] == '3' ) {
	    table[2][*nbIII] = init_object (3, *x, *y, screen);
	    *x += table[2][*nbIII].width;
	    *nbIII += 1;
	  }
	  else {
	    if (tab_data[i][j] == '\n') {
	      *x = 0;
	      *y += DEFAULT_HEIGHT;
	    }
	    else {
	      * x += DEFAULT_WIDTH;
	    }
	  }
	}
      }
    }
  }
}
      
void rebond (object_breakout *ball, int side){
    
  if (side == 1) { //  || side == 3) {
    ball->speed_y = - ball -> speed_y ;
  }
  if (side == 0) { // || side == 2) {
    ball->speed_x = - ball -> speed_x;
  }
  
}


bool collide_precise (object_breakout *sprite1, object_breakout *sprite2, SDL_PixelFormat *format, int *cu, int *cv) {
  
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
  
  
void collide_table (object_breakout ** table, int *n, int *m, int *l, object_breakout *ball, SDL_PixelFormat *format, int nbtype) {
  bool exit1 = false;  //put true when we have a collision or we have browse all the table 
  int *k = NULL, i = 0;
  while (!exit1 && i < nbtype) {
     if (i == 0){
      k = n;
     }
     else if (i == 1){
      k = m;
     }
    else{
      k = l;
    }
    exit1 = collide_table_aux( table[i], k, ball, format);
    i++; 
  }
}
    
bool collide_table_aux (object_breakout *table , int *n, object_breakout *ball, SDL_PixelFormat *format) {
  bool exit2 = false;
  int i = 0, j;
  int u = 0, v = 0;
  bool g, d, h, b;
  g = table[i].x < ball -> x + ball -> width;
  d = table[i].x + table[i].width > ball -> x;
  h = table[i].y <= ball -> y + ball -> height;
  b = table[i].y + table [i].height >= ball -> y;
  while (!exit2 && i < *n) {
    if (collide_precise (ball, &table[i], format, &u, &v)) {
      if ( (g || d) && !(h || b))  {
	printf("g\n");
	rebond (ball, 0);
	//ball->speed_x = - ball -> speed_x;
	exit2 = true;
      }
      else if (b || h) {
	printf("b\n");
	rebond (ball, 1);
	//ball->speed_y = - ball -> speed_y ;
	exit2 = true;
      }

      table[i].c_frame += 1;
      if (table[i].c_frame == table[i].n_frame) {
	for (j=i; j < *n-1; j++) {
	  table[j] = table[j+1];
	}
	*n = *n - 1;
      }
      else {
	table[i].picture.x = table[i].c_frame * table[i].width;
      }
    }
    i++;
  }
  return exit2;
}
      
/*  float xa, ya;
  float angle = 2*M_PI/sprite->orientation; //Calcul de l'angle entre chaque orientation en radian
  xa = (cos(sprite->orientationC * angle)) * a;
  ya = (-sin(sprite->orientationC * angle)) * a;
  sprite->vx = sprite->vx + (2 * xa);
  sprite->vy = sprite->vy + (2 * ya); */
      
      
void collide_platform (object_breakout *plat, object_breakout *ball, SDL_PixelFormat *format) {
  float p1x, p1y, p2x, p2y, xa, ya;
  float mx, my;
  float angle, angleR, a = M_PI/2;
  float dadj, dhyp;
  int cx = 0, cy = 0;
  if (collide_precise(ball, plat, format, &cx, &cy)) {
    if (cy >= ball -> y + ball -> height) {
      mx = plat -> x + (plat -> width / 2);
      my = plat -> y;
      if (cx > mx + 0.05 || cx < mx - 0.05) {
	if (cx < mx + 0.05) {      
	  p1x = ball -> x;
	  p1y = ball -> y + ball -> height;
	  p2.x = ball -> x;
	  p2.y = ball -> y;
	 }
	else if (cx > mx + 0.05) {
	  p1x = ball -> x + ball -> width;
	  p1y = ball -> y + ball -> height;
	  p2x = ball -> x + ball -> width;
	  p2y = ball -> y;
	}
	dadj = sqrt( ((cx - p1x)*(cx - p1x)) + ((cy - p1y)*(cy - p1y)) );
	dhyp = sqrt( ((cx - p2x)*(cx - p2x)) + ((cy - p2y)*(cy - p2y)) );
	angle = cos (dadj / dhy); 
	angleR = (M_PI * angle) / 180;
	
	
      