#ifndef _PLAYER_H
#define _PLAYER_H

#include "texture.h"
#include "constantes.h"



typedef struct player
{
   
    #include "attributs.h"
    float posXDepart;
    float posYDepart;

    bool estTourne;
    bool estSurSol;
    
    int nombreVies;
    bool ralenti;
    float scrollX;
    int niveau;
    int nb_lancer;
    Texture_Manager tex;


}Player;


extern Player *getPlayer(void);
extern int  getPlayerX(void);
extern int  getPlayerY(void);

extern int getPlayerOriginX();
extern int getPlayerOriginY();

extern void UpdateJoueur(float dt);
extern void actualiserJoueur(void);

extern void InitJoueur();
extern void setNombretir();
extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);
extern void lancerAttaque();
extern void collision_tir();
extern void CollisionItems();

extern void InputJoueur(SDL_Event *event);
extern void AfficherJoueur();


#endif