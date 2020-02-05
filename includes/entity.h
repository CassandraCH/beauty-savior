#ifndef _ENTITY_H
#define _ENTITY_H

#include "commun.h"

/**
*\file entity.h
*\brief Fichier d'en-tête pour la définition du type Entité 
*/

/**
 * \typedef Entity_t 
 * \brief typedef pour la structure Entity 
 *\struct Entity
 *\brief Structure de base réprésentant les entités vivantes du jeux
 */
typedef struct Entity
{   
    int pointDeVie; /**< Point de vie */
    int x; /**< Position en y */
    int y; /**< Position en y */
    
    int l; /**< Largeur du sprite */
    int h; /**< Hauteur du sprite */

    bool checkPointActif; /**< Vérifie si l'entité est actif ou non */

    Etat etat; /**< Etat du sprite ( en vie,  inactif, mort, saute )  */
    int direction; /**< Direction dans laquelle  se déplace l'entité ( gauche / droite ) */


}Entity_t;


#endif