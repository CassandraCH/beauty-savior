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
#include "listeElements.h"
#include "chargeSave.h"
#include "texture.h"
#include "enjeu.h"
#include "entite.h"


#include "menuPrincipal.h"


typedef struct baseGame 
{
    int state;
    bool estActif;

}Base_Game;

/*######## GETTER & SETTER ######## */
extern Base_Game*  getBaseGame(void);
extern Menu_t* getMenu(void);
extern Scores* getScores(void);
extern SDL_Renderer* getRenderer(void);

extern LinkedList listEnnemies;
extern LinkedList listCollider;
extern LinkedList bullet;

extern int tempsEcoule;
extern SDL_Rect camera;



/*####### FONCTION PRINCIPAL ############ */
extern void Init(const char *title);
extern void Update(float dt);
extern void Quitter_Jeux();
extern void Rendu_Jeux() ;

#endif