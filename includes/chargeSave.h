/**
 * \file chargeSave.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui s'occupe du chargement et sauvegarde de manière globaliser,
 chargement des niveaux, des items, des boites de collisions
 Sauvegarde du joueur.
 En general la sauvegarde et chargement én général.
 */


#ifndef __LOAD_SAVE_H
#define __LOAD_SAVE_H


#include "commun.h"
#include "baseGame.h"

extern void ChargerPartie();
extern void SauvegarderPartie();

extern void SaveCollider_Position();

extern void ChargementCollider(const char * filename);
extern void Chargement_CreationPNJ(LinkedList*lst, char * filename);
extern void ChargementEnnemis(const char * filename);
extern void ChargementItems(const char * filename, SDL_Texture * tex);



#endif