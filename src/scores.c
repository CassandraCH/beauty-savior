/**
 * \file scores.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le score
 * \brief Initialisation, mise à jour, affichage et destruction du score
 */

#include "baseGame.h"


HUD score; /**< hud du score */
HUD niveau; /**< hud du niveau */

/** \fn  extern HUD* getScores()
 *  \brief Retourne l'instance de l'objet score
 *  \details Cela permet d'instaurer un contexte privé
 *  \return Retourne un pointeur sur l'objet score 
 */
extern HUD* getScores()
{
   return &score;
}

/** \fn  extern HUD* getNiveau()
 *  \brief Retourne l'instance de l'objet niveau
 *  \details Cela permet d'instaurer un contexte privé
 *  \return Retourne un pointeur sur l'objet niveau 
 */
extern HUD* getNiveau()
{
    return &niveau;
}