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

void dessinerFullImage(Texture_Manager * tex, int x, int y)
{   
 	SDL_Rect dest;

	/* Règle le rectangle à dessiner selon la taille de l'image source */
	dest.x = x;
	dest.y = y;

	/* Dessine l'image entière sur l'écran aux coordonnées x et y */
	SDL_QueryTexture(tex->texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(getRenderer(), tex->texture, NULL, &dest);
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




extern void ChargerTexte(Texture_Manager* tex, TTF_Font * font, const char * text )
{
    SDL_Color white = { 0, 0, 0, 0 };

    SDL_Surface *tmp = TTF_RenderText_Blended(font, text, white);
    tex->w  = tmp->w;
    tex->h = tmp->h;
    tex->texture = SDL_CreateTextureFromSurface(getRenderer() , tmp);

    SDL_FreeSurface(tmp);
}

extern void LibererRessources( Texture_Manager *tex )
{
   SDL_DestroyTexture(tex->texture);
   tex->texture = NULL;

}