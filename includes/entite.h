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
extern void collision_Decor();
// extern void collision_Decor( typeEntite type, float w, float h , float * x, float * y , float *vy, bool * estSurSol );
extern void collisionDetection();


#endif

