#ifndef __TEXTURE_H
#define __TEXTURE_H /** \def TEXTURE_H */

#include "commun.h" /** les structures du fichier commun.h */

typedef struct textures /** structure des differentes  textures du jeu*/
{
    int h, w;/**<la taille , la largueur de la texture*/
    int row;
    SDL_Texture * texture;

}Texture_Manager;


extern bool chargerImage(Texture_Manager * tex, const char * filename );/**< booleen charger des images*/
extern void dessinerFullImage(Texture_Manager * tex, int x, int y);
extern void dessinerImages( Texture_Manager * tex, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_RendererFlip flip );
extern void ChargerTexte(Texture_Manager* tex, TTF_Font * font, const char * text );
extern void LibererRessources( Texture_Manager *tex );/**< liberation des ressources*/
extern SDL_Texture* ChargerTexture(char * filepath);/**< charger de texture de filepath(chemin de fichier)*/
extern void ChargerTextureManager(Texture_Manager *tex, char * filepath);/**<charger des texture visuel  principal dans le jeu*/

#endif
