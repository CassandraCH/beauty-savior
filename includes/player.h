#ifndef _PLAYER_H
#define _PLAYER_H

#include "texture.h"
#include "constantes.h"



typedef struct player
{
   
    float vx, vy;
    int x, y;
    int w, h;
    bool estMort;
    typeEntite type;


    /**
        Données pour l'animation 
    */
    int m_frameWidth, m_frameHeight;
    int m_textureWidth, m_textureHeight;
    
    float posXDepart;
    float posYDepart;
    float numeroImage;

    SDL_Rect playerRect;
    SDL_Rect playerPosition;
    int originX, originY;
    
    int frame;

    bool estActif;
    bool estTourne;

    bool estSurSol;

    float animationSpeed;


    int nombreVies;
    bool ralenti;
    float scrollX;
    int niveau;
    
    int nb_objet;
    
    Texture_Manager tex;


}Player;



extern Player *getPlayer(void);
extern int  getPlayerX(void);
extern int  getPlayerY(void);

extern void ChargerJoueur(char* filepath, int x , int y , int framesX, int framesY);

extern int getPlayerOriginX();
extern int getPlayerOriginY();

extern void UpdateJoueur(float dt);
extern void actualiserJoueur(void);

extern void InitJoueur();
extern void setNombretir();
extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);
extern void attaqueJoueur();
extern void collision_tir();
extern void CollisionItems();

extern void InputJoueur(SDL_Event *event);
extern void AfficherJoueur();
extern void joueur_surSol();


#endif