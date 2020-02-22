#ifndef _SCORES_H
#define _SCORES_H

#include "commun.h"
#include "texture.h"


typedef struct score
{
    int meilleurScore;
    int scoreActuel;

    TTF_Font* police;
	SDL_Surface* surface;
    SDL_Texture *tex;
	SDL_Rect rect;

}Scores;


extern void Init_Scores();
extern void DessinerScores();
extern void SetScore(int scores);
extern void PlayerScore(int x,  int y);
extern void nouveauScore();



#endif