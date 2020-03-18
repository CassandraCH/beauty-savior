/**
 * \file hud.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le compteur de temps, le compteur de vie et le score à afficher
 * \brief Affichage et mise à jour graphique des éléments
 */

#include "baseGame.h"


extern void Init_HUD(HUD * hud, const char * text, int x,  int y)
{
    hud->surface = TTF_RenderText_Solid(hud->police, text,(SDL_Color){0, 0, 0,0});
    hud->tex = SDL_CreateTextureFromSurface( getRenderer(), hud->surface );
    
    int width, height;
    SDL_QueryTexture(hud->tex, NULL, NULL, &width, &height);

    hud->rect.x = x;
    hud->rect.y = y;
    hud->rect.w = width;
    hud->rect.h = height;
    
}

extern void SetHUD_IntToTexture(HUD * hud, const char * nom, int scores)
{
    SDL_Texture * tex = hud->tex;

    if( tex != NULL )
    {
        SDL_FreeSurface(hud->surface);
        SDL_DestroyTexture(hud->tex);
    }

    char sc[30];

    sprintf( sc, "%s : %d" , nom, scores ); 
    
    hud->surface = TTF_RenderText_Solid(hud->police, sc, (SDL_Color){0, 0, 0,0});
    hud->tex = SDL_CreateTextureFromSurface( getRenderer() , hud->surface );

   
    int width, height;
    SDL_QueryTexture(hud->tex, NULL, NULL, &width, &height);

    hud->rect.w = width;
    hud->rect.h = height;
}

extern void AfficherScores(HUD * hud)
{
    SDL_Rect scor = {hud->rect.x - camera.x  ,hud->rect.y - camera.y, hud->rect.w ,hud->rect.h };
    SDL_RenderCopy(getRenderer(), hud->tex, NULL, &hud->rect);
}


extern void NettoyerHUD(HUD * hud)
{
    if(hud->tex != NULL)
    {
        printf("Nettoyer HUD\n");
        SDL_FreeSurface(hud->surface);
        SDL_DestroyTexture(hud->tex);
    }
    
}