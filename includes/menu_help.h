/**
 * \file menu_help.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere l'affichage de l'aide du jeu.
 */



#ifndef _HELP_H
#define _HELP_H/**< \def _HELP_H*/

extern void Help_Init();                    /**< initialisation du menu de l'aide  */
extern void Help_Input(SDL_Event *event); /**< Gestion des entrées utilisateur du menu de l'aide  */

#endif
