#include "baseGame.h"



extern void init_List(LinkedList *list)
{
  Listes()->head = NULL;
  Listes()->tail = NULL;
  Listes()->nodeCount = 0;
}


extern Node* creerRect(SDL_Rect*rect, typeItem item_t, bool isLeft)
{   
    Node * nouvelElement = malloc( sizeof( Node ) );
    nouvelElement->next = NULL;
    nouvelElement->rect = rect;
    nouvelElement->estMort = false;
    nouvelElement->estSurSol = false;
    nouvelElement->x = rect->x;
    nouvelElement->y = rect->y;
    nouvelElement->w = rect->w;
    nouvelElement->h = rect->h;
    nouvelElement->vx = -1.5f;
    nouvelElement->vx = 0;
    nouvelElement->estTourne = isLeft;
    // nouvelElement->launch = true;
    nouvelElement->type = item_t;
    return ( nouvelElement );
}



extern void insertion(LinkedList * list, SDL_Rect *rect, typeItem items_t, bool isLeft)
{
 
  Node *nouvelElement = CreateRect(rect, items_t);
 
  if (list->nodeCount == 0){
    // Cas lorsque la liste est vide
    list->head = nouvelElement;
    list->tail = nouvelElement;
  }
  else{
    // Cas lorsque la liste n'est pas vide
    list->tail->next = nouvelElement;
    list->tail = nouvelElement;
  }
   
  list->nodeCount++;
  nouvelElement->id = list->nodeCount;
    printf("ID element: %d\n", nouvelElement->id );
    printf("Nombre element: %d\n", list->nodeCount );
}


// extern void moveRectangle ( LinkedList * lst )
// {
//      Node *pt;
//     if( lst->nodeCount  > 0 )
//     {   
        
//         for( pt = lst->head; pt!= NULL; pt= pt->next )
//         {

//             if( pt->rect->x < camera.x+camera.w )
//             {
//                 pt->rect->x += 4;
//             }
//             else 
//             {
//                 pt->touche = true;
//             }

//         }
//     }
// }

extern void deleteList(LinkedList * lst)
{
    Node * temp;
    Node * current = lst->head;
    while( current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
        lst->nodeCount--;
    }
    printf("Nombres occurences :%d\n", lst->nodeCount);
    printf("TOUS LES NŒUDS DE LA LISTE ONT ETAIENT DETRUIT\n");
}

extern void deleteQueue(LinkedList *lstPtr){

  if( lstPtr != NULL )
  {
        if( lstPtr->nodeCount  > 0 )
        {
            Node *first = lstPtr->head;
            printf("ID element: %d\n", first->id );        
            if (lstPtr->nodeCount == 1){
                // Cas si il n'y a qu'un élément 
                lstPtr->head = NULL;
                lstPtr->tail = NULL;

            }
            else{
                //Si il y a plusieurs élements il faut supprimer le premier
                lstPtr->head = first->next;
            }
            
            free(first->rect);
            free(first);
            lstPtr->nodeCount --;
        }
  }
    
    printf("Nombre element : %d\n", lstPtr->nodeCount);
}



extern bool deleteFirst(LinkedList * lst)
{
    
    if( lst->nodeCount == 0 ){
        return false;
    }

    Node * first = lst->head;

    if (lst->nodeCount == 1)
    {
        lst->head = NULL; 
        lst->tail = NULL;
    }
    else 
    {
        lst->head = first->next;
    }
    free(first);
    lst->nodeCount--;
    printf("Nombre element: %d\n", lst->nodeCount);
    return true;
}


extern bool deleteLast(LinkedList * lst)
{
    if( lst->nodeCount == 0 ){
        return false;
    }

    Node * current = lst->head;
    Node * last = lst->tail;

    if (lst->nodeCount == 1)
    {
        lst->head = NULL; 
        lst->tail = NULL;
    }
    else 
    {
        while( current->next != lst->tail )
            current = current->next;

        lst->tail= current;
        lst->tail->next = NULL;

    }
    free(last);
    lst->nodeCount--;
    printf("Nombre element: %d\n", lst->nodeCount);
    return true;
}


extern Node * find (LinkedList *lsptr, int target, Node **prvPtr)
{
    Node * current = lsptr->head;
    *prvPtr = NULL;
    
    while( current != NULL )
    {
        if ( current->touche == target )
        {
            break;
        }
        *prvPtr = current;
        current = current->next;
    }
    return current;
}


extern bool deleteTarget(LinkedList *lsptr, int target)
{   
    Node * current = NULL, *prev = NULL;
    current = find(lsptr,target, &prev);
    if( current == NULL ){
        return false;
    }

    if( current == lsptr->head )
    {
       return deleteFirst(lsptr);
    }
    
    else if( current == lsptr->tail )
    {
       return deleteLast(lsptr);
    }
    else 
    {
        prev->next = current->next;
        free(current);
        lsptr->nodeCount--;

        printf("Nombre element: %d\n", lsptr->nodeCount);
        return true; 
    }
    
}

extern void collisionDetect()
{
    Node * pt;
    
    // Vérifie la collision avec les items
     for(pt = Listes()->head; pt != NULL; pt = pt->next)
    {
        if(collide2d(getPlayerX(), getPlayerY(), pt->rect->x,pt->rect->y,50,50,25, 25 ) && pt->type == item )
        {

            if( !pt->touche )
            {
               pt->touche = true;
               
            }
            break;
        }
    }
    Node * pt2 = NULL;
    //Vérifie la collision avec les armes 
    for(pt2 = bullet.head; pt2 != NULL; pt2 = pt2->next)
    {
     
          
        for(pt = Listes()->head; pt != NULL; pt = pt->next)
        {
            if(collide2d( pt2->rect->x , pt2->rect->y, pt->rect->x,pt2->rect->y,20,20,50, 50 ) && pt->type == ennemy )
                {

                    if( !pt->touche )
                    {
                        pt->touche = true;
                    
                    }
                    break;
                }
            
            }
        
    }


}


extern void RenderElements(LinkedList *lst,SDL_Texture * tex, typeEntite typeE)
{
    Node *pt;
    if( lsptr->nodeCount  > 0 )
    {
        for( pt = lst->head; pt!= NULL; pt= pt->next )
        {
           if ( pt->isDead != true && pt->type == item_t )
           {
            SDL_Rect rect = {  pt->x - camera.x , pt->y - camera.y , pt->w, pt->h };
            SDL_RenderCopy( getRenderer() , tex , NULL, &rect );
           }
        }
    }
        
}