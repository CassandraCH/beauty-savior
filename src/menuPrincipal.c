/**
 * \file menuPrincipal.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le menu principal
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrées clavier et destruction du menu
 */

#include "baseGame.h"

GameObject _gameObject; /**< Structure de type GameObject */

/**
 * \fn extern GameObject* getGameObject()
 * \brief Fonction qui permet retourner le menu principal
 * \return une structure menu de type GameObject
*/
extern GameObject* getGameObject()
{
    return &_gameObject;
}

/**
 * \fn extern int GetKeypressed(GameObject *gameObject)
 * \brief Fonction qui retourne l'option du menu selectionne
 * \param gameObject pointeur sur le menu
 * \return un entier correspondant au numero de l'option selectionnee
*/
extern int GetKeypressed(GameObject *gameObject)
{ 
    return gameObject->componentSelected; 
}

/**
 * \fn extern void Principal_Init()
 * \brief Fonction qui initialise le menu principal
 * \return pas de valeur de retour (void)
*/
extern void Principal_Init()
{       
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu principal\n");
    
    //chargement des sons
    _gameObject.son = Mix_LoadWAV("sounds/menu_click.wav");
    _gameObject.bgm = Mix_LoadMUS("sounds/awesomeness.wav");

    _gameObject.nom_gameObject = "Menu Principal";

    /* 
     * Premiere option : Demarer une nouvelle partie 
     * Actif par défaut
     */ 
    GameObject_LoadRessources(0,0,&_gameObject , "Jouer"
                ,"graphics_assets/icons_buttons/jouer_on_xs.png"
                ,"graphics_assets/icons_buttons/jouer_off_xs.png"
                ,469
                ,366 );

    /* 
     * Deuxieme option : Chargement d'une partie
     */
    GameObject_LoadRessources(1,1,&_gameObject , "Chargement"
            ,"graphics_assets/icons_buttons/load_on_xs.png"
            ,"graphics_assets/icons_buttons/load_off_xs.png"
            ,455
            ,449 );


    /* 
     * Troisieme option : Quitter le jeu 
     */
    GameObject_LoadRessources(2,1,&_gameObject , "Quitter"
            ,"graphics_assets/icons_buttons/quitter_on_xs.png"
            ,"graphics_assets/icons_buttons/quitter_off_xs.png"
            ,469
            ,491 );

    /* 
     * Quatrième option : Couper/Activer Son
     */
    GameObject_LoadRessources(3,1,&_gameObject , "ActiverSon"
            ,"graphics_assets/icons_buttons/sound_on_xs.png"
            ,"graphics_assets/icons_buttons/sound_off_xs.png"
            ,487
            ,627 );


    //Option selectionnee = la premiere (nouvelle partie)
    _gameObject.componentSelected = 0;

    //Chargement de la texture du menu principal
     _gameObject.bg = Texture_Load("graphics_assets/menu_bg_xs.png");

     printf("Fin Chargement Menu principal\n");
}

/**
 * \fn extern void UpdateComponent(gameObject * component, int etat )
 * \brief Fonction qui rafraichit l'affichage des options
 * \param component option a mettre a jour
 * \param etat etat : selectionne ou non
 * \return pas de valeur de retour (void)
*/
extern void UpdateComponent(Component * component, int etat )
{
    /* 
     * Surface tampon => utile pour parametrer la surface
     * TTF_RenderText_Blended => permet de creer une surface et de l'affiche en haute qualite 
     */

    // SDL_Surface *tmp = TTF_RenderText_Blended(menu.police, component->nomOption, component->couleur);
    
    SDL_Surface *tmp = IMG_Load( component->filename[etat] );
    component->largeur = tmp->w;
    component->hauteur = tmp->h;

    //Liberer la memoire utilisee pour l'ancienne structure
    if( component->texture != NULL)
    {   
        printf("Texture libéré\n");
        SDL_DestroyTexture(component->texture);
        component->texture = NULL;
    }

    //Creer la nouvelle texture avec les parametres dans la surface tampon
    component->texture = SDL_CreateTextureFromSurface( getRenderer() , tmp);

    //Liberer la memoire utilisee pour la surface tampon
    SDL_FreeSurface(tmp);
}

/**
 * \fn extern void UpdateImage_Component(gameObject * component, const char * filename)
 * \brief Fonction qui rafraichit l'affichage des options
 * \param component option a mettre a jour
 * \param filename nom du fichier à partir duquel on charge la texture
 * \return pas de valeur de retour (void)
*/
extern void UpdateImage_Component(Component * component, const char * filename )
{
   /* 
     * Surface tampon => utile pour parametrer la surface
     * TTF_RenderText_Blended => permet de creer une surface et de l'affiche en haute qualite 
     */

    
    SDL_Surface *tmp = IMG_Load( filename );
    component->largeur = tmp->w;
    component->hauteur = tmp->h;

    //Liberer la memoire utilisee pour l'ancienne structure
    if( component->texture != NULL)
    {   
        printf("Texture libéré\n");
        SDL_DestroyTexture(component->texture);
        component->texture = NULL;
    }

    //Creer la nouvelle texture avec les parametres dans la surface tampon
    component->texture = SDL_CreateTextureFromSurface( getRenderer() , tmp);

    //Liberer la memoire utilisee pour la surface tampon
    SDL_FreeSurface(tmp);
}


/**
 * \fn extern void UP_Key(GameObject *gameObject)
 * \brief Fonction qui permet de naviguer dans le menu vers le haut
 * \param gameObject pointeur sur le menu
 * \return pas de valeur de retour (void)
*/
extern void UP_Key(GameObject *gameObject)
{
    //Si l'option actuellement selectionnee est differente de la premiere
    //Si on est sur la premiere option => on ne peut pas aller sur une option au-dessus
    if (gameObject->componentSelected - 1 >= 0)
    {  
        //Rafraichir l'affichage
        UpdateComponent(&gameObject->components[gameObject->componentSelected] , 1);

        //Modifier l'option selectionnee => passe a l'option suivante
        gameObject->componentSelected--;

        //Rafraichir l'affichage
        UpdateComponent(&gameObject->components[gameObject->componentSelected], 0 );
    }
}

/**
 * \fn extern void DOWN_Key(GameObject *gameObject)
 * \brief Fonction qui permet de naviguer dans le menu vers le bas
 * \param gameObject pointeur sur le menu
 * \return pas de valeur de retour (void)
*/
extern void DOWN_Key(GameObject *gameObject)
{
    //Si l'option actuellement selectionnee est differente de la derniere
    //Si on est sur la derniere option => on ne peut pas aller sur une option en-dessous
    if (gameObject->componentSelected + 1 < MAX_NUMBER)
    {
        //Rafraichir l'affichage
        UpdateComponent(&gameObject->components[gameObject->componentSelected], 1);

        //Modifier l'option selectionnee => passe a l'option precedente
        gameObject->componentSelected++;

        //Rafraichir l'affichage
        UpdateComponent(&gameObject->components[gameObject->componentSelected], 0);
    }
}

/**
 * \fn extern void RIGHT_Key(GameObject* gameObject, int nombresOptions)
 * \brief Fonction qui permet de naviguer dans le menu a RIGHT_Key
 * \param gameObject Pointeur sur le gameObject
 * \param nombresOptions Nombre de components utilisés
 * \return pas de valeur de retour (void)
*/
extern void RIGHT_Key(GameObject* gameObject, int nombresOptions)
{

    //Si l'option actuellement selectionnee est differente de la premiere
    //Si on est sur la dernière option => on ne peut pas aller sur une option au-dessus 
    if (gameObject->componentSelected + 1 < nombresOptions  )
    {
        //Rafraichir l'affichage
        UpdateComponent(&gameObject->components[gameObject->componentSelected], 1);

        //Modifier l'option selectionnee => passe a l'option precedente
        gameObject->componentSelected++;

        //Rafraichir l'affichage
        UpdateComponent(&gameObject->components[gameObject->componentSelected], 0);
    }
}

/**
 * \fn extern void LEFT_Key(GameObject* gameObject, int nombresOptions)
 * \brief Fonction qui permet de naviguer dans le menu a LEFT_Key
 * \param gameObject pointeur sur le menu
 * \param nombresOptions nombre d'options
 * \return pas de valeur de retour (void)
*/
extern void LEFT_Key(GameObject* gameObject, int nombresOptions)
{
    //Si l'option actuellement selectionnee est differente de la premiere
    //Si on est sur la premiere option => on ne peut pas aller sur une option au-dessus
    if (gameObject->componentSelected - 1 >= 0)
    {  
  
        //Rafraichir l'affichage
        UpdateComponent(&gameObject->components[gameObject->componentSelected] , 1);

        //Modifier l'option selectionnee => passe a l'option suivante
        gameObject->componentSelected--;

        //Rafraichir l'affichage
        UpdateComponent(&gameObject->components[gameObject->componentSelected], 0 );
    }
    
}

/**
 * \fn extern void GameObject_Render(GameObject* gameObject, int nombresOptions, int posX, int posY , int largeurBG, int hauteurBG) 
 * \brief Fonction qui permet d'afficher le menu
 * \brief Affichage des différentes options
 * \param gameObject pointeur sur le menu
 * \param nombresOptions nombre d'options dans le menu
 * \param posX position en x de l'arriere plan
 * \param posY position en y de l'arriere plan
 * \param largeurBG largeur de l'arriere plan
 * \param hauteurBG hauteur de l'arriere plan
 * \return pas de valeur de retour (void)
*/
extern void GameObject_Render(GameObject* gameObject, int nombresOptions, int posX, int posY , int largeurBG, int hauteurBG) 
{
    SDL_Rect rect = {posX,posY, largeurBG, hauteurBG };

    //Gestion de l'affichage du rendu
    if( gameObject->bg != NULL )
        SDL_RenderCopy( getRenderer(), gameObject->bg , NULL, &rect );

    //Pour chaque option, afficher a l'ecran son rendu
	for (int i = 0; i < nombresOptions; i++)
	{
        //Rectangle tampon 
        SDL_Rect rect = {gameObject->components[i].x, gameObject->components[i].y, gameObject->components[i].largeur, gameObject->components[i].hauteur};
        SDL_RenderCopy( getRenderer(), gameObject->components[i].texture , NULL, &rect);
	}
}

/**
 * \fn extern void Principal_Input(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu principal
 * \brief Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Principal_Input(SDL_Event *event)
{
    // Lecture de tous les evenements
    while( SDL_PollEvent(event) != 0 )
    {
        //Cas ou l'utilisateur veut quitter le jeu : touche echap ou croix de la fenetre
        if( event->type == SDL_QUIT ||  event->key.keysym.sym == SDLK_ESCAPE )
        {
            //changer l'etat du jeu
            getBaseGame()->estActif = false;
            return;
        }

        //Si une touche est appuyee
        if(  event->type == SDL_KEYUP )
        {
            switch ( event->key.keysym.sym)
            {
                //Cas de la touche fleche du haut
                case SDLK_UP:
                    //Gestion du son
                    Mix_PlayChannel(-1, getGameObject()->son, 0);
                    UP_Key(getGameObject());
                    break;

                //Cas de la touche fleche du bas
                case SDLK_DOWN:
                    //Gestion du son
                    Mix_PlayChannel(-1, getGameObject()->son, 0);
                    DOWN_Key(getGameObject());
                    break;

                //Cas de la touche entree
                case SDLK_RETURN:
                    switch (GetKeypressed( getGameObject() ))
                    {
                        //Cas de la premiere option : demarer une nouvelle partie
                        case 0:
                           
                            increaseRock();
                            getPlayer()->rockActif = true;

                            //Suppression des listes
                            Delete_List( getCollider() );
                            Delete_List( getEnnemis() );
                            Delete_List( getBullets() );

                            Interface_Init();
                            
                            Level_Load();

                            //Changement de l'etat du jeu
                            getBaseGame()->state = IN_GAME;
                            Mix_HaltMusic();
                            return;
                            break;

                        //Cas de la deuxieme option : charger une partie
                        case 1:
                            // printf("Bouton option press%c\n", 130);
                            printf("Chargement depuis menu principal\n");
                            Load_Init();
                            GameObject_Clean(getGameObject(), 4);

                            //Changement de l'etat du jeu
                            getBaseGame()->state = LOADING;

                            //Arret de la musique
                            Mix_HaltMusic();
                            break;

                        //Cas de la troisieme option : quitter le jeu
                        case 2:
                            //Changement de l'etat du jeu
                            getBaseGame()->estActif = false;
                            return;
                            break;
                        default:
                            break;
                    }
                    break;

                //Cas de la touche s
                case SDLK_s:
                    //Si la musique est en pause
                    if( Mix_PausedMusic() == 1 )
                    {
                        UpdateComponent(&_gameObject.components[3], 0);

                        //On enlève la pause (la musique repart où elle en était)
                        Mix_ResumeMusic();
                    }

                    //Si la musique est en train de jouer
                    else
                    {
                        UpdateComponent(&_gameObject.components[3], 1);

                        //On met en pause la musique
                        Mix_PauseMusic();
                    }    
                    break;
                default:
                    break;
            }//fin du switch
        }//fin du if   
    } //fin while (SDL_PollEvent)
}

/**
 * \fn extern void GameObject_LoadRessources(int numero,int num_image, GameObject * gameObject,  char * nomOption,  char * image_on,  char * image_off, int positionX, int positionY)
 * \brief Fonction qui gere le chargement des donnes du menu
 * \param numero numero de l'option
 * \param num_image numero de l'image selectionne par defaut
 * \param gameObject pointeur sur le menu
 * \param nomOption nom de l'option
 * \param image_on chemin pour acceder a l'image selectionnee
 * \param image_off chemin pour acceder a l'image deselectionnee
 * \param positionX position en x
 * \param positionY position en y
 * \return pas de valeur de retour (void)
*/
extern void GameObject_LoadRessources(int numero, int num_image, GameObject * gameObject,  char * nomOption,  char * image_on,  char * image_off, int positionX, int positionY)
{
    //Chargement des donnees
    gameObject->components[numero].nomOption = nomOption;
    gameObject->components[numero].filename[0] = image_on;
    gameObject->components[numero].filename[1] = image_off;

    //Refraichissement de l'affichage de l'option
    UpdateComponent( &gameObject->components[numero], num_image  );
    
    //Position (en x et y) de l'option dans la fenetre
    gameObject->components[numero].x = positionX;
    gameObject->components[numero].y = positionY;
}

/**
 * \fn extern void GameObject_Clean(GameObject * gameObject, int nombreOptions)
 * \brief Fonction qui permet de nettoyer l'ecran du menu
 * \param gameObject pointeur sur le menu
 * \param nombreOptions nombre d'options du menu
 * \return pas de valeur de retour (void)
*/
extern void GameObject_Clean(GameObject * gameObject, int nombreOptions)
{
    printf("Suppression Menu %s\n", gameObject->nom_gameObject );

    if( gameObject != NULL )
    {
         //Parcours de toute les options
        for(int i = 0; i < nombreOptions; i++)
        {
            //Liberation de la memoire utilisee pour la texture de l'option
            if( gameObject->components[i].texture != NULL ) 
            {
                //Liberation de la memoire utilisee pour la texture de l'option
                SDL_DestroyTexture(gameObject->components[i].texture);
            }
        }
        printf("Fin Suppression Menu %s \n", gameObject->nom_gameObject);

    }
      return;

}
