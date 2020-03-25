/**
 * \file scores.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le score
 * \brief Initialisation, mise à jour, affichage et destruction du score
 */

#include "baseGame.h"


<<<<<<< HEAD
HUD score;
HUD niveau;
HUD time_;

/** \fn  getScores
=======
HUD score; /**< hud du score */
HUD niveau; /**< hud du niveau */

/** \fn  extern HUD* getScores()
>>>>>>> origin/Chaumulon_br
 *  \brief Retourne l'instance de l'objet score
 *  \details Cela permet d'instaurer un contexte privé
 *  \return Retourne un pointeur sur l'objet score 
 */
extern HUD* getScores()
{
   return &score;
}

<<<<<<< HEAD
=======
/** \fn  extern HUD* getNiveau()
 *  \brief Retourne l'instance de l'objet niveau
 *  \details Cela permet d'instaurer un contexte privé
 *  \return Retourne un pointeur sur l'objet niveau 
 */
>>>>>>> origin/Chaumulon_br
extern HUD* getNiveau()
{
    return &niveau;
}

extern HUD* getTime()
{
    return &time_;
}