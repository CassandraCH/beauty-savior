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
* \details structure gerant les principaux objets qui seront reculter par le joueur
*/

typedef struct item
{

    float w; /** <largeur de l'entite>*/
    float h; /** < hauteur de l'entite>*/
    float x; /** <la position x >*/
    float y;  /** <la position y>*/
    float vx; /** <la velocite x la vitesse laquelle va l'entite dans une direction x>*/
    float vy; /** <la velocite y , la vitesse laquelle va l'entite dans une direction y>*/
    typeEntite type; /** <le type de l'entite>*/

    bool estMort; /** <un type booleen pour savoir c'est l'entite est mort>*/
    int nb_lancer; /** <un compteur pour savoir le nb de lancer, attaque en cours>*/

    int nb_objet;/**< le nombre d'objets*/
    bool lancer;/**< les lancers*/
    float movingX;/**< le mouvement selon la position x*/


}Items;
/**< This is the documentation for the preceding typedef */


Items liste_items[MAX_ITEMS]; /**< This is the documentation for the preceding typedef */

// extern void moveRectangle( Items * tab_Items );

#endif
