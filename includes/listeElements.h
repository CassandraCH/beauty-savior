#ifndef _ENTITE_NJ_H
#define _ENTITE_NJ_H

#include "commun.h"
#include "texture.h"

typedef struct Node
{
  #include "attributs.h"

  SDL_Rect *rect;

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

extern void collisionDetect();

extern Node* creerRect(SDL_Rect*rect, typeEntite item_t, bool isLeft);
extern void insertion(LinkedList * list, SDL_Rect *rect, typeEntite items_t, bool isLeft);
extern void deleteQueue(LinkedList *lstPtr);
extern void RenderElements(LinkedList *lst,SDL_Texture * tex, typeEntite typeE);

extern void moveRectangle ( LinkedList * lst );
extern void clearRect (LinkedList *lst);

extern void deleteList(LinkedList * lst);
extern bool deleteFirst(LinkedList * lst);
extern bool deleteLast(LinkedList * lst);
extern Node * find (LinkedList *lsptr, int target, Node **prvPtr);
extern bool deleteTarget(LinkedList *lsptr, int target);


#endif