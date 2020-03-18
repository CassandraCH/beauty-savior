/**
 * \file attributs.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère toutes les entites du jeu, les collisions, les attaques ...
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "commun.h"
#include "listeElements.h"



// extern bool UpdateBullets();

extern bool UpdateBullets( typeEntite typeA, typeEntite typeB );
extern void attaqueEnnemis();
extern void CreerTir( typeEntite type,int width, int height, int startX, int startY );
extern void SetNombreTir_Ennemis();
extern void UpdateEnnemis();
extern void collision_Decor( typeEntite type, float w, float h , float * x, float * y , float *vy, bool * estSurSol );
extern void collisionDetection();


#endif

