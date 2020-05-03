/**
 * \file input.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les entrées de l'utilisateur en fonction de si l'utilisateur est en train de jouer ou bien sur le menu principal
 */
#include "baseGame.h"

/**
 * \fn extern void ProcessInput(SDL_Event * event)
 * \brief Fonction qui gère les entrées utilisateur
 * \details En fonction de si l'utilisateur est en cours de partie, sur le menu principal, sur le menu pause, sur le menu game over ou si le niveau vient d'être achevé
 * \param event evenement (entree utilisateur)
 * \return pas de valeur de retour (void)
*/
extern void ProcessInput(SDL_Event * event)
{
    //Cas où l'utilsateur est sur le menu principal
    if (getBaseGame()->state == MENU_PRINCIPAL )
    {
        Input_MenuPrincipal(event);
    }

    //Cas où l'utilsateur est en cours de partie
    else if (getBaseGame()->state == IN_GAME )
    {
        Input_InGame(event);
    }

    //Cas où l'utilsateur est sur le menu pause
    else if ( getBaseGame()->state == PAUSE )
    {
        Input_MenuPause(event);
    }

    //Cas où l'utilsateur est sur le menu de l'inventaire
    else if ( getBaseGame()->state == INVENTAIRE )
    {
        Input_Inventaire(event);
    }

    //Cas où l'utilsateur est sur le menu de chargement
    else if ( getBaseGame()->state == LOADING )
    {
        Input_MenuLoad(event);
    }

    //Cas où l'utilsateur vient de terminer le niveau
    else if( getBaseGame()->state == LEVEL_COMPLETED )
    {
        Input_MenuContinue(event);
    }

    //Cas où l'utilsateur a gagné le jeu (terminé tous les niveaux)
    else if ( getBaseGame()->state == GAMEWIN )
    {
        Input_MenuWin( event );
    }

    //Cas où l'utilsateur est sur le menu game over
    else if (getBaseGame()->state == GAMEOVER)
    {
        Input_MenuGameOver(event);
    }

}