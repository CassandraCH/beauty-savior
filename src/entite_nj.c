#include "baseGame.h"



extern void init_List(LinkedList *list)
{
  Listes()->head = NULL;
  Listes()->tail = NULL;
  Listes()->nodeCount = 0;
}


extern Node* CreateRect(SDL_Rect*rect, typeItem item_t)
{   
    Node * nouvelElement = malloc( sizeof( Node ) );
    nouvelElement->next = NULL;
    nouvelElement->rect = rect;
    nouvelElement->touche = false;
    nouvelElement->id = 0;
    nouvelElement->type = item_t;
    return ( nouvelElement );
}


extern void  drawCollider(LinkedList *lsptr, SDL_Texture * tex, typeItem item_t )
{
    Node *pt;
    if( lsptr->nodeCount  > 0 )
    {
        for(pt = lsptr->head ; pt != NULL ; pt = pt->next )
        {
            SDL_Rect ledgeRect = {  pt->rect->x- camera.x ,pt->rect->y-  camera.y ,pt->rect->w,pt->rect->h };
            SDL_RenderCopy(getRenderer(), tex , NULL, &ledgeRect);
        }

        // for( pt = lsptr->head; pt!= NULL; pt= pt->next )
        // {
        //    if ( pt->touche != true && pt->type == item_t )
        //    {
        //     SDL_Rect legde = {  pt->rect->x - getBaseGame()->camera.x , pt->rect->y - getBaseGame()->camera.y , pt->rect->w, pt->rect->h };
        //     SDL_RenderCopy( getRenderer() , tex , NULL, &legde );
        //    }
        // }
    }
        
}

// extern void insertQueue(SDL_Rect *rect, typeItem items_t)
// extern void insertQueue(LinkedList * list, SDL_Rect *rect, typeItem items_t)
// {
 
//   Node *nouvelElement = CreateRect(rect, items_t);
 
//   if (Listes()->nodeCount == 0){
//     // this is the case when the list is empty
//     Listes()->head = nouvelElement;
//     Listes()->tail = nouvelElement;
//   }
//   else{
//     // this is the case when the list is not empty
   
//     Listes()->tail->next = nouvelElement;
//     Listes()->tail = nouvelElement;
//   }
   
//   Listes()->nodeCount++;
//   nouvelElement->id = Listes()->nodeCount;
//     printf("ID element: %d\n", nouvelElement->id );
//     printf("Nombre element: %d\n", Listes()->nodeCount );
// }

extern void insertQueue(LinkedList * list, SDL_Rect *rect, typeItem items_t)
{
 
  Node *nouvelElement = CreateRect(rect, items_t);
 
  if (list->nodeCount == 0){
    // this is the case when the list is empty
    list->head = nouvelElement;
    list->tail = nouvelElement;
  }
  else{
    // this is the case when the list is not empty
   
    list->tail->next = nouvelElement;
    list->tail = nouvelElement;
  }
   
  list->nodeCount++;
  nouvelElement->id = list->nodeCount;
    printf("ID element: %d\n", nouvelElement->id );
    printf("Nombre element: %d\n", list->nodeCount );
}

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
    printf("SUCCESSFULLY DELETED ALL NODES OF LINKED LIST\n");
}

extern void deleteQueue(LinkedList *lstPtr){

  if( lstPtr != NULL )
  {
        if( lstPtr->nodeCount  > 0 )
        {
            Node *first = lstPtr->head;
            printf("ID element: %d\n", first->id );        
            if (lstPtr->nodeCount == 1){
                // there is only one node
                lstPtr->head = NULL;
                lstPtr->tail = NULL;

            }
            else{
                // there are many nodes and we need to delete the first
                lstPtr->head = first->next;
            }
            
            free(first->rect);
            free(first);
            lstPtr->nodeCount --;
        }
  }
    
    printf("Nombre element : %d\n", lstPtr->nodeCount);
}


extern void moveRectangle ( LinkedList * lst )
{
     Node *pt;
    if( lst->nodeCount  > 0 )
    {   
        
        for( pt = lst->head; pt!= NULL; pt= pt->next )
        {

            if( pt->rect->x < camera.x+camera.w )
            {
                pt->rect->x += 4;
            }
            else 
            {
                pt->touche = true;
            }

        }
    }
}



extern void clearRect (LinkedList *lst)
{
           
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


extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
    return (! ( (x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))  )  );
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

        Node * pt_e = listEnnemies.head;
    // Vérifie la collision avec les ennemies
     for(; pt_e != NULL; pt_e = pt_e->next)
    {
        if(collide2d(getPlayerX(), getPlayerY(), pt_e->rect->x,pt_e->rect->y,50,50,25, 25 ) && pt_e->type == ennemy )
        {

            if( !getPlayer()->estMort )
            {
                if( getPlayer()->nombreVies > 0 )
                {
                    getPlayer()->estMort = true;
                    Init_MenuPrincipal();
                    DestructionNiveau();
                    getBaseGame()->state = MENU_PRINCIPAL;
                    getPlayer()->x = 100;
                    getPlayer()->y = 100;
                    getPlayer()->vx = 0;
                    getPlayer()->nombreVies--;
                    printf("Il reste %d points de vie\n", getPlayer()->nombreVies );
                }else 
                {
                    getPlayer()->x = 300;
                    getPlayer()->y = 300;
                    getPlayer()->vx = 0;
                }
            }
            break;
        }
    }


    //Check for falling
    if( getPlayer()->y > 600)
    {
        if(!getPlayer()->estMort  )
        {
          getPlayer()->estMort = true;
          Init_MenuPrincipal();
            DestructionNiveau();
            getBaseGame()->state = MENU_PRINCIPAL;

            getPlayer()->x = 100;
            getPlayer()->y = 100;
            getPlayer()->vx = 0;
        }
    }

    // checks for collision with any ledges(brick blocks)
    for(pt =  Listes()->head; pt != NULL; pt = pt->next)
    {
        // man taille en largeur et hauteur.
        float mw = 50; float mh = 50;
        // homme position en x et y 
        float mx = getPlayerX(), my =getPlayerY();
        // position en x et y des briques, et taille en largeur et hauteur.
        float bx = pt->rect->x, by = pt->rect->y, bw = pt->rect->w, bh = pt->rect->h;

        if( mx+mw/2 > bx && mx+mw/2 < bx+bw  )
        {
             // are we bumping our head ?
            if( my < by+bh && my > by && getPlayer()->vy < 0 )
            {
                // correct y
                getPlayer()->y = by+bh;
                my = by+bh;

                 // bumped our head, stop any velocity
                getPlayer()->vy = 0;
                getPlayer()->surLeSol = true;

            }
        }


        if( mx+mw > bx && mx < bx+bw  )
        {
            // are we landing on the ledge?
            if( my+mh > by && my < by && getPlayer()->vy > 0 )
            {
                // correct y
                getPlayer()->y = by-mh;
                my = by-mh;

                // landed on the ledge stop any velocity
                getPlayer()->vy = 0;
                if(!getPlayer()->surLeSol)
                {
                    // Mix_PlayChannel(-1, game->landSound, 0);
                    getPlayer()->surLeSol = 1;
                }

            }
        }

        if(my+mh > by && my<by+bh)
        {
          //rubbing against right edge
          if(mx < bx+bw && mx+mw > bx+bw && getPlayer()->vx < 0)
          {
            //correct x
            getPlayer()->x = bx+bw;
            mx = bx+bw;

            getPlayer()->vx = 0;
          }
          //rubbing against left edge
          else if(mx+mw > bx && mx < bx && getPlayer()->x > 0)
          {
            //correct x
            getPlayer()->x = bx-mw;
            mx = bx-mw;

            getPlayer()->vx = 0;
          }
        }
    }
}



