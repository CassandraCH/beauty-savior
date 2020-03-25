/**
 * \file items.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme mise a jour des fichiers principaux de attributs.h
 */



#ifndef _ITEMS_H
#define _ITEMS_H /**< \def _ITEMS_H*/

#include "constantes.h"
/**
* \struct item
* \details structure gerant
*/

typedef struct item
{
    #include "attributs.h"

    int nb_objet;/**< le nombre d'objets*/
    bool lancer;/**< les lancers*/
    float movingX;/**< le mouvement selon la position x*/



}Items;

Items liste_items[MAX_ITEMS];

// extern void moveRectangle( Items * tab_Items );

#endif
