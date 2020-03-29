/**
 * \file attributs.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les attributs communs des entites
 */

float w , h; /** <largeur et hauteur de l'entite */
float x , y; /** <la position x et y*/
float vx, vy;/** <la velocite x et velocite y, la vitesse laquelle va l'entite dans une direction*/
typeEntite type; /** <le type de l'entite*/

bool estMort;/** <un type booleen pour savoir c'est l'entite est mort*/
int nb_lancer;/** <un compteur pour savoir le nb de lancer, attaque en cours*/