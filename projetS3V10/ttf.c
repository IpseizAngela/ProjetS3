TTF_Init();  //Initialisation de SDL_ttf
TTF_Font *police = TTF_OpenFont("A Love of Thunder.ttf",20);
SDL_Color couleur = {255,255,255};
char score[60];
char vie[20];
const char *txtS = "Point de vie : ";
const char *txtV = "Score : ";

SDL_Surface *TexteS, *TexteV, *texteScore, *texteVie;
texteScore =  TTF_RenderUTF8_Solid(police, txtS, couleur);
texteVie =  TTF_RenderUTF8_Solid(police, txtV, couleur);

//Initialisation des positions des differents textes
SDL_Rect positionS, positionV, positionTxtS, positionTxtV;
positionTxtS.x = 0;
positionTxtS.y = 0;
positionTxtV.x = 0;
positionTxtV.y = 25;
positionV.x = 140;
positionV.y = 0;
positionS.x = 75;
positionS.y = 25;

sprintf(score, "%d", Tab_Vaisseau[0].score);
sprintf(vie, "%d", Tab_Vaisseau[0].pv);
int
TexteS = TTF_RenderUTF8_Solid(police, score, couleur);
TexteV = TTF_RenderUTF8_Solid(police, vie, couleur);

SDL_BlitSurface(texteScore, NULL, screen, &positionTxtS);
SDL_BlitSurface(TexteS, NULL, screen, &positionS);
SDL_BlitSurface(texteVie, NULL, screen, &positionTxtV);
SDL_BlitSurface(TexteV, NULL, screen, &positionV); 

void print_text (const char text, int val, SDL_Surface *screen, int pos_x, int pos_y) 
