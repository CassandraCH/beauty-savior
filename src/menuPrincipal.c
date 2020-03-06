#include "baseGame.h"
// #include "menuPrincipal.h"
// #include "constantes.h"
// #include "commun.h"

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
extern int getTouchePresse()
{ 
    return menu.selectedOption; 
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

    /* 
     * Premiere option : demarer une nouvelle partie 
     * couleur du début = rouge
     */ 
    menu.menu[0].couleur = (SDL_Color) {0xFF, 0, 0,0 };
    menu.menu[0].nomOption = "Play";

    //Refraichissement de l'affichage de l'option
    UpdateOption( &menu.menu[0] );
    
    //Position (en x et y) de l'option dans la fenetre
    menu.menu[0].x = (width / 2) - (menu.menu[0].largeur);
    menu.menu[0].y = height / (MAX_NUMBER + 1) * 1;

    /* 
     * Deuxieme option : chargement d'une partie 
     * couleur du début = blanc
     */
    menu.menu[1].couleur = (SDL_Color){0xFF, 0xFF, 0xFF, 0xFF};
    menu.menu[1].nomOption = "Options";
    //Refraichissement de l'affichage de l'option
    UpdateOption(&menu.menu[1]);
    //Position (en x et y) de l'option dans la fenetre
    menu.menu[1].x = (width / 2) - (menu.menu[1].largeur);
    menu.menu[1].y = height / (MAX_NUMBER + 1) * 2;

    /* 
     * Troisieme option : quitter le jeu 
     * couleur du début = blanc
     */
    menu.menu[2].couleur = (SDL_Color){0xFF, 0xFF, 0xFF, 0xFF};
    menu.menu[2].nomOption = "Exit";
    //Refraichissement de l'affichage de l'option
    UpdateOption(&menu.menu[2]);
    //Position (en x et y) de l'option dans la fenetre
    menu.menu[2].x = (width / 2) - (menu.menu[2].largeur);
    menu.menu[2].y = height / (MAX_NUMBER + 1) * 3;

    //Option selectionnee = la premiere (nouvelle partie)
    menu.selectedOption = 0;
}

/* 
 * Fonction qui rafraichit l'affichage des Options 
 */
extern void UpdateOption(Options_t * menut)
{
    /* 
     * Surface tampon => utile pour parametrer la surface
     * TTF_RenderText_Blended => permet de creer une surface et de l'affiche en haute qualite 
     */
    SDL_Surface *tmp = TTF_RenderText_Blended(menu.police, menut->nomOption, menut->couleur);
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
extern void ToucheHaut()
{
    //Si l'option actuellement selectionnee est differente de la premiere
    //Si on est sur la premiere option => on ne peut pas aller sur une option au-dessus
    if (menu.selectedOption - 1 >= 0)
    {  
        //Pour l'option actuelle => changer la couleur (mettre blanc)
        menu.menu[menu.selectedOption].couleur = (SDL_Color){0xFF, 0xFF, 0xFF, 0xFF};
        //Rafraichir l'affichage
        UpdateOption(&menu.menu[menu.selectedOption]);

        //Modifier l'option selectionnee => passe a l'option suivante
        menu.selectedOption--;

        //Pour l'option sur laquelle on veut aller => changer la couleur (mettre rouge)
        menu.menu[menu.selectedOption].couleur = (SDL_Color){0xFF, 0, 0, 0};
        //Rafraichir l'affichage
        UpdateOption(&menu.menu[menu.selectedOption]);
    }

}
/*
 * Fonction qui permer de naviguer dans le menu vers le bas
 */
extern void ToucheBas()
{
    //Si l'option actuellement selectionnee est differente de la derniere
    //Si on est sur la derniere option => on ne peut pas aller sur une option en-dessous
    if (menu.selectedOption + 1 < MAX_NUMBER)
    {
        //Pour l'option actuelle => changer la couleur (mettre blanc)
        menu.menu[menu.selectedOption].couleur = (SDL_Color){0xFF, 0xFF, 0xFF, 0xFF};
        //Rafraichir l'affichage
        UpdateOption(&menu.menu[menu.selectedOption]);

        //Modifier l'option selectionnee => passe a l'option precedente
        menu.selectedOption++;

        //Pour l'option sur laquelle on veut aller => changer la couleur (mettre rouge)
        menu.menu[menu.selectedOption].couleur = (SDL_Color){0xFF, 0, 0, 0};
        //Rafraichir l'affichage
        UpdateOption(&menu.menu[menu.selectedOption]);
    }
}

/*
 * Fonction qui permet d'afficher le menu principal
 * => affichage les differentes options
 */
extern void Dessiner_MenuPrincipal() 
{
    //Pour chaque option, afficher a l'ecran son rendu
	for (int i = 0; i < MAX_NUMBER; i++)
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
                    ToucheHaut();
                    break;
                case SDLK_DOWN:
                    Mix_PlayChannel(-1, getMenu()->son, 0);
                    ToucheBas();
                    break;
                case SDLK_LEFT:
            
                    break;
                case SDLK_RETURN:
                    switch ( getTouchePresse() )
                    {
                        case 0:
                            getPlayer()->estMort = false;
                            suppListe( getCollider() );
                            suppListe(getEnnemis());
                            suppListe(getBullets());
                            PlayerScore("PIECES: 0", 10, 0);
                            ChargerNiveau();
                            Nettoyer_MenuPrincipal();
                            getBaseGame()->state = IN_GAME;
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
    for(int i = 0; i < MAX_NUMBER; i++)
    {
        free(menu.menu[i].texture);
    }

   
}
