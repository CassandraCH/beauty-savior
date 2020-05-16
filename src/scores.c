/**
 * \file scores.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le score
 * \brief Initialisation, mise à jour, affichage et destruction du score
 */

#include "basegame.h"


HUD score; /**< hud du score */
HUD vie; /**< hud de la vie pour le menu de fin de partie */
HUD niveau; /**< hud du niveau */
HUD item_s[3];/**< hud des items du jeux */
HUD time_; /**< hud du timer */

/** \fn  extern HUD* getNombreVie()
 *  \brief Retourne le hud du nombre de vie
 *  \brief 
 *  \return Retourne un pointeur sur l'objet séléctionné 
 */
extern HUD* getNombreVie()
{
    return &vie;
}


/** \fn  extern HUD* getScores()
 *  \brief Retourne l'instance de l'objet score
 *  \brief Cela permet d'instaurer un contexte privé
 *  \return Retourne un pointeur sur l'objet score 
 */
extern HUD* getScores()
{
   return &score;
}

/** \fn  extern HUD* getNiveau()
 *  \brief Retourne l'instance de l'objet niveau
 *  \brief Cela permet d'instaurer un contexte privé
 *  \return Retourne un pointeur sur l'objet niveau 
 */
extern HUD* getNiveau()
{
    return &niveau;
}

/** \fn  extern HUD* getTime()
 *  \brief Retourne l'instance de l'objet niveau
 *  \brief Cela permet d'instaurer un contexte privé
 *  \return Retourne un pointeur sur l'objet niveau 
 */
extern HUD* getTime()
{
    return &time_;
}

/** \fn  extern HUD* getItem(int num_item) 
 *  \brief Retourne de l'item séléction
 *  \param num_item correspond au numéro de l'item selectionné
 *  \brief Cela permet d'instaurer un contexte privé
 *  \return Retourne un pointeur sur l'objet séléctionné 
 */
extern HUD* getItem(int num_item) 
{
    return &item_s[num_item];
}




