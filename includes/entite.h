/**
 * \file entite.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère toutes les entites du jeu, les collisions, les attaques ...
 */


#ifndef ENTITY_H
#define ENTITY_H /**< \def  ENTITY_H*/

#include "commun.h"
#include "listeElements.h"



extern void Enemy_Attack();                                         /**< fonction attaque Ennemis       */
extern void Enemy_SetBullets();                                     /**< fonction les tirs ennemis      */
extern void Enemy_Update();                                         /**< fonction Enemy_Update          */

extern void CreateBullet( typeEntite type,int width, int height, int startX, int startY );  /**< fonction tir avec parametres le type,selon la largueur, la taille et selon les vecteurs x et y */
extern bool Bullets_Update( typeEntite typeA, typeEntite typeB );   /**< booleen pour les Bullets_Update */

extern void Level_Collision();                                      /**< fonction collision de decor    */
extern void Collision_Detection();                                  /**< les detection de collisions    */


#endif
