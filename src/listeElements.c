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
 * \fn extern int getTimerBullet()
 * \brief Fonction qui permet d'acceder a la duree de vie/temps d'apparition a l'ecran des bullets
 * \return un pointeur sur une liste de type LinkedList
*/
extern int getTimerBullet()
{
    return timerBullets;   
}

/**
 * \fn extern void setTimerBullet(int time)
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
 * \fn extern Node* creerElement(SDL_Rect*rect, typeEntite item_t, bool actif ) 
 * \brief Fonction qui permet de créer un rectangle (portion de l'ecran)
 * \details Ce rectangle sera utilise pour la texture
 * \param rect rectangle SDL
 * \param item_t type de l'entite
 * \param actif etat de l'entite
 * \return Pointeur sur une structure de type Node
*/
extern Node* creerElement(SDL_Rect*rect, typeEntite item_t, bool actif ) 
{   
    Node * nouvelElement = malloc( sizeof( Node ) );
    nouvelElement->suivant = NULL; 

    //Remplir la zone memoire avec des 0
    memset(nouvelElement, 0, sizeof(Node));

    nouvelElement->rect = rect;
    nouvelElement->type = item_t;

    /* ### CARACTERISTIQUE LIEE AU TIR ### */
    nouvelElement->movingX = 0; //Sens du tir de l'ennemi
    nouvelElement->lancer = true; //Etat du tir

    nouvelElement->x = rect->x;
    nouvelElement->y = rect->y;
    nouvelElement->w = rect->w;
    nouvelElement->h = rect->h;
    nouvelElement->actif = actif;

    //Cas si c'est un ennemi
    if( item_t == ennemi ) 
    {  
        //Sauvegarde de la position initialie en x et en y
        nouvelElement->baseX = rect->x;
        nouvelElement->baseY = rect->y;

        //Si il n'est pas mort
        if( actif == true )
        {
            //Permet de générer aléatoirement une vitesse de déplacement
            nouvelElement->phase = 2 * 3.14 * (rand() % 360) / 360.0f;

            //Velocite = vitesse a laquelle il se deplace
            nouvelElement->vx = -1.8f;
        }
        //Gravite 
		nouvelElement->vy = 0;
    }

    return ( nouvelElement );
}

/**
 * \fn extern void insertion(LinkedList * list, SDL_Rect *rect, typeEntite items_t, bool actif)
 * \brief Fonction qui permet d'inserer un element dans une liste passee en parametre
 * \details 
 * \param list pointeur sur la liste dans laquelle on veut inserer un element
 * \param rect pointeur sur l'element a ajouter
 * \param items_t type de l'element a ajouter : ennemi, bullet, collider...
 * \param actif etat de l'element
 * \return pas de valeur de retour (void)
*/
extern void insertion(LinkedList * list, SDL_Rect *rect, typeEntite items_t, bool actif)
{
    printf("Insertion objet\n");
    Node *nouvelElement = creerElement(rect, items_t, actif);

    //Cas lorsque la liste est vide
    if (list->nodeCount == 0)
    {
        list->tete = nouvelElement;
        list->queue = nouvelElement;
    }

    //Cas lorsque la liste n'est pas vide
    else
    {
        list->queue->suivant = nouvelElement;
        list->queue = nouvelElement;
    }

    //Mise a jour du compteur
    list->nodeCount++;
    return; 
}

/**
 * \fn extern void suppListe(LinkedList * lst)
 * \brief Fonction qui permet de supprimer la liste passee en parametre
 * \details 
 * \param lst pointeur sur la liste dans laquelle on veut inserer un element
 * \return pas de valeur de retour (void)
*/
extern void suppListe(LinkedList * lst)
{
    //Si la liste n'est pas vide
    if( lst->nodeCount > 0 && lst->tete != NULL) 
    {
        Node * temp; //element tampon
        Node * current = lst->tete; //element courant

        //Tant qu'il y a encore des elements dans la liste
        while( current != NULL)
        {
            temp = current;
            current = current->suivant;
            free(temp);
            lst->nodeCount--;
        }
        printf("TOUS LES NŒUDS DE LA LISTE ONT ETAIENT DETRUIT\n");
    }
    
}

/**
 * \fn extern bool suppPremier(LinkedList * lst)
 * \brief Fonction qui permet de supprimer la tete de la liste passee en parametre
 * \details 
 * \param lst pointeur sur la liste dans laquelle on veut inserer un element
 * \return un booleen si l'element a bien ete supprime ou non
*/
extern bool suppPremier(LinkedList * lst)
{
    //Verifie que la liste n'est pas vide
    if( lst->nodeCount == 0 )
    {
        return false;
    }

    Node * first = lst->tete; //pointeur sur le premier element de la liste

    //Si il n'y a qu'un element
    if (lst->nodeCount == 1)
    {
        lst->tete = NULL; 
        lst->queue = NULL;
    }

    //Si il y a plus d'un element dans la liste
    else 
    {
        lst->tete = first->suivant;
    }

    free(first->rect);
    free(first);

    //Mise a jour du compteur d'element
    lst->nodeCount--;

    printf("Nombre element: %d\n", lst->nodeCount);
    return true;
}

/**
 * \fn extern bool suppDernier(LinkedList * lst)
 * \brief Fonction qui permet de supprimer la queue de la liste passee en parametre
 * \details 
 * \param lst pointeur sur la liste dans laquelle on veut inserer un element
 * \return un booleen si l'element a bien ete supprime ou non
*/
extern bool suppDernier(LinkedList * lst)
{
    //Verifie que la liste n'est pas vide
    if( lst->nodeCount == 0 )
    {
        return false;
    }

    Node * current = lst->tete; //pointeur sur le premier element de la liste
    Node * last = lst->queue; //pointeur sur le dernier element de la liste

    //Si il n'y a qu'un element
    if (lst->nodeCount == 1)
    {
        lst->tete = NULL; 
        lst->queue = NULL;
    }

    //Si il y a plus d'un element dans la liste
    else 
    {
        while( current->suivant != lst->queue )
            current = current->suivant;

        lst->queue= current;
        lst->queue->suivant = NULL;

    }

    free(last->rect);
    free(last);

    //Mise a jour du compteur d'element
    lst->nodeCount--;

    printf("Nombre element: %d\n", lst->nodeCount);
    return true;
}

/**
 * \fn extern Node * trouve(LinkedList *lsptr, int target, Node **prvPtr)
 * \brief Fonction qui permet de chercher un element dans une liste
 * \details 
 * \param lsptr pointeur sur la liste dans laquelle on cherche un element
 * \param target element cible qui est cherche
 * \param prvPtr pointeur sur l'element precedent
 * \return Pointeur sur une structure de type Node
*/
extern Node * trouve(LinkedList *lsptr, int target, Node **prvPtr)
{
    Node * current = lsptr->tete; //element courant
    *prvPtr = NULL; //pointeur sur l'element precedent
    
    //tant qu'on n'a pas parcouru toute la liste ou que l'element cible n'a pas ete trouve
    while( current != NULL )
    {
        //Si l'element actuel est mort
        if ( current->estMort == target )
        {
            break;
        }

        //l'element courrant devient l'element precedent
        *prvPtr = current;

        //l'element actuel devient l'element suivant
        current = current->suivant;
    }
    return current;
}

/**
 * \fn extern bool supprimeCible(LinkedList *lsptr, int target)
 * \brief Fonction qui permet de supprimer un element cible dans une liste
 * \details 
 * \param lsptr pointeur sur la liste dans laquelle on veut supprimer un element
 * \param target element cible qu'on veut supprimer
 * \return un booleen si l'element cible a bien ete supprime ou non
*/
extern bool supprimeCible(LinkedList *lsptr, int target)
{   
    Node * current = NULL, *prev = NULL;
    current = trouve(lsptr,target, &prev);
    
    //Si la liste est vide
    if( current == NULL ){
        return false;
    }

    //Si l'element a supprime est le premier element de la liste
    if( current == lsptr->tete )
    {
       return suppPremier(lsptr);
    }

    //Si l'element a supprime est le dernier element de la liste
    else if( current == lsptr->queue )
    {
       return suppDernier(lsptr);
    }

    //Sinon
    else 
    {
        prev->suivant = current->suivant;
        free(current);
        lsptr->nodeCount--;

        printf("Nombre element: %d\n", lsptr->nodeCount);
        return true; 
    }
}

/**
 * \fn extern void Afficher_ElementsListes(LinkedList *lst,SDL_Texture * tex, typeEntite typeE)
 * \brief Fonction qui permet d'afficher les elements d'une liste
 * \details 
 * \param lst liste dont on veut afficher les elements
 * \param tex texture 
 * \param typeE type des elements a afficher
 * \return pas de valeur de retour (void)
*/
extern void Afficher_ElementsListes(LinkedList *lst, SDL_Texture * tex, typeEntite typeE, int largeurTex, int hauteurTex)
{
    Node *pt;

    //Si il y a au moins un element dans la liste
    if( lst->nodeCount  > 0 )
    {
        //Parcours de la liste
        for( pt = lst->tete; pt!= NULL; pt= pt->suivant )
        {
            //Si l'element n'est pas mort
            if ( pt->estMort != true && pt->type == typeE )
            {
                pt->rect->w = largeurTex;
                pt->rect->h = hauteurTex;

                SDL_Rect rect = { pt->rect->x- camera.x, pt->rect->y -  camera.y, pt->rect->w, pt->rect->h };
                SDL_RenderCopy( getRenderer() , tex , NULL, &rect );
            }
        }
    }
}