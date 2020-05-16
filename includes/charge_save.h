/**
 * \file charge_save.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui s'occupe du chargement et sauvegarde de manière globaliser, chargement des niveaux, des items, des boites de collisions, sauvegarde du joueur. En general la sauvegarde et chargement én général.
 */


#ifndef __LOAD_SAVE_H /**< \def __LOAD_SAVE_H*/
#define __LOAD_SAVE_H /**< \def __LOAD_SAVE_H*/


#include "commun.h"
#include "baseGame.h"

extern void LoadGame();                                             /**< les chargements des parties */
extern void SaveGame();                                             /**< les sauvegardes de parties */
extern void SaveCollider_Position();                                /**< les collider de position */
extern void LoadCollider(const char * filename);                    /**< chargement des collider*/
extern void LoadAndCreate_PNJ(LinkedList*lst, char * filename);     /**< chargement et créations des PNJ ( personnage non joueur ) */
extern void LoadEnemies(const char * filename);                     /**< chargement des ennemis*/
extern void LoadItems(const char * filename, SDL_Texture * tex);    /**< chargement des items */



#endif
