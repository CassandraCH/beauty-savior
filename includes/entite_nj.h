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


extern void init_List(LinkedList *list);

extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);
extern void collisionDetect();


extern Node* CreateRect(SDL_Rect*rect, typeItem item_t);

extern void insertQueue(LinkedList * list, SDL_Rect *rect, typeItem items_t);
extern void deleteQueue(LinkedList *lstPtr);

extern void RenderEntity(SDL_Texture * tex, LinkedList *lsptr);

extern void moveRectangle ( LinkedList * lst );
extern void clearRect (LinkedList *lst);

extern void deleteList(LinkedList * lst);
extern bool deleteFirst(LinkedList * lst);
extern bool deleteLast(LinkedList * lst);
extern Node * find (LinkedList *lsptr, int target, Node **prvPtr);
extern bool deleteTarget(LinkedList *lsptr, int target);


#endif