/**
 * \file texture.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere les texture du jeu .
 */





#ifndef __TEXTURE_H
#define __TEXTURE_H /** \def TEXTURE_H */

#include "commun.h" /** les structures du fichier commun.h */

typedef struct textures /** structure des differentes  textures du jeu*/
{
    int h, w;
    SDL_Texture * texture;

}Texture_Manager;



extern bool chargerImage(Texture_Manager * tex, const char * filename );/**< booleen charger des images*/


extern void LibererRessources( Texture_Manager *tex );/**< liberation des ressources*/
extern SDL_Texture* ChargerTexture(char * filepath);/**< charger de texture de filepath(chemin de fichier)*/
extern void ChargerTextureManager(Texture_Manager *tex, char * filepath);/**<charger des texture visuel  principal dans le jeu*/
extern bool chargerImage(Texture_Manager * tex, const char * filename );/**<chargements des images*/

extern void LibererRessources( Texture_Manager *tex );/**< les ressources*/
extern SDL_Texture* ChargerTexture(char * filepath);/**<chargement des textures*/

extern void ChargerTextureManager(Texture_Manager *tex, char * filepath);

#endif
