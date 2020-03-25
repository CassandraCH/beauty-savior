/**
 * \file texture.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère les textures (affichage)
 * \brief Chargement des images, des textures, des textes et destruction des textures
 */
#include "texture.h"




bool chargerImage(Texture_Manager * tex,const char * filename )
{
    
    printf("Charger image\n");
    SDL_Surface* pTempSurface = IMG_Load( filename );
    if(pTempSurface == 0)
    {
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(getRenderer() , pTempSurface);
    tex->w = pTempSurface->w;
    tex->h = pTempSurface->h;

    if(pTexture != 0)
    {
        SDL_FreeSurface(pTempSurface);
        tex->texture = pTexture;
        return true;
    }
    
    return false;
}



extern void ChargerTextureManager(Texture_Manager *tex, char * filepath )
{
    printf("Chargement texture DECOR");

    if( tex->texture != NULL )
    {
        SDL_DestroyTexture(tex->texture);
    }
    
    tex->texture = NULL;
    
    
    SDL_Surface *surface = IMG_Load(filepath);
    
    if( !surface )
    {
        printf("Cannot find %s..\n",filepath);
        SDL_Quit();
        exit(1);
    }
    else {
        tex->texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
        if( !tex->texture )
            printf("Erreur: %s",filepath);
    }

    SDL_FreeSurface(surface); 
}

extern SDL_Texture *ChargerTexture( char * filepath )
{
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = IMG_Load(filepath);
    if( !surface )
    {
        printf("Cannot find %s..\n",filepath);
        SDL_Quit();
        exit(1);
    }
    else {
        texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
        if( !texture )
             printf("Erreur: %s",filepath);
    }

    SDL_FreeSurface(surface);

    return texture;
}



extern void dessinerImages(Texture_Manager * tex, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);

    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(getRenderer(), tex->texture , &srcRect, &destRect, 0, 0, flip);
}




extern void LibererRessources( Texture_Manager *tex )
{
   SDL_DestroyTexture(tex->texture);
   tex->texture = NULL;

}