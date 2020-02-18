#ifndef __LOAD_SAVE_H
#define __LOAD_SAVE_H

#include "baseGame.h"
#include "commun.h"


extern void ChargerPartie();
extern void SauvegarderPartie();

extern void SauvegarderPos_Noeud(LinkedList * lstptr);

extern void ChargementCollider(const char * filename);
extern void Chargement_CreationPNJ(const char * filename);
extern void ChargementEnnemis(const char * filename);

#endif