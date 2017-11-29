    FILE *fichierScore = NULL;
    fichierScore = fopen("classementScore.txt", "r+");
    FILE *fichierNom = NULL;
    fichierNom = fopen("classementNom.txt", "r+");
    FILE *fichierRemplacementScore = NULL;
    fichierRemplacementScore = fopen("remplacementScore.txt", "w+");
    FILE *fichierRemplacementNom = NULL;
    fichierRemplacementNom = fopen("remplacementNom.txt", "w+");

    char classScore[TAILLE_MAX];
    char classNom[TAILLE_MAX];
	 	
    //demande du nom du joueur dans le terminal
    char Nom[TAILLE_MAX];	 	
    int temp; 
    //pour faire une sauvegarde du score pendant l'echanger de deux variables
    char tempNom[TAILLE_MAX]; //idem pour le nom
	 	
    bool dejaDemande = false;  
    //faux si l'on a pas encore demander le nom sinon vrai
    //}
	 	
    //Variables de l'affichage
    char prem[TAILLE_MAX];
    sprintf (prem, "%s", "1 : ");
    char deux[TAILLE_MAX];
    sprintf (deux, "%s", "2 : ");
    char trois[TAILLE_MAX];
    sprintf (trois, "%s", "3 : ");
	 	
    char classement [3][TAILLE_MAX];
    sprintf(classement[0], "%s", "1 : ");
    sprintf(classement[1], "%s", "2 : ");
    sprintf(classement[2], "%s", "3 : ");
	 	
    TTF_Font *fontClassement;
    fontClassement = TTF_OpenFont ("A Love of Thunder.ttf", 32);

    SDL_Rect positionPrem, positionDeux, positionTrois;
    positionPrem.x = 0;
    positionPrem.y = SCREEN_HEIGHT - 105;
    positionDeux.x = 0;
    positionDeux.y = SCREEN_HEIGHT - 70;
    positionTrois.x = 0;
    positionTrois.y = SCREEN_HEIGHT - 35;

	if (!dejaDemande) {
	  printf ("Quel est ton nom ? \n");
	  scanf ("%s", Nom);
	  dejaDemande = true;
					
	  i = 0;
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
		 			
	  remove ("classementScore.txt");
	  remove ("classementNom.txt");
	  rename ("remplacementScore.txt", "classementScore.txt");
	  rename ("remplacementNom.txt", "classementNom.txt");
	  fclose (fichierRemplacementScore);
	  fclose (fichierRemplacementNom);
		 			
	}
 				
 				
	SDL_Surface *textPrem =
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
	SDL_FreeSurface (textTrois);
 			 
      }