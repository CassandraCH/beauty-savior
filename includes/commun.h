#ifndef _COMMUN_H
#define _COMMUN_H

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

typedef enum  { item, joueur, ennemi, platform , bull, feu }  typeEntite;

// typedef enum {  } typeAttaque;

typedef enum { fixe, anime } texState;




extern SDL_Renderer* getRenderer(void);

#endif