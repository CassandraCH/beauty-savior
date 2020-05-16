/**
 * \file menu_pause.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere le menu pause du jeu.
 */



#ifndef _MENU_PAUSE_H
#define _MENU_PAUSE_H/**< \def _MENU_PAUSE_H*/

extern void Pause_Init();                   /**< initialisation du menu de pause */
extern void Pause_Input(SDL_Event *event);  /**< gestion des entrées utilisateur du menu de pause */

#endif
