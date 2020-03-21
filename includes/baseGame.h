/**
 * \file baseGame.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère les menus principal du jeu.
 */




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
#include "hud.h"
#include "menuPrincipal.h"
#include "menuLoad.h"
#include "menuPause.h"
#include "menu_continue.h"

#include "gameOver.h"

typedef struct baseGame 
{
    int state; /**< Etat du jeu : en cours de partie, sur le menu principal*/
    bool estActif; /**< Etat du jeu : Actif - Non Actif */
    int time;
}Base_Game;


/*######## GETTER & SETTER ######## */
extern SDL_Window* getWindow(void);
extern Base_Game*  getBaseGame(void);
extern LinkedList* getEnnemis(void);
extern LinkedList* getCollider(void);
extern LinkedList* getItems(void);
extern LinkedList* getBullets(void);
extern HUD* getScores(void);
extern HUD* getNiveau();
extern Menu_t* getMenu(void);
extern Menu_t * getMenuLoad();
extern Menu_t * getMenuCon(void);
extern Menu_t * getMenuPause();
extern Menu_t * getMenu_Over();
extern int getTimerBullet(void);
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
extern void LibererRessources_Jeux();
extern void Rendu_Jeux() ;
void delay(unsigned int frameLimit);

#endif