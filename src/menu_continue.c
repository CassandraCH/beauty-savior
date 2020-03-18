#include "baseGame.h"


#include "menu.h"

Menu_t menu_continue;

extern Menu_t * getMenuCon()
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

    SetHUD_IntToTexture(getScores(), "SCORES", getPlayer()->nb_objet);
    getScores()->rect.x = 530;
    getScores()->rect.y = 245;

    SetHUD_IntToTexture(getNiveau(), "NIVEAU", getPlayer()->niveau );
    getNiveau()->rect.x = 535;
    getNiveau()->rect.y = 374;

    ChargerData_Menu(0, 0, &menu_continue, "Continuer", "graphics_assets/icons_buttons/continue.png", "null", 707, 562);

    //Option selectionnee = Reprendre partie
    menu_continue.selectedOption = 0;

    menu_continue.bg = ChargerTexture("graphics_assets/levelComplete.png");
    

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

                        getBaseGame()->state = IN_GAME;
                        setNiveau(2);
                        suppListe(getCollider());
                        suppListe(getEnnemis());
                        suppListe(getBullets());
                        Init_HUD(getScores(), "SCORES : 0", 10, 0);
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
    Init_HUD(getNiveau(), "NIVEAU : 0", 530, 374);
    Init_MenuContinue();
    
    
    getBaseGame()->state = LEVEL_COMPLETED;
    getBaseGame()->time = 0;
    setTimerBullet(0);

}