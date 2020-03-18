#include "baseGame.h"



Menu_t menu_continue;

Menu_t * getMenuCon()
{
    return &menu_continue;
}


extern void Init_MenuContinue()
{
     int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu Continue");
    
    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */ 

    SetScore("SCORES", getPlayer()->nb_objet);
    getScores()->rect.x = 100;
    getScores()->rect.y = 300;

    menu_continue.menu[0].nomOption = "Continue";
    menu_continue.menu[0].filename[0] = "graphics_assets/icons_buttons/continue.png";

    //Refraichissement de l'affichage de l'option
    UpdateOption( &menu_continue.menu[0], 0  );
    
    menu_continue.menu[0].x = 620;
    menu_continue.menu[0].y = 491;


    //Option selectionnee = Reprendre partie
    menu_continue.selectedOption = 0;

    menu_continue.bg = ChargerTexture("graphics_assets/levelComplete.png");


}
extern void Dessiner_MenuContinue()
{
    
    SDL_Rect rect1 = {300, 200, 647,434 };

    SDL_RenderCopy(getRenderer(), menu_continue.bg, NULL, &rect1);

    //Rectangle tampon
    SDL_Rect rect = {menu_continue.menu[0].x, menu_continue.menu[0].y, menu_continue.menu[0].largeur, menu_continue.menu[0].hauteur};
    SDL_RenderCopy(getRenderer(), menu_continue.menu[0].texture, NULL, &rect);       

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
            case SDLK_RETURN:
                switch (getTouchePresse(getMenuCon()))
                {
                case 0:
                        // DestructionNiveau();
                        getBaseGame()->state = IN_GAME;
                        setNiveau(2);
                        suppListe(getCollider());
                        suppListe(getEnnemis());
                        suppListe(getBullets());
                        PlayerScore("SCORES : 0", 10, 0);
                        getPlayer()->x = 86;
                        getPlayer()->y = 495;
                        ChargerNiveau();       
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


extern void Init_Continue()
{
    // NettoyerScore();
    // DestructionNiveau();
    Init_MenuContinue();
    getBaseGame()->state = LEVEL_COMPLETED;
    getBaseGame()->time = 0;
    setTimerBullet(0);

}