/**
 * \file inits.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère l'initialisation
 * \brief Initialisation de la fenêtre, du rendu, du son, du menu principal, du score et du joueur 
 * \brief Destruction du son, des ennemis, de la fenêtre, du menu prinicpal, du rendu...
 */
#include "commun.h"
#include "baseGame.h"

SDL_Renderer *rendu = NULL;
SDL_Window *fenetre = NULL;


extern SDL_Renderer* getRenderer(void)
{
	return rendu;
}

void Init(const char *title)
{
    
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
    getMenu()->police = TTF_OpenFont("fonts/homizio.ttf", 20);
    if(!getMenu()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    getScores()->police = TTF_OpenFont("fonts/BingBam.ttf", 48);
    if(!getScores()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
    }
    /*############### GESTION DES AUDIO *###############*/
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096); //initialize sound


    /*############### INITIALISATION DES ENTITES *###############*/        
    
    InitJoueur( getPlayer() );
	Init_MenuPrincipal();
    
    

    Init_Scores();
    


  
    getBaseGame()->estActif = true;
}

/**
 *  S'occupe de la libération de toutes les ressources du jeux
 *  Ainsi que de la destruction du Renderer et du Window
 */
void LibererRessources_Jeux()
{
     
    SDL_DestroyWindow(fenetre) ;
    SDL_DestroyRenderer (rendu);
    DestructionNiveau();
    rendu = NULL;
    fenetre = NULL;
    
    Mix_FreeChunk(getMenu()->son);
    Mix_FreeMusic( getMenu()->bgm  );
    TTF_CloseFont(getMenu()->police);
    TTF_CloseFont(getScores()->police);
    
    suppListe(&bullet);
    suppListe(&listCollider);
    suppListe(&listEnnemis);
    Nettoyer_MenuPrincipal();
    Nettoyer_MenuPause(getMenu());
    Nettoyer_MenuGameOver();

    TTF_Quit();
    SDL_Quit();
    
    printf("fin sdl quit\n");
}
