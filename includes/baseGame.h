#ifndef __BASE_GAME_H
#define __BASE_GAME_H

#include "constantes.h"

// #include "Inputs.h"
// #include "player.h"
// #include "level.h"
// #include "inventaire.h"
// #include "scores.h"
// #include "load_save.h"
// #include "texture.h"
// #include "ingame.h"


#include "menuPrincipal.h"



typedef struct baseGame 
{
    int state;
    bool estActif;

}Base_Game;


extern LinkedList listEnnemies;
extern LinkedList bullet;

extern int last_frame_time;
extern SDL_Rect camera;


// Gette & Setter  
extern Menu_t* getMenu(void);
extern Base_Game*  getBaseGame(void);
extern NonJoueur* getPNJ(void);
extern Input_t* getInput(void);
extern Score_t* getScores(void);
extern SDL_Renderer* getRenderer(void);


extern void Init(const char *title);
extern void Update(float dt);
extern void delay(unsigned int frameLimit);
extern void Quitter_Jeux();

extern void Rendu_Jeux() ;

#endif