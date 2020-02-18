#include "commun.h"
#include "baseGame.h"

SDL_Window *fenetre;
SDL_Renderer *rendu;

SDL_Renderer* getRenderer(void)
{
	return rendu;
}


void Init(const char *title)
{
    fenetre = NULL;
    rendu= NULL;

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

     if( SDL_Init(SDL_INIT_EVENTS || SDL_INIT_VIDEO) != 0 )
    {
        printf("%s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
    }

    fenetre = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR_FENETRE , HAUTEUR_FENETRE ,SDL_WINDOW_SHOWN );

    rendu= SDL_CreateRenderer( fenetre , -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if (fenetre == NULL || rendu == NULL)
    {
        printf("Erreur d'initialisation de l'ecran: %s \n", SDL_GetError() ) ;				                                                    ;
        exit(EXIT_FAILURE);
    }

    /*############### CHARGEMENT DES POLICES *###############*/
    getMenu()->police = TTF_OpenFont("fonts/Crazy-Pixel.ttf", 48);
    if(!getMenu()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    /*############### GESTION DES AUDIO *###############*/
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096); //initialize sound


    /*############### INITIALISATION DES ENTITES *###############*/        
    
    InitJoueur( getPlayer() );
	Init_MenuPrincipal();
    Init_Scores();


    getBaseGame()->state = MENU_PRINCIPAL ;
    getPlayer()->niveau = 1;
    getPlayer()->nombreVies = 3;
    getBaseGame()->estActif = true;


}


void Quitter_Jeux()
{
     
    Mix_FreeChunk(getMenu()->son);
    TTF_CloseFont(getMenu()->police);
    Nettoyer_MenuPrincipal();
    SDL_DestroyWindow(fenetre) ;
    SDL_DestroyRenderer ( rendu);
    rendu = NULL;
   fenetre = NULL;
    TTF_Quit();
    SDL_Quit();
}
