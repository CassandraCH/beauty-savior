/**
 * \file menu_continue.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief fichier qui gere l'inventaire durant le jeu
 */




#ifndef _INVENTAIRE_H
#define _INVENTAIRE_H /**< \def _MENU_CONTINUE_H*/



extern void Init_Inventaire();/**< l'initialisation du menu continue*/

extern void Input_Inventaire(SDL_Event *event);/**<fonction input pour le menu continue*/

extern void Nettoyer_Inventaire();/**< fonction nettoyer pour le menu continue */


#endif
