/**
 * \file texture.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere les texture du jeu .
 */





#ifndef __TEXTURE_H
/** @brief Clause de mise en garde pour le fichier TEXTURE_H */
#define __TEXTURE_H /

#include "commun.h" /** les structures du fichier commun.h */

typedef struct textures /** structure des differentes  textures du jeu*/
{
    int h; /*!<  hauteur de la texture*/
    int w; /*!< largeur de la texture*/
    SDL_Texture * texture; /*!< texture */

}Texture_Manager;



extern bool Image_Load(Texture_Manager * tex, const char * filename );/**< booleen charger des images*/


extern void TexManager_DestroyRessources( Texture_Manager *tex );/**< liberation des ressources*/
extern SDL_Texture* Texture_Load(char * filepath);/**< charger de texture de filepath(chemin de fichier)*/
extern void TextureManager_Load(Texture_Manager *tex, char * filepath);/**<charger des texture visuel  principal dans le jeu*/
extern bool Image_Load(Texture_Manager * tex, const char * filename );/**<chargements des images*/

extern void TexManager_DestroyRessources( Texture_Manager *tex );/**< les ressources*/
extern SDL_Texture* Texture_Load(char * filepath);/**<chargement des textures*/

extern void TextureManager_Load(Texture_Manager *tex, char * filepath);

#endif
