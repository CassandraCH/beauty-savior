/**
 * \file menuPrincipal.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le menu principal
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrées clavier et destruction du menu
 */

#include "baseGame.h"

Menu_t menu; /**< Structure de type menu_t */

/**
 * \fn extern Menu_t* getMenu()
 * \brief Fonction qui permet retourner le menu principal
 * \return une structure menu de type Menu_t
*/
extern Menu_t* getMenu()
{
    return &menu;
}

/**
 * \fn extern int getTouchePresse(Menu_t *menu)
 * \brief Fonction qui retourne l'option du menu selectionne
 * \param menu pointeur sur le menu
 * \return un entier correspondant au numero de l'option selectionnee
*/
extern int getTouchePresse(Menu_t *menu)
{ 
    return menu->selectedOption; 
}

/**
 * \fn extern void Init_MenuPrincipal()
 * \brief Fonction qui initialise le menu principal
 * \return pas de valeur de retour (void)
*/
extern void Init_MenuPrincipal()
{       
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu principal");
    
    //chargement des sons
    menu.son = Mix_LoadWAV("sounds/menu_click.wav");
    menu.bgm = Mix_LoadMUS("sounds/awesomeness.wav");

    /* 
     * Premiere option : Demarer une nouvelle partie 
     * Actif par défaut
     */ 
    ChargerData_Menu(0,0,&menu , "Jouer"
                ,"graphics_assets/icons_buttons/jouer_on_xs.png"
                ,"graphics_assets/icons_buttons/jouer_off_xs.png"
                ,469
                ,366 );

    /* 
     * Deuxieme option : Chargement d'une partie
     */
    ChargerData_Menu(1,1,&menu , "Chargement"
            ,"graphics_assets/icons_buttons/load_on_xs.png"
            ,"graphics_assets/icons_buttons/load_off_xs.png"
            ,455
            ,449 );


    /* 
     * Troisieme option : Quitter le jeu 
     */
    ChargerData_Menu(2,1,&menu , "Quitter"
            ,"graphics_assets/icons_buttons/quitter_on_xs.png"
            ,"graphics_assets/icons_buttons/quitter_off_xs.png"
            ,469
            ,491 );

    /* 
     * Quatrième option : Couper/Activer Son
     */
    ChargerData_Menu(3,1,&menu , "ActiverSon"
            ,"graphics_assets/icons_buttons/sound_on_xs.png"
            ,"graphics_assets/icons_buttons/sound_off_xs.png"
            ,487
            ,627 );


    //Option selectionnee = la premiere (nouvelle partie)
    menu.selectedOption = 0;

    //Chargement de la texture du menu principal
     menu.bg = ChargerTexture("graphics_assets/menu_bg_xs.png");
}

/**
 * \fn extern void UpdateOption(Options_t * menut, int etat )
 * \brief Fonction qui rafraichit l'affichage des options
 * \param menut option a mettre a jour
 * \param etat etat : selectionne ou non
 * \return pas de valeur de retour (void)
*/
extern void UpdateOption(Options_t * menut, int etat )
{
    /* 
     * Surface tampon => utile pour parametrer la surface
     * TTF_RenderText_Blended => permet de creer une surface et de l'affiche en haute qualite 
     */

    // SDL_Surface *tmp = TTF_RenderText_Blended(menu.police, menut->nomOption, menut->couleur);
    
    SDL_Surface *tmp = IMG_Load( menut->filename[etat] );
    menut->largeur = tmp->w;
    menut->hauteur = tmp->h;

    //Liberer la memoire utilisee pour l'ancienne structure
    if( menut->texture != NULL)
    {   
        printf("Texture libéré\n");
        SDL_DestroyTexture(menut->texture);
        menut->texture = NULL;
    }

    //Creer la nouvelle texture avec les parametres dans la surface tampon
    menut->texture = SDL_CreateTextureFromSurface( getRenderer() , tmp);

    //Liberer la memoire utilisee pour la surface tampon
    SDL_FreeSurface(tmp);
}

/**
 * \fn extern void UpdateImage_Option(Options_t * menut, const char * filename)
 * \brief Fonction qui rafraichit l'affichage des options
 * \param menut option a mettre a jour
 * \param filename nom du fichier à partir duquel on charge la texture
 * \return pas de valeur de retour (void)
*/
extern void UpdateImage_Option(Options_t * menut, const char * filename)
{
   /* 
     * Surface tampon => utile pour parametrer la surface
     * TTF_RenderText_Blended => permet de creer une surface et de l'affiche en haute qualite 
     */

    
    SDL_Surface *tmp = IMG_Load( filename );
    menut->largeur = tmp->w;
    menut->hauteur = tmp->h;

    //Liberer la memoire utilisee pour l'ancienne structure
    if( menut->texture != NULL)
    {   
        printf("Texture libéré\n");
        SDL_DestroyTexture(menut->texture);
        menut->texture = NULL;
    }

    //Creer la nouvelle texture avec les parametres dans la surface tampon
    menut->texture = SDL_CreateTextureFromSurface( getRenderer() , tmp);

    //Liberer la memoire utilisee pour la surface tampon
    SDL_FreeSurface(tmp);
}


/**
 * \fn extern void ToucheHaut(Menu_t *menu)
 * \brief Fonction qui permet de naviguer dans le menu vers le haut
 * \param menu pointeur sur le menu
 * \return pas de valeur de retour (void)
*/
extern void ToucheHaut(Menu_t *menu)
{
    //Si l'option actuellement selectionnee est differente de la premiere
    //Si on est sur la premiere option => on ne peut pas aller sur une option au-dessus
    if (menu->selectedOption - 1 >= 0)
    {  
        //Rafraichir l'affichage
        UpdateOption(&menu->menu[menu->selectedOption] , 1);

        //Modifier l'option selectionnee => passe a l'option suivante
        menu->selectedOption--;

        //Rafraichir l'affichage
        UpdateOption(&menu->menu[menu->selectedOption], 0 );
    }
}

/**
 * \fn extern void ToucheBas(Menu_t *menu)
 * \brief Fonction qui permet de naviguer dans le menu vers le bas
 * \param menu pointeur sur le menu
 * \return pas de valeur de retour (void)
*/
extern void ToucheBas(Menu_t *menu)
{
    //Si l'option actuellement selectionnee est differente de la derniere
    //Si on est sur la derniere option => on ne peut pas aller sur une option en-dessous
    if (menu->selectedOption + 1 < MAX_NUMBER)
    {
        //Rafraichir l'affichage
        UpdateOption(&menu->menu[menu->selectedOption], 1);

        //Modifier l'option selectionnee => passe a l'option precedente
        menu->selectedOption++;

        //Rafraichir l'affichage
        UpdateOption(&menu->menu[menu->selectedOption], 0);
    }
}

/**
 * \fn extern void Droite(Menu_t* menu, int nombresOptions)
 * \brief Fonction qui permet de naviguer dans le menu a droite
 * \param menu pointeur sur le menu
 * \param nombresOptions nombre d'options
 * \return pas de valeur de retour (void)
*/
extern void Droite(Menu_t* menu, int nombresOptions)
{

    //Si l'option actuellement selectionnee est differente de la premiere
    //Si on est sur la dernière option => on ne peut pas aller sur une option au-dessus 
    if (menu->selectedOption + 1 < nombresOptions  )
    {
        //Rafraichir l'affichage
        UpdateOption(&menu->menu[menu->selectedOption], 1);

        //Modifier l'option selectionnee => passe a l'option precedente
        menu->selectedOption++;

        //Rafraichir l'affichage
        UpdateOption(&menu->menu[menu->selectedOption], 0);
    }
}

/**
 * \fn extern void Gauche(Menu_t* menu, int nombresOptions)
 * \brief Fonction qui permet de naviguer dans le menu a gauche
 * \param menu pointeur sur le menu
 * \param nombresOptions nombre d'options
 * \return pas de valeur de retour (void)
*/
extern void Gauche(Menu_t* menu, int nombresOptions)
{
    //Si l'option actuellement selectionnee est differente de la premiere
    //Si on est sur la premiere option => on ne peut pas aller sur une option au-dessus
    if (menu->selectedOption - 1 >= 0)
    {  
  
        //Rafraichir l'affichage
        UpdateOption(&menu->menu[menu->selectedOption] , 1);

        //Modifier l'option selectionnee => passe a l'option suivante
        menu->selectedOption--;

        //Rafraichir l'affichage
        UpdateOption(&menu->menu[menu->selectedOption], 0 );
    }
    
}

/**
 * \fn extern void Dessiner_Menu(Menu_t* menu, int nombresOptions, int posX, int posY , int largeurBG, int hauteurBG) 
 * \brief Fonction qui permet d'afficher le menu
 * \details Affichage des différentes options
 * \param menu pointeur sur le menu
 * \param nombresOptions nombre d'options dans le menu
 * \param posX position en x de l'arriere plan
 * \param posY position en y de l'arriere plan
 * \param largeurBG largeur de l'arriere plan
 * \param hauteurBG hauteur de l'arriere plan
 * \return pas de valeur de retour (void)
*/
extern void Dessiner_Menu(Menu_t* menu, int nombresOptions, int posX, int posY , int largeurBG, int hauteurBG) 
{
    SDL_Rect rect = {posX,posY, largeurBG, hauteurBG };

    //Gestion de l'affichage du rendu
    if( menu->bg != NULL )
        SDL_RenderCopy( getRenderer(), menu->bg , NULL, &rect );

    //Pour chaque option, afficher a l'ecran son rendu
	for (int i = 0; i < nombresOptions; i++)
	{
        //Rectangle tampon 
        SDL_Rect rect = {menu->menu[i].x, menu->menu[i].y, menu->menu[i].largeur, menu->menu[i].hauteur};
        SDL_RenderCopy( getRenderer(), menu->menu[i].texture , NULL, &rect);
	}
}

/**
 * \fn extern void Input_MenuPrincipal(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu principal
 * \details Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Input_MenuPrincipal(SDL_Event *event)
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
                    Mix_PlayChannel(-1, getMenu()->son, 0);
                    ToucheHaut(getMenu());
                    break;

                //Cas de la touche fleche du bas
                case SDLK_DOWN:
                    //Gestion du son
                    Mix_PlayChannel(-1, getMenu()->son, 0);
                    ToucheBas(getMenu());
                    break;

                //Cas de la touche entree
                case SDLK_RETURN:
                    switch (getTouchePresse(getMenu()))
                    {
                        //Cas de la premiere option : demarer une nouvelle partie
                        case 0:
                            //Changement de l'etat du joueur
                            getPlayer()->estMort = false;

                            //Suppression des listes
                            suppListe( getCollider() );
                            suppListe(getEnnemis());
                            suppListe(getBullets());

                            Init_Interface();
                            
                            ChargerNiveau();

                            //Changement de l'etat du jeu
                            getBaseGame()->state = IN_GAME;
                            Mix_HaltMusic();
                            return;
                            break;

                        //Cas de la deuxieme option : charger une partie
                        case 1:
                            // printf("Bouton option press%c\n", 130);
                            printf("Chargement depuis menu principal\n");
                            Init_MenuLoad();
                            Nettoyer_Menu(getMenu(), 4);

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
                        UpdateOption(&menu.menu[3], 0);

                        //On enlève la pause (la musique repart où elle en était)
                        Mix_ResumeMusic();
                    }

                    //Si la musique est en train de jouer
                    else
                    {
                        UpdateOption(&menu.menu[3], 1);

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
 * \fn extern void ChargerData_Menu(int numero,int num_image, Menu_t * menu,  char * nomOption,  char * image_on,  char * image_off, int positionX, int positionY)
 * \brief Fonction qui gere le chargement des donnes du menu
 * \param numero numero de l'option
 * \param num_image numero de l'image selectionne par defaut
 * \param menu pointeur sur le menu
 * \param nomOption nom de l'option
 * \param image_on chemin pour acceder a l'image selectionnee
 * \param image_off chemin pour acceder a l'image deselectionnee
 * \param positionX position en x
 * \param positionY position en y
 * \return pas de valeur de retour (void)
*/
extern void ChargerData_Menu(int numero, int num_image, Menu_t * menu,  char * nomOption,  char * image_on,  char * image_off, int positionX, int positionY)
{
    //Chargement des donnees
    menu->menu[numero].nomOption = nomOption;
    menu->menu[numero].filename[0] = image_on;
    menu->menu[numero].filename[1] = image_off;

    //Refraichissement de l'affichage de l'option
    UpdateOption( &menu->menu[numero], num_image  );
    
    //Position (en x et y) de l'option dans la fenetre
    menu->menu[numero].x = positionX;
    menu->menu[numero].y = positionY;
}

/**
 * \fn extern void Nettoyer_Menu(Menu_t * menu, int nombreOptions)
 * \brief Fonction qui permet de nettoyer l'ecran du menu
 * \param menu pointeur sur le menu
 * \param nombreOptions nombre d'options du menu
 * \return pas de valeur de retour (void)
*/
extern void Nettoyer_Menu(Menu_t * menu, int nombreOptions)
{
    printf("Suppression Menu principal\n");

    //Parcours de toute les options
    for(int i = 0; i < nombreOptions; i++)
    {
        //Liberation de la memoire utilisee pour la texture de l'option
        if( menu->menu[i].texture != NULL ) 
        {
            //Liberation de la memoire utilisee pour la texture de l'option
            free(menu->menu[i].texture);
        }
    }
    printf("Fin Suppression Menu\n");
   return;

}
