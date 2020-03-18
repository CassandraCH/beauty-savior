/**
 * \file items.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme mise a jour des fichiers principaux
 */



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