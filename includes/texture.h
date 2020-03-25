#ifndef __TEXTURE_H
#define __TEXTURE_H

#include "commun.h"

typedef struct textures
{
    int h, w;
    SDL_Texture * texture;
    
}Texture_Manager;


extern bool chargerImage(Texture_Manager * tex, const char * filename );

extern void LibererRessources( Texture_Manager *tex );
extern SDL_Texture* ChargerTexture(char * filepath);
extern void ChargerTextureManager(Texture_Manager *tex, char * filepath);

#endif