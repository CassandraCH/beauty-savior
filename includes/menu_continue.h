/**
 * \file menu_continue.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere le menu durant le jeu.
 */




#ifndef _MENU_CONTINUE_H
#define _MENU_CONTINUE_H /**< \def _MENU_CONTINUE_H*/

extern void Continue_Init();                    /**< l'initialisation du menu continue*/
extern void Continue_Input(SDL_Event *event);   /**< fonction input pour le menu continue*/
extern void Continue_Load();                    /**< Fonction de chargement des ressources du menu continue */

#endif
