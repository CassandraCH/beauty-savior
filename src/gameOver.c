/**
 * \file gameOver.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu du game over
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrées clavier et destruction du menu
 */

#include "baseGame.h"

Menu_t menu_over; /**< Structure de type menu_t */

/**
 * \fn extern Menu_t * getMenu_Over()
 * \brief Fonction qui permet retourner le menu du game over
 * \return une structure menu de type Menu_t
*/
extern Menu_t * getMenu_Over()
{
    return &menu_over;
}

/* 
 * Fonction qui initialise le menu game over
 */
extern void Init_MenuGameOver()
{

    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu Game Over");
    
    // NettoyerScore();
    SetHUD_IntToTexture(getScores(), "SCORES", getPlayer()->nb_objet, 100, 300);


    //chargement du son
    /* Son a modifier */
    menu_over.son = Mix_LoadWAV("sounds/menu_click.wav");

    menu_over.bgm = Mix_LoadMUS("sounds/awesomeness.wav");

    /* 
     * Premiere option : demarer une nouvelle partie 
     * Actif par défaut
     */

    ChargerData_Menu(0, 0, &menu_over, "Nouvelle partie", "graphics_assets/icons_buttons/newpartie_on_xs.png", "graphics_assets/icons_buttons/newpartie_off_xs.png", 469, 366);

    /* 
     * Deuxieme option : Chargement d'un partie
     */


    ChargerData_Menu(1, 1, &menu_over, "Chargement", "graphics_assets/icons_buttons/load_on_xs.png", "graphics_assets/icons_buttons/load_off_xs.png", 455, 449);
    /* 
     * Troisieme option : quitter le jeu 
     */
   

    ChargerData_Menu(2, 1, &menu_over, "Quitter", "graphics_assets/icons_buttons/quitter_on_xs.png", "graphics_assets/icons_buttons/quitter_off_xs.png", 469, 491);

    /* 
     * Quatrième option : Couper/Activer Son
     */

    ChargerData_Menu(3, 1, &menu_over, "Son", "graphics_assets/icons_buttons/sound_on_xs.png", "graphics_assets/icons_buttons/sound_off_xs.png", 487, 627);
    
    
    //Option selectionnee par défaut = la premiere (nouvelle partie)
    menu_over.selectedOption = 0;

    menu_over.bg = ChargerTexture("graphics_assets/menu_over_bg.png");

    
}




/*
 * Fonction qui permet de gérer les evenements 
 * => gestion des entrees clavier (action utilisateur)
 */
extern void Input_MenuGameOver(SDL_Event *event)
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
            case SDLK_UP:
                Mix_PlayChannel(-1, getMenu()->son, 0);
                ToucheHaut(getMenu_Over());
                break;
            case SDLK_DOWN:
                Mix_PlayChannel(-1, getMenu()->son, 0);
                ToucheBas(getMenu_Over());
                break;
            case SDLK_RETURN:
                switch (getTouchePresse(getMenu_Over()))
                {
                case 0:
                    printf("Nouvelle partie depuis gameover");
                    Nettoyer_Menu(getMenu_Over(), 4);
                    Nettoyer_Menu( getMenu() , 4);
                    getPlayer()->estMort = false;
                    suppListe(getCollider());
                    suppListe(getEnnemis());
                    suppListe(getBullets());
                    actualiserJoueur();
                    Init_HUD(getScores(), "SCORES : 0", 10, 0);
                    getBaseGame()->state = IN_GAME;
                    ChargerNiveau();
                    Mix_HaltMusic();
                    return;
                    break;
                case 1:
                    printf("Chargement depuis gameover");
                    Nettoyer_Menu(getMenu_Over(), 4);
                    Nettoyer_Menu( getMenu() , 4);
                    Init_MenuLoad();
                    Nettoyer_Menu(getMenu(), 4);
                    getBaseGame()->state = LOADING;
                    Mix_HaltMusic();
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
                if (Mix_PausedMusic() == 1)
                {
                    UpdateOption(&menu_over.menu[3], 0);
                    //On enlève la pause (la musique repart où elle en était)
                    Mix_ResumeMusic();
                }
                //Si la musique est en train de jouer
                else
                {
                    UpdateOption(&menu_over.menu[3], 1);
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


extern void Init_GameOver()
{

    getPlayer()->estMort = true;
    setNiveau(1);
    Nettoyer_Menu(getMenu(), 4);
    Init_MenuGameOver();
    suppListe( getCollider() );
    suppListe(getEnnemis());
    suppListe(getBullets());
    DestructionNiveau();
    getBaseGame()->state = GAMEOVER;
    getBaseGame()->time = 0;
    setTimerBullet(0);

    
}
