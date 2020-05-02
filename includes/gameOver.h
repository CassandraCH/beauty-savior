/**
 * \file gameover.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère les fonction en rapport avec le menu de "game over"
 */



#ifndef _MENU_GAMEOVER_H
#define _MENU_GAMEOVER_H /**< \def _MENU_GAMEOVER_H*/


extern void Init_MenuGameOver(); /**< fonction d'initialisation de menus game over*/

extern void Input_MenuGameOver(SDL_Event *event);/**< fonction input de menus game over*/

extern void Nettoyer_MenuGameOver();/**< fonction Nettoyer_MenuGameOver*/

extern void Init_GameOver();/**< fonction Init_GameOver*/

#endif
