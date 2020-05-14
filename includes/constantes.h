/**
 * \file constantes.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère les constantes du tout le jeu, notamment les dimensions du niveau, dimensions de la fenetre et le menu pricipal.
 */





#ifndef CONSTANTS_H
/** @brief Clause de mise en garde pour le fichier CONSTANTS_H */
#define CONSTANTS_H

/** @brief  Gravite applique dans le jeu */
#define GRAVITY 0.35f

/** @brief  Nombres d'images par seconde à l'écran */
#define FPS 60

/** @brief  Nombre d'images affichable à l'écran par seconde que l'on cherche à obtenir */
#define FRAME_TARGET_TIME (1000/FPS)


/** @brief LARGEUR NIVEAU */
#define LARGEUR_NIVEAU 9000
/** @brief HAUTEUR NIVEAU */
#define HAUTEUR_NIVEAU  720

/** @brief LARGEUR FENETRE */
#define LARGEUR_FENETRE 1280
/** @brief HAUTEUR FENETRE */
#define HAUTEUR_FENETRE 720

/** @brief MENU PRINCIPAL */
#define MENU_PRINCIPAL 0

/** @brief PARTIE EN COURS */
#define IN_GAME 1

/** @brief JEU EN PAUSE */
#define PAUSE 3

/** @brief GAME OVER */
#define GAMEOVER 4

/** @brief NIVEAU TERMINE */
#define LEVEL_COMPLETED 5

/** @brief PAGE DE CHARGEMENT */
#define LOADING 6

/** @brief MENU INVENTAIRE */
#define INVENTAIRE 7

/** @brief PARTIE GAGNE */
#define GAMEWIN 8

/** @brief AIDE  */
#define HELP 9



/// MENU PRINCIPAL
/** @brief  Lancer une nouvelle partie */
#define NOUVELLE_PARTIE 0

/** @brief  Charger une partie */
#define CHARGER_PARTIE 1

/** @brief  Quitter une partie */
#define QUITTER_PARTIE 2



/** @brief  PREMIER NIVEAU */
#define NIVEAU1 1
/** @brief  DEUXIEME NIVEAU */
#define NIVEAU2 2

/** @brief  Nombre maximum d'items */
#define MAX_ITEMS 3



#endif
