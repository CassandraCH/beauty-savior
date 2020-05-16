/**
 * \file game_over.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère les fonction en rapport avec le menu de "game over"
 */



#ifndef _MENU_GAMEOVER_H
#define _MENU_GAMEOVER_H /**< \def _MENU_GAMEOVER_H*/


extern void GameOver_Init();                    /**< fonction d'initialisation de menus game over*/

extern void GameOver_Input(SDL_Event *event);   /**< fonction input de menus game over*/

extern void GameOver_Clean();                   /**< fonction GameOver_Clean*/

extern void GameOver_Load();                    /**< fonction GameOver_Load */

#endif
