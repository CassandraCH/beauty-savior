/**
 * \file menu_win.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu de pause
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
 */

#include "baseGame.h"

Menu_t menu_win; /**< Structure de type menu_t */

/**
 * \fn extern Menu_t * getMenu_Win()
 * \brief Fonction qui permet retourner le menu concernant la fin d'une partie gagnée
 * \return une structure menu de type Menu_t
*/
extern Menu_t * getMenu_Win()
{
    return &menu_win;
}

/**
 * \fn extern void Init_MenuWin()
 * \brief Fonction qui initialise le menu du jeux gagné
 * \return pas de valeur de retour (void)
*/
extern void Init_MenuWin()
{
     int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu Win");


    //Initialisation du hud score
    SetHUD_IntToTexture( getNombreVie(), "" , 0, 550 , 392) ;
    SetHUD_IntToTexture( getScores() ,"",  0, 680 , 392 );


    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */ 

    // ChargerData_Menu(0,0,&menu_win , "Reprendre partie"
    //             ,"graphics_assets/icons_buttons/back_on_xs.png"
    //             ,"graphics_assets/icons_buttons/back_off_xs.png"
    //             ,339
    //             ,491 );

    // /* 
    //  * Deuxieme option : Retour sur le menu principal
    //  */
    // ChargerData_Menu(1,1, &menu_win ,"Retour menu"
    //             ,"graphics_assets/icons_buttons/menu_on_xs.png"
    //             ,"graphics_assets/icons_buttons/menu_off_xs.png"
    //             ,620
    //             ,491 );

    

    //Option selectionnee = Reprendre partie
    menu_win.selectedOption = 0;

    //Chargement de la texture du menu de pause
    menu_win.bg = ChargerTexture("graphics_assets/game_win.png");
}

/**
 * \fn extern void Input_MenuWin(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu
 * \details Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Input_MenuWin(SDL_Event *event)
{   
    bool isKeyPressed = false; 
    // Lecture de tous les evenements
    while (SDL_PollEvent(event) != 0)
    {
        if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE)
        {
            //changer l'etat du jeu
            getBaseGame()->estActif = false;
            return;
        }

        //Si la touche espace est pressee
        if(event->key.keysym.sym == SDLK_RETURN && event->type == SDL_KEYDOWN )
        {
            getBaseGame()->state = IN_GAME;
            return;
        }

        
    } // fin while (SDL_PollEvent)
}
