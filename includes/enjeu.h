#ifndef __INGAME_H
#define __INGAME_H

#include "commun.h"
#include "inputs.h"


extern void Input_InGame(SDL_Event *event);
extern void UpdateIngame(float dt);
extern void RenderIngame();


#endif