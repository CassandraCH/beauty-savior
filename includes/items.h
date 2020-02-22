#ifndef _ITEMS_H
#define _ITEMS_H

#include "constantes.h"


typedef struct item
{
    #include "attributs.h"

    int nb_objet;
    bool lancer;
    float movingX;



}Items;

Items liste_items[MAX_ITEMS];

// extern void moveRectangle( Items * tab_Items );

#endif