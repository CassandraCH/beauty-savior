#ifndef _PLAYER_H
#define _PLAYER_H

#include "texture.h"
#include "constants.h"



typedef struct player
{
   
    #include "attributs.h"

    float posXDepart;
    float posYDepart;

    int nombreVies;
    bool ralenti;
    float scrollX;
    int niveau;
    int lancer;
    Texture_Manager tex;


}Player;


extern Player *getPlayer(void);
extern int  getPlayerX(void);
extern int  getPlayerY(void);
extern void setPlayerX(int valeur);
extern void setPlayerY(int valeur);
extern void UpdateJoueur(float dt);
extern void actualiserJoueur(void);

extern void InitJoueur(Player *player);
extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);

extern void InputJoueur(const Uint8 * keystates);
extern void AfficherJoueur();


#endif