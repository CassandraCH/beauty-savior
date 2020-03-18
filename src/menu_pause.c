#include "baseGame.h"

Menu_t menu_pause;

extern Menu_t * getMenuPause()
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

    ChargerData_Menu(0,0,&menu_pause , "Reprendre partie"
                ,"graphics_assets/icons_buttons/back_on_xs.png"
                ,"graphics_assets/icons_buttons/back_off_xs.png"
                ,339
                ,491 );


    /* 
     * Deuxieme option : Retour sur le menu principal
     */

     ChargerData_Menu(1,1, &menu_pause ,"Retour menu"
                ,"graphics_assets/icons_buttons/menu_on_xs.png"
                ,"graphics_assets/icons_buttons/menu_off_xs.png"
                ,620
                ,491 );


    //Option selectionnee = Reprendre partie
    menu_pause.selectedOption = 0;

    menu_pause.bg = ChargerTexture("graphics_assets/pause.png");
    

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
                Gauche(getMenuPause());
                break;
            case SDLK_RIGHT:
                Droite(getMenuPause());
                break;
          
            case SDLK_RETURN:
                switch (getTouchePresse(getMenuPause()))
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


