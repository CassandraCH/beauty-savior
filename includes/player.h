/**
 * \file player.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere le joueur par exemple la vitesse de deplacements,sa position etc.
 */


#ifndef _PLAYER_H
#define _PLAYER_H/**< \def _PLAYER_H*/

#include "texture.h"
#include "constantes.h"

/**
 *\struct player
 *\details Structure gérant les caractéristiques liées au joueur
 */

typedef struct player
{
    
    #include "attributs.h"
  
    float posXDepart;       /**<sa positon de depart selon x*/
    float posYDepart;       /**<sa positon de depart selon y*/
 
    bool osActif;           /**< booleen pour vérifier l'os est l'élement actif */
    bool treeActif;         /**< booleen pour vérifier le tree est l'élement actif */
    bool rockActif;         /**< booleen pour vérifier le rock est l'élement actif */

    bool estTourne;         /**<le booleen est tourne*/

    bool estSurSol;         /**<le booleen est sur le sol*/
    int scores;             /**<score du joueur*/

    int nombreVies;         /**< le nombre de vie du joueur*/
    bool ralenti;           /**<le ralentisement du joueur*/

    int niveau;             /**< le niveau du joueur */

    int nb_objet;           /**< nombres d'objets qui a le joueur*/

    Texture_Manager tex;    /**< Texture du joueur */

    bool isPasspordCollected; /**< booleen pour connaître la collecte ou du passpord dans un niveau */


}Player;
/**< This is the documentation for the preceding typedef */


extern Player * getPlayer(void);
extern int      getPlayerX(void);
extern int      getPlayerY(void);

extern int      getPlayerOriginX();     /**< la position'l'origine) du joueur selon x*/
extern int      getPlayerOriginY();     /**< la position'l'origine) du joueur selon y*/

extern void     Player_Update();
extern void     Player_Reset( void );

extern void     Player_Init();           /**<initialisation du joueur*/
extern void     Player_SetBullets();
extern bool     collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);
extern void     Player_Attack();        /**<les attaques du joueurs*/
extern void     Shoot_Collision();        /**<collission des tirs du joueur*/
extern void     CollisionItems();

extern void     Player_Input(SDL_Event *event);
extern void     Player_Render();


#endif
