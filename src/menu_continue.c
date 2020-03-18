#include "baseGame.h"

Menu_t menu_continue;

Menu_t * getMenuCon()
{
    return &menu_continue;
}


extern void Init_MenuContinue()
{
     int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu principal");
    
    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */ 

    menu_continue.menu[0].nomOption = "Reprendre partie";
    menu_continue.menu[0].filename[0] = "graphics_assets/icons_buttons/back_on_xs.png";
    menu_continue.menu[0].filename[1] = "graphics_assets/icons_buttons/back_off_xs.png";

    //Refraichissement de l'affichage de l'option
    UpdateOption( &menu_continue.menu[0], 0  );
    
    //Position (en x et y) de l'option dans la fenetre
    menu_continue.menu[0].x = 339;
    menu_continue.menu[0].y = 491;

    /* 
     * Deuxieme option : Retour sur le menu principal
     */
    menu_continue.menu[1].nomOption = "Retour menu";
    menu_continue.menu[1].filename[0] = "graphics_assets/icons_buttons/menu_on_xs.png";
    menu_continue.menu[1].filename[1] = "graphics_assets/icons_buttons/menu_off_xs.png";

    //Refraichissement de l'affichage de l'option
    UpdateOption(&menu_continue.menu[1], 1);
    //Position (en x et y) de l'option dans la fenetre
    menu_continue.menu[1].x = 620;
    menu_continue.menu[1].y = 491;


    //Option selectionnee = Reprendre partie
    menu_continue.selectedOption = 0;

    menu_continue.bg = ChargerTexture("graphics_assets/pause.png");


}
extern void Dessiner_MenuContinue()
{
    
    SDL_Rect rect = {300, 200, 645,432 };

    SDL_RenderCopy(getRenderer(), menu_continue.bg, NULL, &rect);

    //Pour chaque option, afficher a l'ecran son rendu
    for (int i = 0; i < MAX_NUMBER-1; i++)
    {
        //Rectangle tampon
        SDL_Rect rect = {menu_continue.menu[i].x, menu_continue.menu[i].y, menu_continue.menu[i].largeur, menu_continue.menu[i].hauteur};
        SDL_RenderCopy(getRenderer(), menu_continue.menu[i].texture, NULL, &rect);       
    }
}

extern void Input_MenuContinue(SDL_Event *event)
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
                Gauche(getMenuCon());
                break;
            case SDLK_RIGHT:
                Droite(getMenuCon());
                break;
          
            case SDLK_RETURN:
                switch (getTouchePresse(getMenuCon()))
                {
                case 0:
                    getBaseGame()->state = IN_GAME;                    
                    break;
                case 1:
                    
                    actualiserJoueur();   
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
