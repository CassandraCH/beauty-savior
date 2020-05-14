/**
 * \file menuPrincipal.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere le menu  pricipal du  jeu.
 */

#ifndef _MENU_PRINCIPAL_H
/**< \def _MENU_PRINCIPAL_H*/
#define _MENU_PRINCIPAL_H



extern void Principal_Init();                   /**<initialisation du menu principal */
extern void Principal_Input(SDL_Event *event);  /**<gestion des entrées utilisateur du menu principal */

#endif
