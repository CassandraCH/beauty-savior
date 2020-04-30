/**
 * \file baseGame.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère les menus principal du jeu.
 */




#ifndef __BASE_GAME_H
#define __BASE_GAME_H /**< \def __BASE_GAME_H*/


// Fichier d'entête pour les différents fichiers

// #include "inventaire.h"
#include "constantes.h"



#include "entite.h"
#include "player.h"
#include "level.h"
#include "items.h"
#include "listeElements.h"
#include "chargeSave.h"
#include "texture.h"

#include "entite.h"
#include "hud.h"
#include "inventaire.h"
#include "menuPrincipal.h"
#include "menuLoad.h"
#include "menuPause.h"
#include "menu_continue.h"
#include "interface.h"

#include "gameOver.h"


/**
 *\struct baseGame
 *\details Structure principale de jeux, qui gère tous les composants du jeux majeurs.
 */
typedef struct baseGame
{
    int state; /**< Etat du jeu : en cours de partie, sur le menu principal */
    bool estActif; /**< Etat du jeu : Actif - Non Actif */
    int time;  /**< time : temps du jeux */

    int min; /**<  : temps liée au timer du jeux : minutes du jeux */
    
    int tempsPrecedent; /**<  temps précédent en référence au temps écoulé depuis la dernière image */
    int tempsActuel;  /**<  temps actuel en référence au temps écoulé depuis la dernière image */


}Base_Game; 
/**< This is the documentation for the preceding typedef */

/*######## GETTER & SETTER ######## */
extern SDL_Window* getWindow(void);/**< fonction SDL_Window qui gere la fenetre*/
extern Base_Game*  getBaseGame(void);/**< fonction Base_Game*/
extern LinkedList* getEnnemis(void);/**< fonction getEnnemis qui gere les ennemis*/
extern LinkedList* getCollider(void);/**< fonction getCollider*/
extern LinkedList* getItems(void);/**< fonction getItems*/
extern LinkedList* getBullets(void);/**< fonction getBullets*/

extern HUD* getScores(void);/**< fonction getScores qui gere le scores*/
extern HUD* getNiveau();/**< fonction getNiveau qui gere les niveaux*/
extern HUD* getTime();/**< fonction getNiveau qui gere le timer du jeux*/
extern HUD* getItem(int num_item) ;/**< fonction getItem*/
extern Menu_t* getMenu(void);/**< fonction getMenu*/
extern Menu_t* getInventaire(void);/**< fonction getInventaire*/
extern Menu_t* getInterface(void);/**< fonction getInterface*/
extern Menu_t * getMenuLoad(void);/**< fonction getMenuLoad*/
extern Menu_t * getMenuCon(void);/**< fonction getMenuCon*/
extern Menu_t * getMenuPause(void);/**< fonction getMenuPause*/
extern Menu_t * getMenu_Over(void);/**< fonction getMenu_Over*/

extern int getOs();/**< fonction getOs*/
extern int getRock( );/**< fonction getRock*/
extern int getBranche();/**< fonction getBranche*/

extern int getTimerBullet(void);/**< fonction getTimerBullet*/
extern void setTimerBullet(int time);/**< fonction setTimerBullet , avec la variable temps*/

extern void ProcessInput(SDL_Event* event);/**< fonction ProcessInput*/
extern void Input_InGame(SDL_Event *event);/**< fonction Input_InGame*/
extern void delay(unsigned int frameLimit);


/*######## LISTES ######## */
extern LinkedList listEnnemis;/**< la listes des ennemis*/
extern LinkedList listCollider;/**< liste des collition*/
extern LinkedList bullet;
extern LinkedList items;
extern void Update_Listes();


extern int tempsEcoule;/**< les temps ecouler*/
extern SDL_Rect camera;/**< la camera*/



/*####### FONCTION PRINCIPAL ############ */
extern void Init(const char *title);
extern void Update(float dt);
extern void LibererRessources_Jeux();
extern void Rendu_Jeux() ;

#endif
