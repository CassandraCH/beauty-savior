/**
 * \file baseGame.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère les menus principal du jeu.
 */


#ifndef __BASE_GAME_H
#define __BASE_GAME_H /**< \def __BASE_GAME_H*/


// Fichier d'entête pour les différents fichiers

#include "constantes.h"


#include "entite.h"
#include "player.h"
#include "level.h"
#include "listeElements.h"
#include "chargeSave.h"
#include "texture.h"

#include "entite.h"
#include "hud.h"
#include "inventaire.h"
#include "menuPrincipal.h"
#include "menuLoad.h"
#include "menuPause.h"
#include "menu_win.h"
#include "menu_continue.h"
#include "menu_help.h"

#include "interface.h"

#include "gameover.h"


/**
 *\struct baseGame
 *\details Structure principale de jeux, qui gère tous les composants du jeux majeurs.
 */
typedef struct baseGame
{
    int state; /**< Etat du jeu : en cours de partie, sur le menu principal */
    bool estActif; /**< Etat du jeu : Actif - Non Actif */
    int time;  /**< time : temps du jeux */

    int min; /**<  : temps liée au timer du jeux : minutes du jeux */
    
    int tempsPrecedent; /**<  temps précédent en référence au temps écoulé depuis la dernière image */
    int tempsActuel;  /**<  temps actuel en référence au temps écoulé depuis la dernière image */

    SDL_Texture * passportReq; /**< Texture du passeport nécéssaire pour le niveau */

}Base_Game; 
/**< This is the documentation for the preceding typedef */


#include "definitions.h"



#endif
