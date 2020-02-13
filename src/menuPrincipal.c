//#include "baseGame.h
#include "menuPrincipal.h"

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
extern int GetKeyPressed()
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
    menu.sound = Mix_LoadWAV("sounds/menu_click.wav");

    /* 
     * Premiere option : demarer une nouvelle partie 
     * couleur du début = rouge
     */ 
    menu.menu[0].couleur = (SDL_Color) { 0xFF, 0, 0,0 };
    menu.menu[0].string = "Nouvelle Partie";
    //Refraichissement de l'affichage de l'option
    UpdateOption( &menu.menu[0] );
    //Position (en x et y) de l'option dans la fenetre 
    menu.menu[0].x = (width / 2) - (menu.menu[0].width);
    menu.menu[0].y = height / (MAX_NUMBER + 1) * 1;

    /* 
     * Deuxieme option : chargement d'une partie 
     * couleur du début = blanc
     */
    menu.menu[1].color = (SDL_Color) {0xFF,0xFF,0xFF,0xFF};
    menu.menu[1].string = "Charger Partie";
    //Refraichissement de l'affichage de l'option
    UpdateOption(&menu.menu[1]);
    //Position (en x et y) de l'option dans la fenetre
    menu.menu[1].x = (width/2) - (menu.menu[1].width);
    menu.menu[1].y = height / (MAX_NUMBER + 1) * 2;

    /* 
     * Troisieme option : quitter le jeu 
     * couleur du début = blanc
     */
    menu.menu[2].color = (SDL_Color) {0xFF,0xFF,0xFF,0xFF};
    menu.menu[2].string = "Exit";
    //Refraichissement de l'affichage de l'option
    UpdateOption(&menu.menu[2]);
    //Position (en x et y) de l'option dans la fenetre
    menu.menu[2].x = (width/2) - (menu.menu[2].width);
    menu.menu[2].y = height / (MAX_NUMBER + 1) * 3;

    //Option selectionnee = la premiere (nouvelle partie)
    menu.selectedItem = 0;
}

/* 
 * Fonction qui rafraichit l'affichage des options 
 */
extern void UpdateOption(Options * menut)
{
    //Surface tampon
    SDL_Surface *tmp = TTF_RenderText_Blended(menu.font, menut->string, menut->color );
    menut->width  = tmp->w;
    menut->height= tmp->h;

    if( menut->texture != NULL)
    {   
        printf("Texture libéré\n");
        SDL_DestroyTexture(menut->texture);
        menut->texture = NULL;
    }

    menut->texture = SDL_CreateTextureFromSurface( getRenderer() , tmp);
    SDL_FreeSurface(tmp);
}


extern void MoveUp()
{   
	if ( menu.selectedItem - 1 >= 0)
	{   

        // Blanc
		menu.menu[menu.selectedItem].color = (SDL_Color) {0xFF,0xFF,0xFF,0xFF};
        UpdateOption(&menu.menu[menu.selectedItem]);
        
        menu.selectedItem--;

		//Rouge
        menu.menu[menu.selectedItem].color = (SDL_Color) {0xFF,0,0,0};
        UpdateOption(&menu.menu[menu.selectedItem]);
    }

}

extern void MoveDown()
{  
	if ( menu.selectedItem  + 1 < MAX_NUMBER )
	{
        // Blanc
		menu.menu[menu.selectedItem].color = (SDL_Color) {0xFF,0xFF,0xFF,0xFF};
        UpdateOption(&menu.menu[menu.selectedItem]);
		
        menu.selectedItem++;

        // Rouge
		menu.menu[menu.selectedItem].color = (SDL_Color) {0xFF,0,0,0};
        UpdateOption(&menu.menu[menu.selectedItem]);
    }
}


extern void Draw_MenuPrincipal() 
{
	for (int i = 0; i < MAX_NUMBER; i++)
	{
        SDL_Rect rect = { menu.menu[i].position.x, menu.menu[i].position.y, menu.menu[i].width, menu.menu[i].height };
        SDL_RenderCopy( getRenderer(), menu.menu[i].texture , NULL, &rect);
	}
}

extern void Input_MenuPrincipal(SDL_Event* event)
{
    
    while( SDL_PollEvent(event) != 0 )
    {
        if( event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE )
        {
            getBaseGame()->estActif = false;
            return;
        }

        if( event->type == SDL_KEYUP )
        {
            switch (event->key.keysym.sym)
            {
                case SDLK_UP:
                    Mix_PlayChannel(-1, getMenu()->sound, 0);
                    MoveUp();
                    break;
                case SDLK_DOWN:
                    Mix_PlayChannel(-1,  getMenu()->sound, 0);
                    MoveDown();
                    break;
                case SDLK_LEFT:
            
                    break;
                case SDLK_RETURN:
                    switch ( GetKeyPressed() )
                    {
                        case 0:
                            getPlayer()->estMort = false;
                            deleteList(Listes());
                            deleteList(&listEnnemies);
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

extern void Nettoyer_MenuPrincipal()
{
    printf("Suppression Menu principal\n");
    for(int i = 0; i < MAX_NUMBER; i++)
    {
        free(menu.menu[i].texture);
    }
   
}


