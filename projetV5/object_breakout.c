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
	ball -> x = 50;
	ball -> y = 50;
	ball -> speed_x = 0.05;
	ball -> speed_y = 0.01;
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
  int colorkey; 
    
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
    colorkey = SDL_MapRGB (screen -> format, 255, 0, 255);
    SDL_SetColorKey (object.sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
    object.n_frame = 1;
  }

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
void move_ball (object_breakout *ball) {
  ball -> x += ball -> speed_x;
  ball -> y += ball -> speed_y;
  ball -> position.x = ball -> x;
  ball -> position.y = ball -> y;
    
  if (ball -> x   <  0 ) {
    rebond(ball, 0, 0);
  }
  if (ball -> x   > SCREEN_WIDTH - ball -> width) {
    rebond(ball, 2, 0);
  }
  if (ball -> y  <  0) {
    rebond(ball, 1, 0);
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
      
void rebond (object_breakout *balle, int side, int type){
    
  if (side == 1  || side == 3) {
    printf ("1 side = %d \n", side);
    balle->speed_y = - balle -> speed_y ;
    //balle.speed_x = 0.05;
  }
  if (side == 0 || side == 2) {
    printf ("2 side = %d \n", side);
    balle->speed_x = - balle -> speed_x;
    // balle.speed_y = 0.05;

  }
  
}

void collide_table (object_breakout ** table, int *n, int *m, int *l, object_breakout *ball) {
  int i,j;
  for (i=0; i<*n; i++) {
    if (collide (&table[0][i], ball)) {
      if (table[0][i].counter <= 0) {
	if (table[0][i].x <= ball -> x + ball -> width){
	  // printf("dokjfchisqdvhb");
	  rebond (ball, 0, 0);
	  ball->speed_x = - ball -> speed_x;
	  table[0][i].counter = 50;
	}
	else if (table[0][i].x + table[0][i].width >= ball -> x) {
	  rebond (ball, 2, 0);
	  ball->speed_x = - ball -> speed_x;
	  table[0][i].counter = 50;
	}
	else if (table[0][i].y + table[0][i].height <=  ball -> y ) {
	  rebond (ball, 3, 0);
	  ball->speed_y = - ball -> speed_y;
	  table[0][i].counter = 50;
	}
	else if (table[0][i].y >= ball ->y + ball->height){
	  rebond(ball, 1, 0);
	  ball->speed_y = - ball -> speed_y;
	  table[0][i].counter = 50;
	}
      }
      table[0][i].counter -= 1;
      table[0][i].c_frame += 1;
      if (table[0][i].c_frame == table[0][i].n_frame) {
	for (j=i; j<*n-1; j++) {
	  table[0][j] = table[0][j+1];
	}
	*n = *n-1;
      }
      else  {
	table[0][i].picture.x = table[0][i].c_frame * table[0][i].width;
      }
    }
  }

   
  
  for (i=0; i<*m; i++) {
    if (collide (&table[1][i], ball)) {
      if (table[1][i].counter <= 0){
	if (table[1][i] . x <= ball -> x + ball -> width) {
	  rebond (ball, 'l', 0);
	  ball->speed_x = - ball -> speed_x;
	  table[1][i].counter = 100;
	}
	else {
	  if (table[1][i].x + table[1][i].width >= ball -> x) {
	    rebond (ball, 'r', 0);
	    ball->speed_x = - ball -> speed_x;
	    table[1][i].counter = 100;
	  }
	  else {
	    
	    if (table[1][i].y + table[1][i].height <=  ball -> y) {
	      rebond (ball, 'b', 0);
	      ball->speed_y = - ball -> speed_y;
	      table[1][i].counter = 100;
	    }
	    else {
	      rebond(ball, 't', 0);
	      ball->speed_y = - ball -> speed_y;
	      table[1][i].counter = 100;
	    }
	  }   
	}
      }
      table[1][i].counter -= 1;
      table[1][i].c_frame += 1;
      if (table[1][i].c_frame == table[1][i].n_frame) {
	for (j=i; j<*m-1; j++) {
	  table[1][j] = table[1][j+1];
	}
	*m = *m-1;
      }
      else  {
	table[1][i].picture.x = table[1][i].c_frame * table[1][i].width;
      } 
    }
  }
    
  for (i=0; i<*l; i++) {
    if (collide (&table[2][i], ball)) {
      if (table[2][i].counter <= 0) {
	if (table[2][i] . x == ball -> x + ball -> width) {
	  rebond (ball, 'l', 0);
	  ball->speed_x = - ball -> speed_x;
	  table[2][i].counter = 50;
                    
	}
	else {
	  if (table[2][i].x + table[2][i].width == ball -> x) {
	    rebond (ball, 'r', 0);
	    ball->speed_x = - ball -> speed_x;
	    table[2][i].counter = 50;
	  }
	  else {
	    if (table[2][i].y + table[2][i].height ==  ball -> y) {
	      rebond (ball, 'b', 0);
	      ball->speed_y = - ball -> speed_y;
	      table[2][i].counter = 50;
	    }
	    else {
	      rebond(ball, 't', 0);
	      ball->speed_y = - ball -> speed_y;
	      table[2][i].counter = 50;
	    }
	  }   
	}
      }
      table[2][i].counter -= 1;
      table[2][i].c_frame += 1;
      if (table[2][i].c_frame == table[2][i].n_frame) {
	for (j=i; j<*l-1; j++) {
	  table[2][j] = table[2][j+1];
	}
	*l = *l-1;
      }
      else  {

	table[2][i].picture.x = table[2][i].c_frame * table[2][i].width;
      }
    }
  }
}
