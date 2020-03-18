/**
 * \file menuPrincipal.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le menu principal
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrées clavier et destruction du menu
 */

#include "baseGame.h"


    Menu_t menu;

/*
 * Fonction qui retourne le menu
 */ 
extern Menu_t* getMenu()
{
    return &menu;
}

/* 
 * Fonction qui retourne l'option du menu selectionne
 */
extern int getTouchePresse(Menu_t *menu)
{ 
    return menu->selectedOption; 
}

extern void ChargerData_Menu(int numero,int num_image, Menu_t * menu,  char * nomOption,  char * image_on,  char * image_off,
int positionX, int positionY
)

{
    menu->menu[numero].nomOption = nomOption;
    menu->menu[numero].filename[0] = image_on;
    menu->menu[numero].filename[1] = image_off;

    //Refraichissement de l'affichage de l'option
    UpdateOption( &menu->menu[numero], num_image  );
    
    //Position (en x et y) de l'option dans la fenetre
    menu->menu[numero].x = positionX;
    menu->menu[numero].y = positionY;
}

/* 
 * Fonction qui initialise le menu principal
 */
extern void Init_MenuPrincipal()
{   
    
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu principal");
    
    //chargement du son
    menu.son = Mix_LoadWAV("sounds/menu_click.wav");

    menu.bgm = Mix_LoadMUS("sounds/awesomeness.wav");

    /* 
     * Premiere option : demarer une nouvelle partie 
     * Actif par défaut
     */ 

     ChargerData_Menu(0,0,&menu , "Jouer"
                ,"graphics_assets/icons_buttons/jouer_on_xs.png"
                ,"graphics_assets/icons_buttons/jouer_off_xs.png"
                ,469
                ,366 );

    /* 
     * Deuxieme option : Chargement d'un partie
     */

    ChargerData_Menu(1,1,&menu , "Chargement"
            ,"graphics_assets/icons_buttons/load_on_xs.png"
            ,"graphics_assets/icons_buttons/load_off_xs.png"
            ,455
            ,449 );


    /* 
     * Troisieme option : quitter le jeu 
     */

    ChargerData_Menu(2,1,&menu , "Quitter"
            ,"graphics_assets/icons_buttons/quitter_on_xs.png"
            ,"graphics_assets/icons_buttons/quitter_off_xs.png"
            ,469
            ,491 );

     /* 
     * Quatrième option : Couper/Activer Son
     */
   
    ChargerData_Menu(3,1,&menu , "Quitter"
            ,"graphics_assets/icons_buttons/sound_on_xs.png"
            ,"graphics_assets/icons_buttons/sound_off_xs.png"
            ,487
            ,627 );



    //Option selectionnee = la premiere (nouvelle partie)
    menu.selectedOption = 0;

    menu.bg = ChargerTexture("graphics_assets/menu_bg_xs.png");


}

/* 
 * Fonction qui rafraichit l'affichage des Options 
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

/*
 * Fonction qui permer de naviguer dans le menu vers le haut
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
/*
 * Fonction qui permer de naviguer dans le menu vers le bas
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

/*
 * Fonction qui permet d'afficher le menu principal
 * => affichage les differentes options
 */
extern void Dessiner_MenuPrincipal() 
{

    SDL_Rect rect = {0,0, 1280, 720 };

    SDL_RenderCopy( getRenderer(), menu.bg , NULL, &rect );

    //Pour chaque option, afficher a l'ecran son rendu
	for (int i = 0; i < MAX_NUMBER+1; i++)
	{
        //Rectangle tampon 
        SDL_Rect rect = {menu.menu[i].x, menu.menu[i].y, menu.menu[i].largeur, menu.menu[i].hauteur};
        SDL_RenderCopy( getRenderer(), menu.menu[i].texture , NULL, &rect);
	}

    
}

/*
 * Fonction qui permet de gérer les evenements 
 * => gestion des entrees clavier (action utilisateur)
 */
extern void Input_MenuPrincipal(SDL_Event *event)
{


    // Lecture de tous les evenements
    while( SDL_PollEvent(event) != 0 )
    {
        if( event->type == SDL_QUIT ||  event->key.keysym.sym == SDLK_ESCAPE )
        {
            //changer l'etat du jeu
            getBaseGame()->estActif = false;
            return;
        }

        //
        if(  event->type == SDL_KEYUP )
        {
            switch ( event->key.keysym.sym)
            {
                case SDLK_UP:
                    Mix_PlayChannel(-1, getMenu()->son, 0);
                    ToucheHaut(getMenu());
                    break;
                case SDLK_DOWN:
                    Mix_PlayChannel(-1, getMenu()->son, 0);
                    ToucheBas(getMenu());
                    break;
                case SDLK_LEFT:
            
                    break;
                case SDLK_RETURN:
                    switch (getTouchePresse(getMenu()))
                    {
                        case 0:
                            getPlayer()->estMort = false;
                            suppListe( getCollider() );
                            suppListe(getEnnemis());
                            suppListe(getBullets());
                            PlayerScore("SCORES : 0", 10, 0);
                            ChargerNiveau();
                            // Nettoyer_MenuPrincipal();
                            getBaseGame()->state = IN_GAME;
                            Mix_HaltMusic();
                            return;
                            break;
                        case 1:
                            printf("Bouton option press%c\n", 130);
                            break;
                        case 2:
			               getBaseGame()->estActif = false;
			                 return;
                            break;
                        default:
                            break;
                    }
                break;
                case SDLK_s:
                     //Si la musique est en pause
                        if( Mix_PausedMusic() == 1 )
                        {
                            UpdateOption(&menu.menu[3], 0  );
                            //On enlève la pause (la musique repart où elle en était)
                            Mix_ResumeMusic();
                        }
                        //Si la musique est en train de jouer
                        else
                        {
                            UpdateOption(&menu.menu[3], 1  );
                            //On met en pause la musique
                            Mix_PauseMusic();
                        }    
                break;
                default:
                    break;
            }
        }   
    } // fin while (SDL_PollEvent)
}

/*
 * Fonction qui permet de supprimer le menu => liberation de la memoire
 */
extern void Nettoyer_MenuPrincipal()
{
    // NettoyerScore();
    printf("Suppression Menu principal\n");
    for(int i = 0; i < MAX_NUMBER+1; i++)
    {
       if( menu.menu[i].texture != NULL ) 
        {
            free(menu.menu[i].texture);
        }
      
    }
    printf("Fin Suppression Menu principal\n");
   return;

}
