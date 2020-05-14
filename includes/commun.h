/**
 * \file commun.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui a les enumerations.
 */



#ifndef _COMMUN_H
#define _COMMUN_H /**< \def _COMMUN_H*/

/**< les entites */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL_mixer.h>




/**
 *\enum bool
 *\brief énumération représentant un type booléen
 */
typedef enum 
{ 
    false, 
    true 
}bool;

/**
 *\enum typeEntite
 *\brief énumération représentant les types du jeux
 */
typedef enum  { item,  joueur, ennemi, platform ,checkpoint, 
                bull, feu,os, rock , tree, gamewin , passport }  typeEntite;


/**
 *\enum texState
 *\brief énumération les états d'une entité: fixe ou animé
 */
typedef enum { fixe, anime } texState;


extern SDL_Renderer* getRenderer(void); /**< Accès à la structure d'un rendu */


#endif
