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
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>




typedef enum { false, true } bool;

typedef enum  { item, joueur, ennemi, platform ,checkpoint, bull, feu }  typeEntite;

// typedef enum {  } typeAttaque;

typedef enum { fixe, anime } texState;


extern SDL_Renderer* getRenderer(void);


#endif
