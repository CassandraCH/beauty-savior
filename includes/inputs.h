/**
 * \file inputs.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme 
 */


#ifndef __INPUT_H_
#define __INPUT_H_

#include "commun.h"




typedef struct input
{
    bool left, right, up, down, jump, attack, enter, erase, pause, escape;
    SDL_Event event;
 
} Input;

extern void ProcessInput(SDL_Event* event);



#endif