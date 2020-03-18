/**
 * \file constantes.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère les constantes du tout le jeu, notamment les dimensions du niveau, dimensions de la fenetre et le menu pricipal.
 */





#ifndef CONSTANTS_H
#define CONSTANTS_H

#define GRAVITY 0.35f

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

//Dimensions du niveau
#define LARGEUR_NIVEAU 9000
#define HAUTEUR_NIVEAU  720

//Dimensions de la fenetre
#define LARGEUR_FENETRE 1280
#define HAUTEUR_FENETRE 720

#define MENU_PRINCIPAL 0
#define IN_GAME 1
#define LEVEL_COMPLETED 5
#define PAUSE 3
#define GAMEOVER 4


/// MENU PRINCIPAL
#define NOUVELLE_PARTIE 0
#define CHARGER_PARTIE 1
#define QUITTER_PARTIE 2


#define NIVEAU1 1
#define NIVEAU2 2

#define MAX_ITEMS 3






#endif