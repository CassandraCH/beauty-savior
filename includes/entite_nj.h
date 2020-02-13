#ifndef _ENTITE_NJ_H
#define _ENTITE_NJ_H

#include "common.h"
#include "texture.h"

typedef struct Node
{
  bool touche;

  SDL_Rect *rect;
  typeItem type; //enum
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

// typedef struct inventaire
// {

//     void (*InitInventaire)(LinkedList *);
//     void (*DessinerItem) (SDL_Texture * , LinkedList * );
//     // Node* (*CreerItem)(SDL_Rect*);
//     Node* (*CreerItem)(SDL_Rect*, typeItem);
//     //, typeItem 

//     void (*InsererItem)(SDL_Rect *rect, typeItem );
//     void (*SupprimerItem)(LinkedList *lstPtr);
//     void (*DeplacementItem) ( LinkedList * lst );
//     void (*NettoyerItem )(LinkedList *lst);
//     bool (*SuppPremierItem)(LinkedList * lst);
//     bool (*SuppDernierItem)(LinkedList * lst);
//     Node* (*TrouverItem) (LinkedList *lsptr, int target, Node **prvPtr);
//     bool (*SupprimerItemCible)(LinkedList *lsptr, int target);

//     int (*NombreItems)(LinkedList* );

//     LinkedList listes;

// }Inventaire;



extern LinkedList* Listes();
extern void InitialiserInventaire();
extern void initList();

extern void collisionDetect();

extern void init_List(LinkedList *list);
extern void insertQueue(LinkedList * list, SDL_Rect *rect, typeItem items_t);

extern Node* CreateRect(SDL_Rect*rect, typeItem item_t);
extern void drawCollider(SDL_Texture * tex, LinkedList *lsptr, typeItem item_t);

extern void deleteQueue(LinkedList *lstPtr);
extern void moveRectangle ( LinkedList * lst );
extern void clearRect (LinkedList *lst);

extern void deleteList(LinkedList * lst);
extern bool deleteFirst(LinkedList * lst);
extern bool deleteLast(LinkedList * lst);
extern Node * find (LinkedList *lsptr, int target, Node **prvPtr);
extern bool deleteTarget(LinkedList *lsptr, int target);

extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);

#endif