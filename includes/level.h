#ifndef __LEVEL_H
#define __LEVEL_H

#include "texture.h"
// #include "inventaire.h"


typedef struct level
{
    void (*Render)();

    Texture_Manager levelTextures[5];
    
    int departX;
    int departY;
    
    int cameraX;
    int cameraY;

    
}Level;

extern Level *getLevel();
extern void ChargerNiveau();
extern void Affichage_Niveau();
extern void DestructionNiveau();

#endif 