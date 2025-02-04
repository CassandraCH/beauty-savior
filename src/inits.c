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
#include "basegame.h"

SDL_Renderer *rendu = NULL; /**< Structure du rendu */
SDL_Window *fenetre = NULL; /**< Structure de la fenêtre */

/**
 * \fn extern SDL_Renderer* getRenderer(void)
 * \brief Fonction qui permet d'accéder à la structure du rendu
 * \return un pointeur sur une structure de type SDL_Renderer
*/
extern SDL_Renderer* getRenderer(void)
{
	return rendu;
}

/**
 * \fn void Init(const char *title)
 * \brief Fonction qui permet d'initialiser la fenêtre
 * \brief Création de la fenetre
 * \brief Chargement des polices, de l'audio et des entites
 * \param title chaine de caracteres
 * \return pas de valeur de retour (void)
*/
void Init(const char *title)
{
    //Verifie que l'API des polices a bien été initialisé
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //Verifie que la bibliothèque SDL a bien été initialisée
    if( SDL_Init(SDL_INIT_EVENTS || SDL_INIT_VIDEO) != 0 )
    {
        printf("%s\n", SDL_GetError() );
        exit(EXIT_FAILURE);
    }

    //Création de la fenêtre
    fenetre = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR_FENETRE , HAUTEUR_FENETRE ,SDL_WINDOW_SHOWN );

    //Création du rendu
    rendu = SDL_CreateRenderer( fenetre , -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    //Vérifie que la fenêtre et le rendu ont été créé correctement
    if (fenetre == NULL || rendu == NULL)
    {
        printf("Erreur d'initialisation de l'ecran: %s \n", SDL_GetError() ) ;				                                                    ;
        exit(EXIT_FAILURE);
    }

    /*############### CHARGEMENT DES POLICES *###############*/

    getGameObject()->police = TTF_OpenFont("fonts/homizio.ttf", 20);
    //Vérifie que la police a bien été chargé pour le menu
    if(!getGameObject()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }


    getScores()->police = TTF_OpenFont("fonts/arial.ttf", 42);
    //Verifie que la police a bien été chargé pour le score
    if(!getScores()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
    }


    getNiveau()->police = TTF_OpenFont("fonts/arial.ttf", 54);
    //Verifie que la police a bien été chargé pour le niveau
    if(!getNiveau()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
    }
    

    getTime()->police  = TTF_OpenFont("fonts/arial.ttf", 42);
    //Verifie que la police a bien été chargé pour le timer
    if(!getTime()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
    }

    getItem(0)->police  = TTF_OpenFont("fonts/arial.ttf",45);
    //Verifie que la police a bien été chargé pour les items
    if(!getItem(0)->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
    }
    getItem(1)->police  = getItem(0)->police;
    getItem(2)->police  = getItem(0)->police;

    
    getNombreVie()->police = TTF_OpenFont("fonts/arial.ttf", 54);
    //Verifie que la police a bien été chargé pour le compteur de vies
    if(!getNombreVie()->police )
    {
        printf("Cannot find font file!!\n");
        SDL_Quit();
    }

    /*############### GESTION DES AUDIO *###############*/
    //Initialisation du son
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);


    /*############### INITIALISATION DES ENTITES *###############*/        
    
    Player_Init( getPlayer() );
	Principal_Init();      
    Init_Textures();
    getBaseGame()->tempsActuel = 0;
    getBaseGame()->tempsPrecedent = 0;
    getBaseGame()->min = 60;
  
    getBaseGame()->isActive = true;
}

/**
 * \fn void Game_DestroyRessources(void)
 * \brief Fonction qui libère toutes les ressources du jeu 
 * \brief Destruction des structures rendu et fenêtre 
 * \return pas de valeur de retour (void)
*/
void Game_DestroyRessources(void)
{ 
    //Suppression des textures
    Level_Destroy(); 
    Clean_Textures();

    //Libération des resspurces concernant le joueur
    TexManager_DestroyRessources( &getPlayer()->tex );

    //Suppression des audios qui ont été chargé
    Mix_FreeChunk(getGameObject()->son);
    Mix_FreeMusic( getGameObject()->bgm  );

    //Suppression des polices qui ont été chargé
    TTF_CloseFont(getGameObject()->police);
    TTF_CloseFont(getTime()->police);
    TTF_CloseFont(getScores()->police);
    TTF_CloseFont( getMenu_Win()->police );
    
    //Suppression des listes
    Delete_List(&bullet);
    Delete_List(&listCollider);
    Delete_List(&listEnnemis);

    //Destruction des menus
    GameObject_Clean(getMenuCon(), 1);
    GameObject_Clean(getGameObject(), 4 );
    GameObject_Clean(getMenuPause(), 2);
    GameObject_Clean( getInterface(), 5 );
    GameObject_Clean( getMenu_Win(), 2);


    //Destruction de la fenetre, du rendu et du niveau 
    SDL_DestroyWindow(fenetre) ;
    SDL_DestroyRenderer (rendu);
    
    rendu = NULL;
    fenetre = NULL;
        

    TTF_Quit(); //Quitter TTF
    SDL_Quit(); //Quitter SDL
    
    printf("fin sdl quit\n");
}
