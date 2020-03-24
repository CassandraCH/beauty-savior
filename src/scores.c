/**
 * \file scores.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le score
 * \brief Initialisation, mise à jour, affichage et destruction du score
 */

#include "baseGame.h"


HUD score;
HUD niveau;


/** \fn  getScores
 *  \brief Retourne l'instance de l'objet score
 *  
 *  \return Retourne un pointeur sur l'objet score 
 *  
 *  \details Cela permet d'instaurer un contexte privée. 
 */
extern HUD* getScores()
{
   return &score;
}


extern HUD* getNiveau()
{
    return &niveau;
}