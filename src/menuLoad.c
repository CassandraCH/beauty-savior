#include "baseGame.h"

Menu_t menu_load;

extern Menu_t * getMenuLoad()
{
    return &menu_load;
}


extern void Init_MenuLoad()
{
     int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu principal");
    
      
    ChargerPartie();
    SetHUD_IntToTexture(getScores(), "SCORES", getPlayer()->nb_objet, 490, 245);


    SetHUD_IntToTexture(getNiveau(), "NIVEAU", getPlayer()->niveau , 490, 374 );

    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */ 

    ChargerData_Menu(0,0,&menu_load , "Retour"
                
                ,"graphics_assets/icons_buttons/return_on_xs.png"
                ,"graphics_assets/icons_buttons/return_off_xs.png"
                ,339
                ,570 );


    /* 
     * Deuxieme option : Retour sur le menu principal
     */

     ChargerData_Menu(1,1, &menu_load ,"Charger Partie"
                ,"graphics_assets/icons_buttons/load_on_xs.png"
                ,"graphics_assets/icons_buttons/load_off_xs.png"
                ,620
                ,570 );


    //Option selectionnee = Reprendre partie
    menu_load.selectedOption = 0;

    menu_load.bg = ChargerTexture("graphics_assets/chargement.png");
    

}

extern void Input_MenuLoad(SDL_Event *event)
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
                Gauche(getMenuLoad());
                break;
            case SDLK_RIGHT:
                Droite(getMenuLoad());
                break;
          
            case SDLK_RETURN:
                switch (getTouchePresse(getMenuLoad()))
                {
                case 0:

                    Nettoyer_Menu(getMenuLoad(), 2);
                    Nettoyer_Menu( getMenu_Over() , 4);
                    actualiserJoueur();
                    getBaseGame()->state = MENU_PRINCIPAL;                     
                    break;
                case 1:
                    
                    DestructionNiveau();
                    actualiserJoueur();
                    getPlayer()->estMort = false;
                    SetHUD_IntToTexture(getScores(), "SCORES", getPlayer()->nb_objet, 10, 0);
                  
                    Nettoyer_Menu(getMenu(), 4);
                    ChargerNiveau();
                   
                    getBaseGame()->state = IN_GAME;
                    Mix_HaltMusic();
                   
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


