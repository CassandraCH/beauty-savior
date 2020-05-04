/**
 * \file chargeSave.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui s'occupe du chargement et sauvegarde de manière globaliser, chargement des niveaux, des items, des boites de collisions, sauvegarde du joueur. En general la sauvegarde et chargement én général.
 */


#ifndef __LOAD_SAVE_H /**< \def __LOAD_SAVE_H*/
#define __LOAD_SAVE_H /**< \def __LOAD_SAVE_H*/


#include "commun.h"
#include "baseGame.h"

extern void LoadGame();                 /**< les charger des parties */
extern void SaveGame();                 /**< les sauvegarde de parties */
extern void SaveCollider_Position();    /**< les collider de position */
extern void LoadCollider(const char * filename);                    /**< chargements des collider*/
extern void LoadAndCreate_PNJ(LinkedList*lst, char * filename);     /**< chargements et créations des PNJ ( personnage non joueur ) */
extern void LoadEnemies(const char * filename);                     /**< chargements des ennemis*/
extern void LoadItems(const char * filename, SDL_Texture * tex);    /**< chargements des items */



#endif
