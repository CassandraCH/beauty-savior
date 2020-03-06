#ifndef ENTITY_H
#define ENTITY_H

#include "commun.h"
#include "listeElements.h"

typedef struct entite_s 
{
    #include "attributs.h"
    
}Entite;


extern bool UpdateBullets();
extern void UpdateEnnemis();
extern void collisionDetection();



#endif

