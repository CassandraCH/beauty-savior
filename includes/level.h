#ifndef __LEVEL_H
#define __LEVEL_H

#include "texture.h"

typedef struct level
{

    Texture_Manager levelTextures[5];
    Texture_Manager layer_1;
    Texture_Manager layer_2;
    Texture_Manager layer_3;
    
    int departX;
    int departY;
    
    int cameraX;
    int cameraY;

    
}Level;

extern Level *getLevel();
extern void setNiveau(int niveau);
extern void ChargerNiveau();
extern void Affichage_Niveau();
extern void DestructionNiveau();

extern void afficher_textures_niveau(int niveau);
extern void Debug_AfficherCollider();

#endif 