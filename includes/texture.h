#ifndef __TEXTURE_H
#define __TEXTURE_H

#include "commun.h"

typedef struct textures
{
    int h, w;
    SDL_Texture * texture;
    
}Texture_Manager;


extern bool chargerImage(Texture_Manager * tex, const char * filename );
// extern void dessinerFullImage(Texture_Manager * tex, int x, int y);

// extern void dessinerImages( Texture_Manager * tex, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_RendererFlip flip );
// extern void ChargerTexte(Texture_Manager* tex, TTF_Font * font, const char * text );


extern void LibererRessources( Texture_Manager *tex );
extern SDL_Texture* ChargerTexture(char * filepath);
extern void ChargerTextureManager(Texture_Manager *tex, char * filepath);

#endif