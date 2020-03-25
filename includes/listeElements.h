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
  #include "attributs.h"

  SDL_Rect *rect;
  bool actif;
  int nb_objets; /**< le nombres d'objets*/
  float baseX, baseY;/**< les bases selon le coeifficient x et y*/
  float phase;/**< float de la phase*/
  bool lancer;/**< float des lancer*/
  float movingX;/**<les deplacements selon x*/
  Texture_Manager imagesItem[2];
  int imageCourante;

  struct Node *suivant;
}Node;
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

extern Node* creerRect(SDL_Rect*rect, typeEntite item_t, bool actif );/**< creation du rectangle*/
extern void insertion(LinkedList * list, SDL_Rect *rect, typeEntite items_t , bool actif);

extern void deleteQueue(LinkedList *lstPtr);
extern void Afficher_ElementsListes(LinkedList *lst,SDL_Texture * tex, typeEntite typeE);/**< affiche les elements de la liste*/

extern void suppListe(LinkedList * lst);
extern bool suppPremier(LinkedList * lst);
extern bool suppDernier(LinkedList * lst);
extern Node * trouve (LinkedList *lsptr, int target, Node **prvPtr);
extern bool supprimeCible(LinkedList *lsptr, int target);/**<suppime la cible*/


#endif
