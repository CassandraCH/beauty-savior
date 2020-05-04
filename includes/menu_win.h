/**
 * \file menu_win.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere le menu de la partie gagnée
 */



#ifndef _MENU_WIN_H
#define _MENU_WIN_H/**< \def _MENU_WIN_H*/

extern void GameWin_Init();                     /**< initialisation du menu de la partie gagnée  */
extern void GameWin_Input(SDL_Event *event);    /**< gestion des entrées utilisateur du menu de la partie gagnée  */

#endif
