#include "baseGame.h"



extern void Init_HUD(const char * text, int x,  int y)
{
    score.surface = TTF_RenderText_Solid(score.police, text,(SDL_Color){0, 0, 0,0});
    score.tex = SDL_CreateTextureFromSurface( getRenderer(), score.surface );
    
    int width, height;
    SDL_QueryTexture(score.tex, NULL, NULL, &width, &height);

    score.rect.x = x;
    score.rect.y = y;
    score.rect.w = width;
    score.rect.h = height;
    
}

extern void NettoyerHUD()
{
    if(score.tex != NULL)
    {
        printf("Nettoyer scores\n");
        SDL_FreeSurface(score.surface);
        SDL_DestroyTexture(score.tex);
    }
    
}