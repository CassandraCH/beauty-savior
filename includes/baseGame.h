#ifndef __BASE_GAME_H
#define __BASE_GAME_H


// Fichier d'entête pour les différents fichiers 

// #include "inventaire.h"
#include "constantes.h"


#include "inputs.h"
#include "entite.h"
#include "player.h"
#include "level.h"
#include "scores.h"
#include "items.h"
#include "listeElements.h"
#include "chargeSave.h"
#include "texture.h"
#include "enjeu.h"
#include "entite.h"
#include "menuPrincipal.h"

typedef struct baseGame 
{
    int state; /**<  */
    bool estActif; /**< Etat du jeux : Actif - Non Actif */
    int time;


}Base_Game;



/*######## GETTER & SETTER ######## */
extern SDL_Window* getWindow(void);
extern Base_Game*  getBaseGame(void);
extern LinkedList* getEnnemis();
extern LinkedList* getCollider();
extern LinkedList* getItems();
extern LinkedList* getBullets();
extern Scores* getScores(void);
extern Menu_t* getMenu(void);
extern int getTimerBullet();
extern void setTimerBullet(int time);


/*######## LISTES ######## */
extern LinkedList listEnnemis;
extern LinkedList listCollider;
extern LinkedList bullet;
extern LinkedList items;
extern void Update_Listes();


extern int tempsEcoule;
extern SDL_Rect camera;



/*####### FONCTION PRINCIPAL ############ */
extern void Init(const char *title);
extern void Update(float dt);
extern void Quitter_Jeux();
extern void Rendu_Jeux() ;

#endif