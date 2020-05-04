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
* \brief structure gerant les noeud de la liste
*/

typedef struct Node
{

  #include "attributs.h"
  

  SDL_Rect *rect;       /*!< Rectangle qui défini la taille d'un éléments>*/
  bool actif;           /*!< Défini si l'élement est actif ou non>*/

  int nb_objets;        /**< le nombres d'objets*/
  float baseX;          /**< Position de départ en X*/
  float baseY;          /**< Position de départ en Y*/
  float phase;          /**< float de la phase*/
  bool lancer;          /**< float des lancer*/
  float movingX;        /**<les deplacements selon x*/

  Texture_Manager imagesItem[2];  /**< Tableau de texture pour un element*/
  int imageCourante;              /**<Determine l'image actuellement visible a l'écran*/

  struct Node *next;           /**<Pointeur vers l'element suiv*/
}Node;
/**< This is the documentation for the preceding typedef */


/**
* \struct list
* \brief structure gerant les noeud de l'entete et a la fin.
*/
typedef struct list
{
  struct Node *head;          /**< noeud d'entete */
  struct Node *queue;         /**< noeud de fin */

  int nodeCount;            /**< compteur de noeuds */

}LinkedList;

/**< This is the documentation for the preceding typedef */

extern void List_Init(LinkedList *list);              /**< initialisation des listes */
extern void List_Update();                            /**< Mis à jour de la listes */

extern Node*  CreateElement(SDL_Rect*rect, typeEntite item_t, bool actif );                         /**< creation du rectangle*/
extern void   Insert_Element(LinkedList * list, SDL_Rect *rect, typeEntite items_t , bool actif);   /**< creation du rectangle*/

extern void   List_RenderElements(LinkedList *lst, SDL_Texture * tex, typeEntite typeE, int largeurTex, int hauteurTex);    /**< affiche les elements de la liste*/

extern void   Delete_List(LinkedList * lst);                        /**< Supprime la liste */
extern bool   Delete_First(LinkedList * lst);                       /**< Supprime le premier */
extern bool   Delete_Last(LinkedList * lst);                        /**< Supprime le dernier */
extern Node * Find (LinkedList *lsptr, int target, Node **prvPtr);  /**< trouve la cible */
extern bool   Delete_Target(LinkedList *lsptr, int target);         /**< suppime la cible */



#endif
