#ifndef __BASE_GAME_H
#define __BASE_GAME_H


// Fichier d'entête pour les différents fichiers 

// #include "inventaire.h"


#include "entite.h"
#include "player.h"
#include "scores.h"
#include "enjeu.h"
#include "listeElements.h"

#include "inputs.h"
#include "entite.h"
#include "texture.h"
#include "menuPrincipal.h"
#include "constantes.h"
#include "level.h"
#include "chargeSave.h"

typedef struct baseGame 
{
    int state;
    bool estActif;

}Base_Game;

extern LinkedList listCollider;
extern LinkedList listEnnemies;
extern LinkedList bullet;

extern int tempsEcoule;
extern SDL_Rect camera;


/*######## GETTER & SETTER ######## */
extern Menu_t* getMenu(void);
extern Base_Game*  getBaseGame(void);
extern Scores* getScores(void);
extern SDL_Renderer* getRenderer(void);


/*####### FONCTION PRINCIPAL ############ */
extern void Init(const char *title);
extern void Update(float dt);
extern void Quitter_Jeux();
extern void Rendu_Jeux() ;

#endif