/**
 * \file gameOver.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu du game over
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrées clavier et destruction du menu
 */

#include "baseGame.h"

Menu_t menu_over;

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
    SetScore("SCORES", getPlayer()->nb_objet);
    getScores()->rect.x = 100;
    getScores()->rect.y = 300;
    // PlayerScorrect->e("SCORE
    // PlayerScorrect->y("S4ORES : 0", 10, 0);

    //chargement du son
/* Son a modifier */
    menu_over.son = Mix_LoadWAV("sounds/menu_click.wav");

    menu_over.bgm = Mix_LoadMUS("sounds/awesomeness.wav");

    /* 
     * Premiere option : demarer une nouvelle partie 
     * Actif par défaut
     */

    menu_over.menu[0].nomOption = "Nouvelle partie";
/* Changer les fichiers => mettre "nouvelle partie" */
<<<<<<< HEAD
    menu_over.menu[0].filename[0] = "graphics_assets/newpartie_on_xs.png";
    menu_over.menu[0].filename[1] = "graphics_assets/newpartie_off_xs.png";
=======
    menu_over.menu[0].filename[0] = "graphics_assets/icons_buttons/newpartie_on_xs.png";
    menu_over.menu[0].filename[1] = "graphics_assets/icons_buttons/newpartie_off_xs.png";
>>>>>>> 723ab1285700ea88dda443bee94dc142e3e2d8f3

    //Refraichissement de l'affichage de l'option
    UpdateOption(&menu_over.menu[0], 0);

    //Position (en x et y) de l'option dans la fenetre
    menu_over.menu[0].x = 469;
    menu_over.menu[0].y = 366;

    /* 
     * Deuxieme option : Chargement d'un partie
     */
    menu_over.menu[1].nomOption = "Chargement";
    menu_over.menu[1].filename[0] = "graphics_assets/icons_buttons/load_on_xs.png";
    menu_over.menu[1].filename[1] = "graphics_assets/icons_buttons/load_off_xs.png";

    //Refraichissement de l'affichage de l'option
    UpdateOption(&menu_over.menu[1], 1);
    //Position (en x et y) de l'option dans la fenetre
    menu_over.menu[1].x = 455;
    menu_over.menu[1].y = 449;

    /* 
     * Troisieme option : quitter le jeu 
     */
    menu_over.menu[2].nomOption = "Quitter";
    menu_over.menu[2].filename[0] = "graphics_assets/icons_buttons/quitter_on_xs.png";
    menu_over.menu[2].filename[1] = "graphics_assets/icons_buttons/quitter_off_xs.png";


    //Refraichissement de l'affichage de l'option
    UpdateOption(&menu_over.menu[2], 1);
    //Position (en x et y) de l'option dans la fenetremake

    menu_over.menu[2].x = 469;
    menu_over.menu[2].y = 491;

    /* 
     * Quatrième option : Couper/Activer Son
     */
    menu_over.menu[3].nomOption = "Son";
    menu_over.menu[3].filename[0] = "graphics_assets/icons_buttons/sound_on_xs.png";
    menu_over.menu[3].filename[1] = "graphics_assets/icons_buttons/sound_off_xs.png";


    //Refraichissement de l'affichage de l'option
    UpdateOption(&menu_over.menu[3], 0);
    //Position (en x et y) de l'option dans la fenetre
    menu_over.menu[3].x = 487;
    menu_over.menu[3].y = 627;

    //Option selectionnee = la premiere (nouvelle partie)
    menu_over.selectedOption = 0;

    menu_over.bg = ChargerTexture("graphics_assets/menu_over_bg.png");
}



/*
 * Fonction qui permet d'afficher le menu principal
 * => affichage les differentes options
 */
extern void Dessiner_MenuGameOver()
{

    SDL_Rect rect = {0, 0, 1280, 720};

    SDL_RenderCopy(getRenderer(), menu_over.bg, NULL, &rect);

    //Pour chaque option, afficher a l'ecran son rendu
    for (int i = 0; i < MAX_NUMBER + 1; i++)
    {
        //Rectangle tampon
        SDL_Rect rect = {menu_over.menu[i].x, menu_over.menu[i].y, menu_over.menu[i].largeur, menu_over.menu[i].hauteur};
        SDL_RenderCopy(getRenderer(), menu_over.menu[i].texture, NULL, &rect);
    }
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
            case SDLK_LEFT:

                break;
            case SDLK_RETURN:
                switch (getTouchePresse(getMenu_Over()))
                {
                case 0:
                    getPlayer()->estMort = false;
                    suppListe(getCollider());
                    suppListe(getEnnemis());
                    suppListe(getBullets());
                    actualiserJoueur();
                    PlayerScore("SCORES : 0", 10, 0);
                    getBaseGame()->state = IN_GAME;
                    ChargerNiveau();
                    // Nettoyer_MenuPrincipal();
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

/*
 * Fonction qui permet de supprimer le menu => liberation de la memoire
 */
extern void Nettoyer_MenuGameOver()
{
    // NettoyerScore();
    printf("Suppression Menu Game Over\n");
    for (int i = 0; i < MAX_NUMBER + 1; i++)
    {
        if (menu_over.menu[i].texture != NULL)
        {
            free(menu_over.menu[i].texture);
        }
    }
    printf("Fin Suppression Menu Game Over\n");
    return;
}

extern void Init_GameOver()
{

    getPlayer()->estMort = true;
    Nettoyer_MenuPrincipal();
    Init_MenuGameOver();
    DestructionNiveau();
    getBaseGame()->state = GAMEOVER;
    getBaseGame()->time = 0;
    setTimerBullet(0);
    
}