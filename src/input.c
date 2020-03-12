/**
 * \file input.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les entrées de l'utilisateur en fonction de si l'utilisateur est en train de jouer ou bien sur le menu principal
 */
#include "baseGame.h"

/**
 * Gestion des entrées utilisateurs.
 */ 
extern void ProcessInput(SDL_Event * event)
{

   if (getBaseGame()->state == MENU_PRINCIPAL )
   {
        Input_MenuPrincipal(event);
   }
   else if (getBaseGame()->state == IN_GAME )
   {
       Input_InGame(event);
   }
   

}