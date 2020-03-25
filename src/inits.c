/**
 * \file inits.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les initialisations
 * \brief Initialisation de la fenêtre, du rendu, du son, du menu principal, du score et du joueur 
 * \brief Destruction du son, des ennemis, de la fenêtre, du menu prinicpal, du rendu...
 */
#include "commun.h"
#include "baseGame.h"

SDL_Renderer *rendu = NULL; /**< Structure du rendu */
SDL_Window *fenetre = NULL; /**< Structure de la fenetre */

/**
 * \fn extern SDL_Renderer* getRenderer(void)
 * \brief Fonction qui permet d'acceder a la structure du rendu
 * \details 
 * \return un pointeur sur une structure de type SDL_Renderer
*/
extern SDL_Renderer* getRenderer(void)
{
	return rendu;
}

/**
 * \fn void Init(const char *title)
 * \brief Fonction qui permet d'initialiser 
 * \details Creation de la fenetre
 * \details Chargement des polices, de l'audio et des entites
 * \param title chaine de caracteres
 * \return pas de valeur de retour (void)
*/
void Init(const char *title)
{
    //Verifie que l'API des polices a bien ete initialise
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //Verifie que la bibliotheque SDL a bien ete initialisee
    if( SDL_Init(SDL_INIT_EVENTS || SDL_INIT_VIDEO) != 0 )
    {
        printf("%s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
    }

    //Creation de la fenetre
    fenetre = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR_FENETRE , HAUTEUR_FENETRE ,SDL_WINDOW_SHOWN );

    //Creation du rendu
    rendu = SDL_CreateRenderer( fenetre , -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    //Verifie que la fenetre et le rendu ont ete cree correctements
    if (fenetre == NULL || rendu == NULL)
    {
        printf("Erreur d'initialisation de l'ecran: %s \n", SDL_GetError() ) ;				                                                    ;
        exit(EXIT_FAILURE);
    }

    /*############### CHARGEMENT DES POLICES *###############*/
    getMenu()->police = TTF_OpenFont("fonts/homizio.ttf", 20);

    //Verifie que la police a bien ete charge pour le menu
    if(!getMenu()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }


    getScores()->police = TTF_OpenFont("fonts/arial.ttf", 54);

    //Verifie que la police a bien ete charge pour le score
    if(!getScores()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
    }


    getNiveau()->police = TTF_OpenFont("fonts/arial.ttf", 54);
    
    //Verifie que la police a bien ete charge pour le niveau
    if(!getNiveau()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
    }
    

    /*############### GESTION DES AUDIO *###############*/
    //Initialisation du son
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);


    /*############### INITIALISATION DES ENTITES *###############*/        
    
    InitJoueur( getPlayer() );
	Init_MenuPrincipal();      
    getBaseGame()->estActif = true;
}

/**
 * \fn void LibererRessources_Jeux(void)
 * \brief Fonction qui libere toutes les ressources du jeu 
 * \details Destruction des structures rendu et fenetre 
 * \return pas de valeur de retour (void)
*/
void LibererRessources_Jeux(void)
{
    //Destruction de la fenetre, du rendu et du niveau 
    SDL_DestroyWindow(fenetre) ;
    SDL_DestroyRenderer (rendu);
    DestructionNiveau();
    rendu = NULL;
    fenetre = NULL;
    
    //Suppression des audios et des polices qui ont ete charges
    Mix_FreeChunk(getMenu()->son);
    Mix_FreeMusic( getMenu()->bgm  );
    TTF_CloseFont(getMenu()->police);
    TTF_CloseFont(getScores()->police);
    
    //Suppression des listes
    suppListe(&bullet);
    suppListe(&listCollider);
    suppListe(&listEnnemis);

    //Destruction des menus
    Nettoyer_Menu(getMenuCon(), 1);
    Nettoyer_Menu(getMenu(), 4 );
    Nettoyer_Menu(getMenuPause(), 2);

    TTF_Quit(); //Quitter TTF
    SDL_Quit(); //Quitter SDL
    
    printf("fin sdl quit\n");
}
