/**
 * \file attributs.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Fichier regroupant les attributs en commun des entités 
 * \details Ce fichier est utilisé afin d'éviter la redondance de déclarations.
 */

float w;    /*!< largeur de l'entite    */
float h;    /*!<  hauteur de l'entite   */
float x;    /*!< la position x  */
float y;    /*!< la position y  */
float vx;   /*!< la velocite x la vitesse laquelle va l'entite dans une direction x */
float vy;   /*!< la velocite y , la vitesse laquelle va l'entite dans une direction y   */
typeEntite type; /*!< le type de l'entite   */

bool estMort; /*!< un type booleen pour savoir c'est l'entite est mort> */
int nb_lancer; /*!< un compteur pour savoir le nb de lancer, attaque en cours>  */
