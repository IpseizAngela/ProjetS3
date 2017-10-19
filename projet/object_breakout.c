#include "object_breakout.h"
/************** management of keyboard keys *****************/

void HandleEvent(SDL_Event event, int *quit,  SDL_Rect *position)
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
      break;
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
  int col1 = 1;      /*count the number of columns if it's a pair line
		       initialized at 1 for count the \n */
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
  				*col = max_col;/*we put the maximum of the 
						 number of columns if the 
						 max is superior at col*/
  			}
  			col1 = 1;// put the numbers of columns at 1 otherwise we will have
  			col2 = 1;// the number of all the character in the file
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
  
  if (file != NULL) {                //read the file only if the file is open
    T = allocation2D(row,col);   /*array of 2 dimensions for take the
				   database and declared thanks
				   to the allocation2D function */
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



/******** initilize the bricks **********/

object_breakout init_object (int type, float x_act, float y_act) {
    
    object_breakout object;  //creation of the object
    object.width = 32;
    object.height = 16;
    object.x = x_act;
    object.y = y_act;
    object.picture.x = 0;
    object.picture.y = 0;
    object.picture.h = object.height;
    object.picture.w = object.width;
    object.position.x = (int) (object.x);
    object.position.y = (int) (object.y);
    if (type == BRICKI) {
	object.sprite = SDL_LoadBMP("Brick1.bmp");
        object.c_frame = 1;
        object.n_frame = 1;
    }
    
    if (type == BRICKII) {
	object.sprite = SDL_LoadBMP("Brick2.bmp");
        object.c_frame = 1;
        object.n_frame = 2;
    }
    
    if (type == BRICKIII) {
	object.sprite = SDL_LoadBMP("Brick3.bmp");
        object.c_frame = 1;
        object.n_frame = 3;
    }
    
    return object;
}
/*load the picture*/
SDL_Surface *load(char *name_file){
  SDL_Surface *temp, *picture_loaded;
  temp = SDL_LoadBMP(name_file);
  picture_loaded = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  
  return picture_loaded;
}

/*set the colorkey of a picture*/
void set_colorkey(SDL_Surface *screen,int R, int G, int B, SDL_Surface *sprite ){
  int colorkey;
colorkey = SDL_MapRGB(screen->format, R, G, B);
SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}

/* Draw and print objects */
void draw(object_breakout *sprite,SDL_Surface *screen){
  SDL_Rect spriteImage;
  SDL_Rect spritePosition;

  spriteImage.y = 0.0;
  spriteImage.w = sprite->width;
  spriteImage.h = sprite->height;
  
  /* choose image according to direction and animation flip: */
  spriteImage.x = sprite->width*(int)sprite->c_frame;
  spritePosition.x=sprite->x;
  spritePosition.y=sprite->y;
  SDL_BlitSurface(sprite->sprite, &spriteImage, screen, &spritePosition);
}

/* Gives a random number between two ends */
float nb_random (float min, float max) {
  float nb;
  /*to have a really random number*/
  srand(time(NULL));
  /*RAND_MAX is the limit of the random of the compilator*/
  nb = (float) rand()/ RAND_MAX * (max - min) + min;/*(max - min) is the size of the interval*/
  return nb;
}

/* Collide between 2 objects */
bool collide(sprite_t *sprite1,sprite_t *sprite2){
  if ((max(sprite1->x,sprite2->x) < min(sprite1->x+sprite1->size_w,sprite2->x+sprite2->size_w))
      && (max(sprite1->y,sprite2->y) < min(sprite1->y+sprite1->size_h,sprite2->y+sprite2->size_h))){
    return true;
  }else{
    return false;
  }
}

/*Free an array
void erased(char T,int col){
  int i;
  for(i=0;i<col;i++){
    free(*T[i]);
  }
  free(T);
}
*/
/*Load image of sprite
SDL_Surface* load_image(char *c){
  SDL_Surface *image, *sprite;
  image = SDL_LoadBMP(c);
  sprite = SDL_DisplayFormat(image);
  SDL_FreeSurface(image);
  return sprite;
}
*/
