/**
 * \file gameOver.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu du game over
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
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

/**
 * \fn extern void Init_MenuGameOver()
 * \brief Fonction qui initialise le menu game over
 * \return pas de valeur de retour (void)
*/
extern void Init_MenuGameOver()
{

    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu Game Over");
    
    //Creation de la texture pour le score
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
     * Deuxieme option : Chargement d'une partie
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

    //Chargement de la texture du menu game over
    menu_over.bg = ChargerTexture("graphics_assets/menu_over_bg.png");
}

/**
 * \fn extern void Input_MenuGameOver(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu
 * \details Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Input_MenuGameOver(SDL_Event *event)
{
    // Lecture de tous les evenements
    while (SDL_PollEvent(event) != 0)
    {
        //Si l'utilisateur clique sur la croix ou le bouton echap
        if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE)
        {
            //changer l'etat du jeu
            getBaseGame()->estActif = false;
            return;
        }

        //Si une touche est appuyee
        if (event->type == SDL_KEYUP)
        {
            switch (event->key.keysym.sym)
            {
                //Cas touche fleche du haut
                case SDLK_UP:
                    //Gestion du son
                    Mix_PlayChannel(-1, getMenu()->son, 0);
                    ToucheHaut(getMenu_Over());
                    break;

                //Cas touche fleche du bas
                case SDLK_DOWN:
                    //Gestion du son
                    Mix_PlayChannel(-1, getMenu()->son, 0);
                    ToucheBas(getMenu_Over());
                    break;

                //Cas de la touche entree
                case SDLK_RETURN:
                    switch (getTouchePresse(getMenu_Over()))
                    {
                        //Cas de la premiere option : nouvelle partie
                        case 0:
                            printf("Nouvelle partie depuis gameover");

                            //Nettoyage de l'affichage
                            Nettoyer_Menu(getMenu_Over(), 4);
                            Nettoyer_Menu( getMenu() , 4);

                            //Changement de l'etat du joueur
                            getPlayer()->estMort = false;

                            //Suppression des listes
                            suppListe(getCollider());
                            suppListe(getEnnemis());
                            suppListe(getBullets());

                            actualiserJoueur();

                            //Initialisation du hud score
                            Init_HUD(getScores(), "SCORES : 0", 10, 0);
                            getBaseGame()->state = IN_GAME;

                            //Charger le niveau
                            ChargerNiveau();

                            Mix_HaltMusic();
                            return;
                            break;

                        //Cas de la deuxiemme option : chargement d'une partie
                        case 1:
                            printf("Chargement depuis gameover");

                            //Nettoyage de l'affichage
                            Nettoyer_Menu(getMenu_Over(), 4);
                            Nettoyer_Menu( getMenu() , 4);

                            Init_MenuLoad();
                            Nettoyer_Menu(getMenu(), 4);
                            getBaseGame()->state = LOADING;
                            Mix_HaltMusic();
                            break;

                        //Cas de la troisieme option : quitter
                        case 2:
                            getBaseGame()->estActif = false;
                            return;
                            break;
                        default:
                            break;
                    }//fin switch
                    break;

                //Cas de la touche s
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
            }//fin switch
        }
    } // fin while (SDL_PollEvent)
}

/**
 * \fn extern void Init_GameOver()
 * \brief Fonction qui initialise l'etat game over
 * \details Gestion des entrees clavier de l'utilisateur
 * \return pas de valeur de retour (void)
*/
extern void Init_GameOver()
{
    //Changement de l'etat du joueur
    getPlayer()->estMort = true;

    //Rechargement le niveau 1
    setNiveau(1);

    Nettoyer_Menu(getMenu(), 4);
    Init_MenuGameOver();

    //Suppression des listes
    suppListe( getCollider() );
    suppListe(getEnnemis());
    suppListe(getBullets());

    //Detruire les niveau
    DestructionNiveau();

    //Changement de l'etat du jeu = game over
    getBaseGame()->state = GAMEOVER;
    getBaseGame()->time = 0;

    
    setTimerBullet(0);
}
