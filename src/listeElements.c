/**
 * \file listeElements.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui permet de gérer les listes
 * \brief Création d'une liste, ajout de nouvel élément, suppression de la tête, suppresion de la queue, accès à une liste, affichage d'une liste'
 */
#include "baseGame.h"

/*#### DONNEES PRIVEES ####*/
LinkedList listEnnemis; /**< Liste des ennemis */
LinkedList bullet; /**< Liste des bullets */
LinkedList listCollider; /**< Liste des colliders */
LinkedList items; /**< Liste des items */

int timerBullets; /**< Temps d'apparition a l'ecran des bullets */

/**
 * \fn extern LinkedList* getEnnemis()
 * \brief Fonction qui permet d'acceder a la liste des ennemis
 * \return un pointeur sur une liste de type LinkedList
*/
extern LinkedList* getEnnemis()
{
   return &listEnnemis;
}

/**
 * \fn extern LinkedList* getCollider()
 * \brief Fonction qui permet d'acceder a la liste des colliders
 * \return un pointeur sur une liste de type LinkedList
*/
extern LinkedList* getCollider()
{
   return &listCollider;
}

/**
 * \fn extern LinkedList* getBullets()
 * \brief Fonction qui permet d'acceder a la liste des bullets
 * \return un pointeur sur une liste de type LinkedList
*/
extern LinkedList* getBullets()
{
   return &bullet;
}

/**
 * \fn extern LinkedList* getItems()
 * \brief Fonction qui permet d'acceder a la liste des items
 * \return un pointeur sur une liste de type LinkedList
*/
extern LinkedList* getItems()
{
   return &items;
}

/**
 * \fn extern LinkedList* getBullets()
 * \brief Fonction qui permet d'acceder a la duree de vie/temps d'apparition a l'ecran des bullets
 * \return un pointeur sur une liste de type LinkedList
*/
extern int getTimerBullet()
{
    return timerBullets;   
}

/**
 * \fn extern LinkedList* getBullets()
 * \brief Fonction qui permet d'acceder a la duree de vie/temps d'apparition a l'ecran des bullets
 * \return pas de valeur de retour (void)
*/
extern void setTimerBullet(int time)
{
    timerBullets = time;
}

/**
 * \fn extern void init_List(LinkedList *list)
 * \brief Fonction qui permet d'initialiser la liste passee en parametre
 * \param list liste a initialiser
 * \return pas de valeur de retour (void)
*/
extern void init_List(LinkedList *list)
{
  list->tete = NULL;
  list->queue = NULL;
  list->nodeCount = 0;
}

/**
 * \fn extern Node* creerRect(SDL_Rect*rect, typeEntite item_t, bool actif ) 
 * \brief Fonction qui permet de créer 
 * \param rect
 * \param item_t
 * \param actif
 * \return Pointeur sur une structure de type Node
*/
extern Node* creerRect(SDL_Rect*rect, typeEntite item_t, bool actif ) 
{   
    
    Node * nouvelElement = malloc( sizeof( Node ) );
    nouvelElement->suivant = NULL; 

    memset(nouvelElement, 0, sizeof(Node));
    nouvelElement->rect = rect;
    nouvelElement->type = item_t;
    nouvelElement->nb_objets = 0;
    nouvelElement->movingX = 0;
    nouvelElement->lancer = true;
   
    nouvelElement->x = rect->x;
    nouvelElement->y = rect->y;
    nouvelElement->w = rect->w;
    nouvelElement->h = rect->h;
    nouvelElement->actif = actif;

    if( item_t == ennemi ) 
    {
        nouvelElement->baseX = rect->x;
        nouvelElement->baseY = rect->y;

        if( actif == true )
         {
            nouvelElement->phase = 2*3.14*(rand() % 360) / 360.0f;
            nouvelElement->vx = -1.8f;
         }
		nouvelElement->vy = 0;
    }

    return ( nouvelElement );
}


extern void insertion(LinkedList * list, SDL_Rect *rect, typeEntite items_t, bool actif)
{
    printf("Insertion objet\n");
  Node *nouvelElement = creerRect(rect, items_t, actif);

  if (list->nodeCount == 0){
    // Cas lorsque la liste est vide
    list->tete = nouvelElement;
    list->queue = nouvelElement;
  }
  else{
    // Cas lorsque la liste n'est pas vide
    list->queue->suivant = nouvelElement;
    list->queue = nouvelElement;
  }

  list->nodeCount++;

  return;
   
}


extern void suppListe(LinkedList * lst)
{
    if( lst->nodeCount > 0 ) 
    {
        Node * temp;
        Node * current = lst->tete;
        while( current != NULL)
        {
            temp = current;
            current = current->suivant;
            free(temp);
            lst->nodeCount--;
        }
    }
    printf("TOUS LES NŒUDS DE LA LISTE ONT ETAIENT DETRUIT\n");
}

extern void deleteQueue(LinkedList *lstPtr){

  if( lstPtr != NULL )
  {
        if( lstPtr->nodeCount  > 0 )
        {
            Node *first = lstPtr->tete;
            
            if (lstPtr->nodeCount == 1){
                // Cas si il n'y a qu'un élément 
                lstPtr->tete = NULL;
                lstPtr->queue = NULL;

            }
            else{
                //Si il y a plusieurs élements il faut supprimer le premier
                lstPtr->tete = first->suivant;
            }
            
            free(first->rect);
            free(first);
            lstPtr->nodeCount --;
        }
  }
}



extern bool suppPremier(LinkedList * lst)
{
    
    if( lst->nodeCount == 0 ){
        return false;
    }

    Node * first = lst->tete;

    if (lst->nodeCount == 1)
    {
        lst->tete = NULL; 
        lst->queue = NULL;
    }
    else 
    {
        lst->tete = first->suivant;
    }
    free(first);
    lst->nodeCount--;
    printf("Nombre element: %d\n", lst->nodeCount);
    return true;
}


extern bool suppDernier(LinkedList * lst)
{
    if( lst->nodeCount == 0 ){
        return false;
    }

    Node * current = lst->tete;
    Node * last = lst->queue;

    if (lst->nodeCount == 1)
    {
        lst->tete = NULL; 
        lst->queue = NULL;
    }
    else 
    {
        while( current->suivant != lst->queue )
            current = current->suivant;

        lst->queue= current;
        lst->queue->suivant = NULL;

    }
    free(last);
    lst->nodeCount--;
    printf("Nombre element: %d\n", lst->nodeCount);
    return true;
}


extern Node * trouve (LinkedList *lsptr, int target, Node **prvPtr)
{
    Node * current = lsptr->tete;
    *prvPtr = NULL;
    
    while( current != NULL )
    {
        if ( current->estMort == target )
        {
            break;
        }
        *prvPtr = current;
        current = current->suivant;
    }
    return current;
}


extern bool supprimeCible(LinkedList *lsptr, int target)
{   
    Node * current = NULL, *prev = NULL;
    current = trouve(lsptr,target, &prev);
    
    if( current == NULL ){
        return false;
    }

    if( current == lsptr->tete )
    {
       return suppPremier(lsptr);
    }
    
    else if( current == lsptr->queue )
    {
       return suppDernier(lsptr);
    }
    else 
    {
        prev->suivant = current->suivant;
        free(current);
        lsptr->nodeCount--;

        printf("Nombre element: %d\n", lsptr->nodeCount);
        return true; 
    }
    
}



extern void Afficher_ElementsListes(LinkedList *lst,SDL_Texture * tex, typeEntite typeE)
{
    Node *pt;
    if( lst->nodeCount  > 0 )
    {
        for( pt = lst->tete; pt!= NULL; pt= pt->suivant )
        {
           if ( pt->estMort != true && pt->type == typeE )
           {
            SDL_Rect rect = {  pt->rect->x- camera.x ,pt->rect->y-  camera.y ,pt->rect->w,pt->rect->h };
            SDL_RenderCopy( getRenderer() , tex , NULL, &rect );
           }
        }
    }
        
}
