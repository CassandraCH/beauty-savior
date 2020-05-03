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



extern bool UpdateBullets( typeEntite typeA, typeEntite typeB );/**< booleen pour les UpdateBullets*/
extern void attaqueEnnemis();/**< fonction attaque Ennemis*/
extern void CreerTir( typeEntite type,int width, int height, int startX, int startY );/**< fonction tir avec parametres le type,selon la largueur, la taille et selon les vecteurs x et y */
extern void SetNombreTir_Ennemis();/**< fonction les tirs ennemis */
extern void UpdateEnnemis();/**< fonction UpdateEnnemis */
extern void collision_Decor();/**< fonction collision de decor*/
extern void collisionDetection();/**< les detection de collisions*/


#endif
