#ifndef _ENTITE_NJ_H
#define _ENTITE_NJ_H

#include "commun.h"
#include "texture.h"


typedef struct Node
{
  #include "attributs.h"

  SDL_Rect *rect;
  bool actif;
  int nb_objets;
  float baseX, baseY;
  float phase;
  bool lancer;
  float movingX;
  Texture_Manager imagesItem[2];
  int imageCourante; 

  struct Node *suivant;
}Node;


typedef struct 
{
  struct Node *tete;
  struct Node *queue;

  int nodeCount;

}LinkedList;


extern void init_List(LinkedList *list);

extern Node* creerRect(SDL_Rect*rect, typeEntite item_t, bool actif );
extern void insertion(LinkedList * list, SDL_Rect *rect, typeEntite items_t , bool actif);

extern void deleteQueue(LinkedList *lstPtr);
extern void Afficher_ElementsListes(LinkedList *lst,SDL_Texture * tex, typeEntite typeE);

extern void suppListe(LinkedList * lst);
extern bool suppPremier(LinkedList * lst);
extern bool suppDernier(LinkedList * lst);
extern Node * trouve (LinkedList *lsptr, int target, Node **prvPtr);
extern bool supprimeCible(LinkedList *lsptr, int target);


#endif