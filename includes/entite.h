#ifndef ENTITY_H
#define ENTITY_H

#include "common.h"

typedef struct entite_s 
{
    #include "attributs.h"
    
}Entite;

extern void deplacement_entiteNJ(Entite *entite);
extern void collisionDecor(Entite *entite);
// Vérifie les cas de non collision
extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);


#endif

