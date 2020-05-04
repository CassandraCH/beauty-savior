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
 *\struct Player
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

extern Player *getPlayer(void);          /**< accès à la structure du joueur */
extern int getPlayerX(void);             /**< accès à la position en x du joueur */
extern int getPlayerY(void);             /**< accès à la position en y du joueur */

extern int      getPlayerOriginX();     /**< la position'l'origine) du joueur selon x*/
extern int      getPlayerOriginY();     /**< la position'l'origine) du joueur selon y*/

<<<<<<< HEAD
extern void     Player_Update();
extern void     Player_Reset( void );
=======
extern void Player_Update();            /**< mise à joueur du joueur */
extern void Player_Reset(void);         /**< réinitialisation du joueur */
>>>>>>> d83bc28279cd640e177026ac11cd68885153c735

extern void     Player_Init();           /**<initialisation du joueur*/
extern void Player_SetBullets();         /**<réglage du nombre de bullets*/
extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2); /**< vérification de la collision entre 2 éléments */
extern void     Player_Attack();        /**<les attaques du joueurs*/
extern void     Shoot_Collision();        /**<collission des tirs du joueur*/
extern void     CollisionItems();

extern void Player_Input(SDL_Event *event); /**< gestion des entrées utilisateur */
extern void Player_Render();                /**<affichage du joueur */

#endif
