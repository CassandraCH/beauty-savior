/**
 * \file constantes.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère les constantes du tout le jeu, notamment les dimensions du niveau, dimensions de la fenetre et le menu pricipal.
 */





#ifndef CONSTANTS_H/**< CONSTANTS_H*/
#define CONSTANTS_H/**< \def CONSTANTS_H*/

#define GRAVITY 0.35f

#define FPS 60
#define FRAME_TARGET_TIME (1000/FPS)

//Dimensions du niveau
#define LARGEUR_NIVEAU 9000 /**< \def LARGEUR_NIVEAU */
#define HAUTEUR_NIVEAU  720 /**< \def HAUTEUR_NIVEAU */

//Dimensions de la fenetre
#define LARGEUR_FENETRE 1280 /**< CONSTANTS_H*/
#define HAUTEUR_FENETRE 720 /**< CONSTANTS_H*/

#define MENU_PRINCIPAL 0 /**< MENU_PRINCIPAL*/
#define IN_GAME 1 /**< IN_GAME*/
#define PAUSE 3 /**< PAUSE*/
#define GAMEOVER 4 /**< GAMEOVER*/
#define LEVEL_COMPLETED 5 /**< LEVEL_COMPLETED*/
#define LOADING 6 /**< LOADING*/


/// MENU PRINCIPAL
#define NOUVELLE_PARTIE 0 /**< NOUVELLE_PARTIE*/
#define CHARGER_PARTIE 1 /**< ChargerPartie */
#define QUITTER_PARTIE 2 /**< QUITTER_PARTIE */


#define NIVEAU1 1
#define NIVEAU2 2

#define MAX_ITEMS 3



#endif
