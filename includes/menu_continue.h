/**
 * \file menu_continue.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere le menu durant le jeu.
 */




#ifndef _MENU_CONTINUE_H
#define _MENU_CONTINUE_H /**< \def _MENU_CONTINUE_H*/



extern void Init_MenuContinue();/**< l'initialisation du menu continue*/


extern void Droite();/**< fonction pour aller a droite*/
extern void Gauche();/**< fonction pour aller a gauche*/

extern void Input_MenuContinue(SDL_Event *event);/**<fonction input pour le menu continue*/

extern void Nettoyer_MenuContinue();/**< fonction nettoyer pour le menu continue */

extern void Init_Continue();

#endif
