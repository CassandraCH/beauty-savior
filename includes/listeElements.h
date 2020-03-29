/**
 * \file listeElements.h
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief programme qui gere tous les elements met en place pour le jeu .
 */




#ifndef _ENTITE_NJ_H
#define _ENTITE_NJ_H/**< \def _ENTITE_NJ_H*/

#include "commun.h"
#include "texture.h"
/**
* \struct Node
* \details structure gerant les noeud de la liste
*/

typedef struct Node
{

    float w; /** <largeur de l'entite*/
    float h; /** < hauteur de l'entite*/
    float x; /** <la position x */
    float y;  /** <la position y */
    float vx; /** <la velocite x la vitesse laquelle va l'entite dans une direction x*/
    float vy; /** <la velocite y , la vitesse laquelle va l'entite dans une direction y*/
    typeEntite type; /** <le type de l'entite*/

  bool estMort; /** <un type booleen pour savoir c'est l'entite est mort>*/
  int nb_lancer; /** <un compteur pour savoir le nb de lancer, attaque en cours>*/

  SDL_Rect *rect; /** <Rectangle qui défini la taille d'un éléments>*/
  bool actif; /** <Défini si l'élement est actif ou non>*/

  int nb_objets; /**< le nombres d'objets*/
  float baseX;/**< Position de départ en X*/
  float baseY;/**< Position de départ en Y*/
  float phase;/**< float de la phase*/
  bool lancer;/**< float des lancer*/
  float movingX;/**<les deplacements selon x*/

  Texture_Manager imagesItem[2];  /**< Tableau de texture pour un element*/
  int imageCourante; /**<Determine l'image actuellement visible a l'écran*/

  struct Node *suivant; /**<Pointeur vers l'element suivant*/
}Node;
/**< This is the documentation for the preceding typedef */


/**
* \struct
* \details structure gerant les noeud de l'entete et a la fin.
*/
typedef struct
{
  struct Node *tete; /**<noeud d'entete*/
  struct Node *queue;/**< noeud de fin*/

  int nodeCount;/**<compteur de noeuds*/

}LinkedList;


extern void init_List(LinkedList *list);/**< initialisation des listes*/

extern Node* creerElement(SDL_Rect*rect, typeEntite item_t, bool actif ); /**< creation du rectangle*/
extern void insertion(LinkedList * list, SDL_Rect *rect, typeEntite items_t , bool actif); /**< creation du rectangle*/

extern void Afficher_ElementsListes(LinkedList *lst,SDL_Texture * tex, typeEntite typeE);/**< affiche les elements de la liste*/

extern void suppListe(LinkedList * lst);
extern bool suppPremier(LinkedList * lst);
extern bool suppDernier(LinkedList * lst);
extern Node * trouve (LinkedList *lsptr, int target, Node **prvPtr);
extern bool supprimeCible(LinkedList *lsptr, int target);/**<suppime la cible*/


#endif
