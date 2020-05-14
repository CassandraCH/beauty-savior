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
LinkedList listEnnemis; 
LinkedList bullet; 
LinkedList listCollider;
LinkedList items; 

int timerBullets; /**< Temps d'apparition a l'ecran des bullets */

/**
 * \fn extern LinkedList* getEnnemis()
 * \brief Fonction qui permet d'acceder à la liste des ennemis
 * \return un pointeur sur une liste de type LinkedList
*/
extern LinkedList* getEnnemis()
{
   return &listEnnemis;
}

/**
 * \fn extern LinkedList* getCollider()
 * \brief Fonction qui permet d'acceder à la liste des colliders
 * \return un pointeur sur une liste de type LinkedList
*/
extern LinkedList* getCollider()
{
   return &listCollider;
}

/**
 * \fn extern LinkedList* getBullets()
 * \brief Fonction qui permet d'acceder à la liste des bullets
 * \return un pointeur sur une liste de type LinkedList
*/
extern LinkedList* getBullets()
{
   return &bullet;
}

/**
 * \fn extern LinkedList* getItems()
 * \brief Fonction qui permet d'acceder à la liste des items
 * \return un pointeur sur une liste de type LinkedList
*/
extern LinkedList* getItems()
{
   return &items;
}

/**
 * \fn extern int getTimerBullet()
 * \brief Fonction qui permet d'acceder à la durée de vie/temps d'apparition à l'écran des bullets
 * \return un pointeur sur une liste de type LinkedList
*/
extern int getTimerBullet()
{
    return timerBullets;   
}

/**
 * \fn extern void setTimerBullet(int time)
 * \brief Fonction qui permet configuer le timer des bullets
 * \param time durée de vie des bullets
 * \return pas de valeur de retour (void)
*/
extern void setTimerBullet(int time)
{
    timerBullets = time;
}

/**
 * \fn extern void List_Init(LinkedList *list)
 * \brief Fonction qui permet d'initialiser la liste passée en paramètre
 * \param list liste a initialiser
 * \return pas de valeur de retour (void)
*/
extern void List_Init(LinkedList *list)
{
  list->head = NULL;
  list->queue = NULL;
  list->nodeCount = 0;
}

/**
 * \fn extern Node* CreateElement(SDL_Rect_rect, typeEntite item_t, bool actif ) 
 * \brief Fonction qui permet de créer un rectangle (portion de l'ecran)
 * \brief Ce rectangle sera utilisé pour la texture
 * \param _rect rectangle SDL
 * \param item_t type de l'entité
 * \param actif etat de l'entité
 * \return Pointeur sur une structure de type Node
*/
extern Node* CreateElement(SDL_Rect _rect, typeEntite item_t, bool actif ) 
{   
    Node * nouvelElement = calloc(1, sizeof( Node ) );
    nouvelElement->next = NULL; 

    //Remplir la zone mémoire avec des 0
    memset(nouvelElement, 0, sizeof(Node));

    nouvelElement->_rect = _rect;
    nouvelElement->type = item_t;

    /* ### CARACTERISTIQUE LIEE AU TIR ### */
    nouvelElement->movingX = 0; //Sens du tir de l'ennemi
    nouvelElement->lancer = true; //Etat du tir

    nouvelElement->x = _rect.x; //posiiton en x
    nouvelElement->y = _rect.y; //posiiton en y
    nouvelElement->w = _rect.w; //largeur
    nouvelElement->h = _rect.h; //hauteur
    nouvelElement->actif = actif; 

    //Cas si c'est un ennemi
    if( item_t == ennemi ) 
    {  
        //Sauvegarde de la position initiale en x et en y
        nouvelElement->baseX = _rect.x;
        nouvelElement->baseY = _rect.y;

        //S'il n'est pas mort
        if( actif == true )
        {
            //Permet de générer aléatoirement une vitesse de déplacement
            nouvelElement->phase = 2 * 3.14 * (rand() % 360) / 360.0f;

            //Vélocité = vitesse à laquelle il se déplace
            nouvelElement->vx = -1.8f;
        }
        //Gravite 
		nouvelElement->vy = 0;
    }

    return ( nouvelElement );
}

/**
 * \fn extern void Insert_Element(LinkedList * list, SDL_Rect _rect, typeEntite items_t, bool actif)
 * \brief Fonction qui permet d'insérer un élément dans une liste passée en paramètre
 * \param list pointeur sur la liste dans laquelle on veut insérer un élement
 * \param _rect pointeur sur l'élement a ajouter
 * \param items_t type de l'élement à ajouter : ennemi, bullet, collider...
 * \param actif état de l'élement
 * \return pas de valeur de retour (void)
*/
extern void Insert_Element(LinkedList * list, SDL_Rect _rect, typeEntite items_t, bool actif)
{
    printf("Insert_Element objet\n");
    Node *nouvelElement = CreateElement(_rect, items_t, actif);

    //Cas lorsque la liste est vide
    if (list->nodeCount == 0)
    {
        list->head = nouvelElement;
        list->queue = nouvelElement;
    }

    //Cas lorsque la liste n'est pas vide
    else
    {
        list->queue->next = nouvelElement;
        list->queue = nouvelElement;
    }

    //Mise a jour du compteur
    list->nodeCount++;
    return; 
}

/**
 * \fn extern void Delete_List(LinkedList * lst)
 * \brief Fonction qui permet de supprimer la liste passée en paramètre
 * \param lst pointeur sur la liste dans laquelle on veut insérer un élement
 * \return pas de valeur de retour (void)
*/
extern void Delete_List(LinkedList * lst)
{
    //Si la liste n'est pas vide
    if( lst->nodeCount > 0 && lst->head != NULL) 
    {
        Node *temp;                //élement tampon
        Node *current = lst->head; //élement courant

        //Tant qu'il y a encore des élements dans la liste
        while( current != NULL)
        {
            temp = current;
            current = current->next;
            free(temp);
            lst->nodeCount--;
        }
        printf("TOUS LES NŒUDS DE LA LISTE ONT ETAIENT DETRUIT\n");
    }
    
}

/**
 * \fn extern bool Delete_First(LinkedList * lst)
 * \brief Fonction qui permet de supprimer la head de la liste passée en paramètre
 * \param lst pointeur sur la liste dans laquelle on veut insérer un élement
 * \return un booleen si l'élement a bien été supprimé ou non
*/
extern bool Delete_First(LinkedList * lst)
{
    //Verifie que la liste n'est pas vide
    if( lst->nodeCount == 0 )
    {
        return false;
    }

    Node *first = lst->head; //pointeur sur le premier élement de la liste

    //S'i 'il n'y a qu'un élement
    if (lst->nodeCount == 1)
    {
        lst->head = NULL; 
        lst->queue = NULL;
    }

    //S'il y a plus d'un élement dans la liste
    else 
    {
        lst->head = first->next;
    }

    
    free(first);

    //Mise a jour du compteur d'élements
    lst->nodeCount--;

    printf("Nombre élément: %d\n", lst->nodeCount);
    return true;
}

/**
 * \fn extern bool Delete_Last(LinkedList * lst)
 * \brief Fonction qui permet de supprimer la queue de la liste liste passée en paramètre
 * \param lst pointeur sur la liste dans laquelle on veut inserer un élement
 * \return un booleen si l'élement a bien été supprimé ou non
*/
extern bool Delete_Last(LinkedList * lst)
{
    //Verifie que la liste n'est pas vide
    if( lst->nodeCount == 0 )
    {
        return false;
    }

    Node *current = lst->head;  //pointeur sur le premier élement de la liste
    Node *last = lst->queue;    //pointeur sur le dernier élement de la liste

    //S'il n'y a qu'un élement
    if (lst->nodeCount == 1)
    {
        lst->head = NULL; 
        lst->queue = NULL;
    }

    //S'i 'il y a plus d'un élement dans la liste
    else 
    {
        while( current->next != lst->queue )
            current = current->next;

        lst->queue= current;
        lst->queue->next = NULL;

    }

  
    free(last);

    //Mise a jour du compteur d'élements
    lst->nodeCount--;

    printf("Nombre element: %d\n", lst->nodeCount);
    return true;
}

/**
 * \fn extern Node * Find(LinkedList *lsptr, int target, Node **prvPtr)
 * \brief Fonction qui permet de chercher un élement dans une liste
 * \param lsptr pointeur sur la liste dans laquelle on cherche un élement
 * \param target élement cible qui est cherché
 * \param prvPtr pointeur sur l'élément précédent
 * \return Pointeur sur une structure de type Node
*/
extern Node * Find(LinkedList *lsptr, int target, Node **prvPtr)
{
    Node *current = lsptr->head; //élement courant
    *prvPtr = NULL;              //pointeur sur l'élement precedent

    //tant qu'on n'a pas parcouru toute la liste ou que l'élément cible n'a pas ete Find
    while( current != NULL )
    {
        //Si l'élément actuel est mort
        if ( current->estMort == target )
        {
            break;
        }

        //l'élément courrant devient l'élément precedent
        *prvPtr = current;

        //l'élément actuel devient l'élément next
        current = current->next;
    }
    return current;
}

/**
 * \fn extern bool Delete_Target(LinkedList *lsptr, int target)
 * \brief Fonction qui permet de supprimer un élément cible dans une liste
 * \param lsptr pointeur sur la liste dans laquelle on veut supprimer un élément
 * \param target élément cible qu'on veut supprimer
 * \return un booleen si l'élément cible a bien été supprimé ou non
*/
extern bool Delete_Target(LinkedList *lsptr, int target)
{   
    Node * current = NULL, *prev = NULL;
    current = Find(lsptr,target, &prev);
    
    //Si la liste est vide
    if( current == NULL ){
        return false;
    }

    //Si l'élément a supprimer est le premier élément de la liste
    if( current == lsptr->head )
    {
       return Delete_First(lsptr);
    }

    //Si l'élément a supprimer est le dernier élément de la liste
    else if( current == lsptr->queue )
    {
       return Delete_Last(lsptr);
    }

    //Sinon
    else 
    {
        prev->next = current->next;
        free(current);
        lsptr->nodeCount--;

        printf("Nombre element: %d\n", lsptr->nodeCount);
        return true; 
    }
}

/**
 * \fn extern void List_RenderElements(LinkedList *lst,SDL_Texture * tex, typeEntite typeE)
 * \brief Fonction qui permet d'afficher les éléments d'une liste
 * \param lst liste dont on veut afficher les éléments
 * \param tex texture 
 * \param typeE type des éléments a afficher
 * \return pas de valeur de retour (void)
*/
extern void List_RenderElements(LinkedList *lst, SDL_Texture * tex, typeEntite typeE, int largeurTex, int hauteurTex)
{
    Node *pt;

    //S'il y a au moins un élément dans la liste
    if( lst->nodeCount  > 0 )
    {
        //Parcours de la liste
        for( pt = lst->head; pt!= NULL; pt= pt->next )
        {
            //Si l'élément n'est pas mort
            if ( pt->estMort != true && pt->type == typeE )
            {
                pt->_rect.w = largeurTex;
                pt->_rect.h = hauteurTex;

                SDL_Rect _rect = { pt->_rect.x- camera.x, pt->_rect.y -  camera.y, pt->_rect.w, pt->_rect.h };
                SDL_RenderCopy( getRenderer() , tex , NULL, &_rect );
            }
        }
    }
}