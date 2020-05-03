/**
 * \file menu_pause.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu de pause
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
 */

#include "baseGame.h"

Menu_t help; /**< Structure de type menu_t */

/**
 * \fn extern Menu_t * getMenuPause()
 * \brief Fonction qui permet retourner le menu de pause
 * \return une structure menu de type Menu_t
*/
extern Menu_t * getHelp()
{
    return &help;
}

/**
 * \fn extern void Init_MenuPause()
 * \brief Fonction qui initialise le menu de pause
 * \return pas de valeur de retour (void)
*/
extern void Init_Help()
{
     int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Help");
    
    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */ 

    help.nom_menu = "Help";


    //Option selectionnee = Reprendre partie
    help.selectedOption = 0;

    //Chargement de la texture de l'aide
    help.bg = ChargerTexture("graphics_assets/keyboard_help.png");
}

/**
 * \fn extern void Input_MenuPause(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu
 * \details Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Input_Help(SDL_Event *event)
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

        //Si une touche est appuyee
        if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_RETURN )
        {
            getBaseGame()->state = IN_GAME;                    
            break;

        }
    

    } // fin while (SDL_PollEvent)
}
