#include "object_breakout.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SPRITE_STEP 5



/************** management of keyboard keys *****************/
void HandleEvent(SDL_Event event, int *quit,  object_breakout *platform, bool *throw, object_breakout *ball){
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
      printf("escape or q\n");
      *quit = 1;
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
	ball -> x = platform->x + PLATFORM_WIDTH;
	ball -> y = platform->y + PLATFORM_HEIGHT;
	ball -> speed_x = SPEEDX;
	ball -> speed_y = SPEEDY;
	*throw = true;
	throw = NULL;
	free(throw);
      } 
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
char ** allocation2D (int l, int c) {
  char ** Tab = Tab = malloc(l*sizeof(char*));
  int i = 0;
  for (i=0; i<l; i++) {
    Tab[i] = malloc(c*sizeof(char));
  }
  return Tab;
}


/******* give a memoru fot the 2D object_breakout table *******/
object_breakout** alloc (int l, int c) {
  object_breakout** Tab = malloc(l*sizeof(object_breakout*));
  int i = 0;
  for (i=0; i<l; i++) {
    Tab[i] = malloc(c*sizeof(object_breakout));
    }
  return Tab;
}



/******** count the number of rows and columns in the file ********/
void count_dimension (FILE *file, int *row, int *col) 
{
  char cursor = NULL;      //take the current value on the file
  bool end_level = false;
  bool end = false;  //for know if we are in the pair and unpair ligne
  int col1 = 1;      //count the number of columns if it's a pair line
  //initialized at 1 for count the \n 
  int col2 = 1;      //count the number of colums if it's a unpair line
  //idem
  int max_col = 0;       //take the maximum of the two numbers of columns
  cursor = fgetc (file); 
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
  }
  printf ("Row : %d, Col : %d \n", *row, *col);
}


/******* read the data text  ******/
char ** read_data(FILE *file, int  row, int col) 
{  
  char ** T = allocation2D(row,col);   /*array of 2 dimensions for take the
					   database and declared thanks
					   to the allocation2D function */
  if (file != NULL) {                //read the file only if the file is open
    
    char cc = NULL;                            /*variable which the current 
						 character of the file */
    int i = 0,j = 0;                            //variables to range the array
    
    for(i=0;i<row;i++){                 //put all the contents of the file in 
      for(j=0;j<col;j++){                   //the array
	cc = fgetc(file);
	if ( (j < (col-1)) && (cc == '\n')) {
	  while (j < (col-1)) {
	    T[i][j] = ' ';
	    j++;
	  }
	}
	T[i][j] = cc;
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
  SDL_Surface *temp = NULL, *picture_loaded = NULL;
  temp = SDL_LoadBMP(name_file);
  picture_loaded = SDL_DisplayFormat (temp);
  SDL_FreeSurface (temp);
  return picture_loaded;
}


/********** set the colokey of the image ********/
void set_colorkey (SDL_Surface *screen, int R, int G, int B, SDL_Surface *sprite) {
  int colorkey = 0;
  colorkey = SDL_MapRGB(screen -> format, R, G, B);
  SDL_SetColorKey (sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}



/******** initialize the bricks **********/
object_breakout init_object (int type, float x_act, float y_act, SDL_Surface *screen,int type_bonus) {
    
  object_breakout object;  //creation of the object  
    
  object.x = x_act;
  object.y  = y_act;
  object.c_frame = 0;
  object.colorkey = SDL_MapRGB (screen -> format, 255, 0, 255);
    
  if (type == BRICKI) {
    object.width = 32;
    object.height = 16;
    object.sprite = load ("Brick1.bmp");
    set_colorkey(screen, 255, 0, 255, object.sprite);
    object.n_frame = 1;
  }
       
  if (type == BRICKII) {
    object.width = 32;
    object.height = 16;
    object.sprite = load ("Brick2.bmp");
    set_colorkey(screen, 255, 0, 255, object.sprite);
    object.n_frame = 2;
  }
    
  if (type == BRICKIII) {
    object.width = 32;
    object.height = 16;
    object.sprite = load ("Brick3.bmp");
    set_colorkey(screen, 255, 0, 255, object.sprite);
    object.n_frame = 3;
      
  }
    
  if (type == BALL) {
    object.width = 16;
    object.height = 16;
    object.sprite = load ("Ball.bmp");
    set_colorkey(screen, 255, 0, 255, object.sprite);
    object.n_frame = 1;
    object.score = 0;
    object.life = 70;
  }

  if (type == PLAT) {
      object.width = 64;
      object.height = 16;
      object.sprite = load ("NormalPlatform.bmp");
      set_colorkey(screen, 255, 0, 255, object.sprite);
      object.n_frame = 1;
      object.colorkey = SDL_MapRGB(screen->format,255, 0, 255);
  }
  
  if (type == BONUS){
    object.t_bonus = type_bonus;
    if (object.t_bonus == REDUC){
      object.width = 16;
      object.height = 16;
      object.sprite = load ("nuke.bmp");
      object.n_frame = 1;
      object.colorkey = SDL_MapRGB(screen->format,0, 0, 162);
    }
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
  int i = 0;
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
    ball -> life -= 1;

  }
}

/* Collide between 2 objects */
bool collide(object_breakout *sprite1,object_breakout *sprite2){
  if ((max(sprite1->x, sprite2->x) < min (sprite1 -> x + sprite1 -> width, sprite2->x + sprite2->width))
      && (max(sprite1->y,sprite2->y) < min(sprite1->y+sprite1->height,sprite2->y+sprite2->height))){
    return true;
  }else{
    return false;
  }
}


/***** read the data table to put them on an other table for the gestion of the bricks ****/
void read_table (object_breakout **table, char **tab_data, float *x, float  *y, int row, int col, int *nbI, int *nbII, int *nbIII,  SDL_Surface *screen) {
  int i = 0,j = 0;
  for (i=0; i<row; i++) {
    for (j=0; j<col; j++) {
      if ( tab_data[i][j] == '1' ) {
	table[0][*nbI] = init_object (1, *x, *y, screen,-1);
	*x += table[0][*nbI].width;
	*nbI += 1;
      }
      else {
	if ( tab_data[i][j] == '2' ) {
	  table[1][*nbII] = init_object (2, *x, *y, screen,-1);
	  *x += table[1][*nbII].width;
	  *nbII += 1;
	}
	else { 
	  if ( tab_data[i][j] == '3' ) {
	    table[2][*nbIII] = init_object (3, *x, *y, screen,-1);
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
bool collide_precise (object_breakout *sprite1, object_breakout *sprite2, SDL_PixelFormat *format, int *cu, int *cv) {
  
  bool test = collide (sprite1, sprite2);

  if (test) {

    Uint32 *bmp1 = (Uint32 *) malloc (sizeof (Uint32) * sprite1 -> width * sprite1 -> height);
    Uint32 *sprite_it = 0, *bmp_it = 0;
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
	  int col1 = 0;
	  Uint8 r = 0, g = 0, b = 0;
	  
	  SDL_GetRGB (pixel1, format, &r, &g, &b);
	  col1 = SDL_MapRGB (format, r, g, b);
	  
	  if (col1 != sprite1 -> colorkey) {
	    Uint32 pixel2 = 0;
	    int col2 = 0;
	    Uint8 r = 0, g = 0, b = 0;
	    int u2 = 0, v2 = 0;
	    
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
    sprite_it = NULL;
    bmp_it = NULL;
    free (sprite_it);
    free (bmp_it);
    free (bmp1);
    free (bmp2);
  }
  
  return test;
}
  

/*** look if we are a collision in a table ***/
void collide_table (object_breakout ** table, int *n, int *m, int *l, object_breakout *ball, SDL_PixelFormat *format, int nbtype, object_breakout *reduc,int *z, SDL_Surface *screen) {
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
     exit1 = collide_table_aux(table[i], k, ball, format, i+1,z,screen,reduc);
    i++; 
  }
  k = NULL;
  free(k);
}
   
/***** look if we are a collision between a brick and the ball into the table ******/
bool collide_table_aux (object_breakout *table , int *n, object_breakout *ball, SDL_PixelFormat *format, int type, int *z, SDL_Surface *screen, object_breakout *reduc) {
  bool exit2 = false;
  int i = 0, j;
  int u = 0, v = 0;
  bool g, d, h, b;
  while (!exit2 && i < *n) {
    if (collide_precise (ball, &table[i], format, &u, &v)) {
      g = table[i].x == u;
      d = table[i].x + table[i].width >= u;
      h = table[i].y == v;
      b = table[i].y + table[i].height >= v;
      if (g || d)  {
	//printf("g ou d\n");
	rebond (ball, 0);
	exit2 = true;
      }
      else if (b || h) {
	//printf("b ou h\n");
	rebond (ball, 1);
	exit2 = true;
      }

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
      power(reduc, z, screen, u,v,true);
    }
    i++;
  }
  return exit2;
}
      

/**** loke if we are a collision between the platform and the ball ******/
void collide_platform (object_breakout *plat, object_breakout *ball, SDL_PixelFormat *format) {
  
  float mx, my, xa, ya;
  float dist;
  int cx = 0, cy = 0;
  bool g, d, h;
  
  if (collide_precise(ball, plat, format, &cx, &cy)) {
    g = plat -> x == cx;
    d = plat -> x + plat -> width >= cx;
    h = plat -> y == cy;
    
    mx = plat -> x + (plat -> width / 2);
    my = plat -> y;
    dist = sqrt( ( (cx - mx) * (cx - mx) ) + ( (cy - my) * (cy - my) ) );
    
    if (h) {
      if (cx > mx){//collide after the half of the platform
	printf ("haut_droit \n");
	xa = cos (2 * M_PI / dist); 
	ya = -sin (2 * M_PI / dist);
	ball -> speed_x = xa*SPEEDX;
	ball -> speed_y = ya*SPEEDY;
      }else {
	printf ("haut_gauche \n");
	xa = -cos (2 * M_PI / dist); 
	ya = -sin (2 * M_PI / dist);
	ball -> speed_x = xa*SPEEDX;
	ball -> speed_y = ya*SPEEDY;
      }
    } 
    else if (g || d) {
      printf("plat_g_d \n");
      rebond(ball, 0);
    }
  } 
}
      
/******* look if there is a collision between the platform and the edges of the screen ********/
void collide_screen (object_breakout *platform) {
  if (platform -> x <= 0.0) {
    platform -> x = 0.0; 
  }
  if (platform -> x >= SCREEN_WIDTH - PLATFORM_WIDTH)  {
    platform -> x = SCREEN_WIDTH - PLATFORM_WIDTH;
  }
}


/****** draw the bakground on the screen **********/
void draw_background (SDL_Surface *background, SDL_Surface *screen) {
  for (int x = 0; x < SCREEN_WIDTH /* BG_WIDTH*/; x++) {
    for (int y = 0; y < SCREEN_HEIGHT /* BG_HEIGHT*/; y++) { 
      SDL_Rect position;
      position.x = x * BG_WIDTH;
      position.y = y * BG_HEIGHT;
      SDL_BlitSurface(background, NULL, screen, &position);
    }
  }
}

/***** print an object_breakout *****/
void print_object (object_breakout *object, SDL_Surface *screen) {
  SDL_BlitSurface (object -> sprite,&object -> picture , screen, &object -> position);
}


/**** print different text on the screen ******/
void print_text (const char *text, int val, SDL_Surface *screen, int pos_x, int pos_y) {
    TTF_Font *font = TTF_OpenFont("A Love of Thunder.ttf",20);
    SDL_Color color = {0,0,0,0};
    SDL_Surface *sprite_text_val = NULL, *sprite_text = NULL;
    SDL_Rect position_text_val, position_text;
    char text_val [50];
    sprintf (text_val, "%d", val);
    sprite_text = TTF_RenderUTF8_Solid (font, text, color);
    sprite_text_val = TTF_RenderUTF8_Solid (font, text_val, color);
    position_text.x = pos_x;
    position_text.y = pos_y;
    position_text_val.x = pos_x + 75;
    position_text_val.y = pos_y;
    
    SDL_BlitSurface (sprite_text, NULL, screen, &position_text);
    SDL_BlitSurface (sprite_text_val, NULL, screen, &position_text_val);
    TTF_CloseFont(font);
    free(sprite_text);
    free(sprite_text_val);
    
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
void power (object_breakout *reduc, int *n, SDL_Surface *screen, int cx, int cy, bool collide_b)
{
  if (collide_b){
    int lucky = nb_random();
    printf("lucky = %d \n",lucky);
    if (lucky == REDUCE_NEED){
      printf(" apparu \n");
      add(reduc, n, cx, cy, screen,REDUC);
      *n = *n + 1;
      for(int j=0;j<*n;j++){
	printf("reduc[%d] = %d   %d \n",j, reduc[j].speed_x, reduc[j].speed_y);
      }
    }
  }    
}


/********  make move the ball ************/
void move_power (object_breakout *reduc, int *n) {
  int i;
  for(i=0;i<*n;i++){
    printf("i = %d \n",i);
    reduc[i]->speed_y = 10;
    reduc[i]->x += reduc[i]->speed_x;
    reduc[i]->y = reduc[i]->speed_y;
    reduc[i]->position.x = reduc[i]->x;
    reduc[i]->position.y = reduc[i]->y;
    if (reduc[i]->y > SCREEN_HEIGHT - reduc[i]->height) {
      del(reduc,n,i);
    }
  }
}





/*
  for (i=0; i<*n; i++){
	mj = &reduc[i];
	if (collide_precise(mj, platform, screen->format,&x,&y)){
	  printf("pris");
	  platform -> width = 32;
	  platform -> sprite = load("LittlePlatform.bmp");
	  del(mj, n, i);
	}
      } 
*/
