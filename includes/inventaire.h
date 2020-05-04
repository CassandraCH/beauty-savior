/**
 * \file inventaire.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief fichier qui gere l'inventaire durant le jeu
 */




#ifndef _INVENTAIRE_H
#define _INVENTAIRE_H /**< \def _MENU_CONTINUE_H*/



extern void Init_Inventaire();/**< l'initialisation du menu continue*/

extern void setOs(int value);
extern void setRock( int value);
extern void setBranche(int value);

extern void incrementeOS();
extern void incrementeRock( );
extern void incrementeBranche();
extern void decrementeOS();
extern void decrementeRock( );
extern void decrementeBranche();

extern void Input_Inventaire(SDL_Event *event);/**<fonction input pour le menu continue*/



#endif
