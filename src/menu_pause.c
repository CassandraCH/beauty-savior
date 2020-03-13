#include "baseGame.h"

Menu_t menu_pause;

Menu_t * getMenuPause()
{
    return &menu_pause;
}


extern void Init_MenuPause()
{
     int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu principal");
    
    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */ 

    menu_pause.menu[0].nomOption = "Reprendre partie";
    menu_pause.menu[0].filename[0] = "graphics_assets/back_on_xs.png";
    menu_pause.menu[0].filename[1] = "graphics_assets/back_off_xs.png";

    //Refraichissement de l'affichage de l'option
    UpdateOption( &menu_pause.menu[0], 0  );
    
    //Position (en x et y) de l'option dans la fenetre
    menu_pause.menu[0].x = 339;
    menu_pause.menu[0].y = 491;

    /* 
     * Deuxieme option : Retour sur le menu principal
     */
    menu_pause.menu[1].nomOption = "Retour menu";
    menu_pause.menu[1].filename[0] = "graphics_assets/menu_on_xs.png";
    menu_pause.menu[1].filename[1] = "graphics_assets/menu_off_xs.png";

    //Refraichissement de l'affichage de l'option
    UpdateOption(&menu_pause.menu[1], 1);
    //Position (en x et y) de l'option dans la fenetre
    menu_pause.menu[1].x = 620;
    menu_pause.menu[1].y = 491;


    //Option selectionnee = Reprendre partie
    menu_pause.selectedOption = 0;

    menu_pause.bg = ChargerTexture("graphics_assets/pause.png");


}
extern void Dessiner_MenuPause()
{
    
    SDL_Rect rect = {300, 200, 645,432 };

    SDL_RenderCopy(getRenderer(), menu_pause.bg, NULL, &rect);

    //Pour chaque option, afficher a l'ecran son rendu
    for (int i = 0; i < MAX_NUMBER-1; i++)
    {
        //Rectangle tampon
        SDL_Rect rect = {menu_pause.menu[i].x, menu_pause.menu[i].y, menu_pause.menu[i].largeur, menu_pause.menu[i].hauteur};
        SDL_RenderCopy(getRenderer(), menu_pause.menu[i].texture, NULL, &rect);       
    }
}

extern void Input_MenuPause(SDL_Event *event)
{
    // Lecture de tous les evenements
    while (SDL_PollEvent(event) != 0)
    {
        if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE)
        {
            //changer l'etat du jeu
            getBaseGame()->estActif = false;
            return;
        }

        //
        if (event->type == SDL_KEYUP)
        {
            switch (event->key.keysym.sym)
            {
            case SDLK_LEFT:
                Gauche();
                break;
            case SDLK_RIGHT:
                Droite();
                break;
          
            case SDLK_RETURN:
                switch (getTouchePresse(getMenuPause()))
                {
                case 0:
                    getBaseGame()->state = IN_GAME;                    
                    break;
                case 1:
                    
                    getBaseGame()->state = MENU_PRINCIPAL;                    
                    return;

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



extern void Droite()
{
    //Si l'option actuellement selectionnee est differente de la premiere
    //Si on est sur la dernière option => on ne peut pas aller sur une option au-dessus 
    if (menu_pause.selectedOption + 1 < MAX_NUMBER - 1 )
    {
        //Rafraichir l'affichage
        UpdateOption(&menu_pause.menu[menu_pause.selectedOption], 1);

        //Modifier l'option selectionnee => passe a l'option precedente
        menu_pause.selectedOption++;

        //Rafraichir l'affichage
        UpdateOption(&menu_pause.menu[menu_pause.selectedOption], 0);
    }
}
extern void Gauche()
{
    //Si l'option actuellement selectionnee est differente de la premiere
    //Si on est sur la premiere option => on ne peut pas aller sur une option au-dessus
    if (menu_pause.selectedOption - 1 >= 0)
    {  
  
        //Rafraichir l'affichage
        UpdateOption(&menu_pause.menu[menu_pause.selectedOption] , 1);

        //Modifier l'option selectionnee => passe a l'option suivante
        menu_pause.selectedOption--;

        //Rafraichir l'affichage
        UpdateOption(&menu_pause.menu[menu_pause.selectedOption], 0 );
    }
    
}


extern void Nettoyer_MenuPause()
{
     // NettoyerScore();
    printf("Suppression Menu Pause\n");
    for (int i = 0; i < MAX_NUMBER - 1; i++)
    {
        if (menu_pause.menu[i].texture != NULL)
        {
            free(menu_pause.menu[i].texture);
        }
    }
    printf("Fin Suppression Menu Pause\n");
}
