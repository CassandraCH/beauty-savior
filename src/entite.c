#include "baseGame.h"

extern bool UpdateBullets(  )
{
    
    Node *pt;
    if( getBullets()->nodeCount  > 0 )
    {   
        for( pt = getBullets()->tete; pt!= NULL; pt= pt->suivant )
        {

            if(  pt->rect->x > 0-25  && pt->rect->x < camera.x+camera.w )
            {   
                
               if ( pt->lancer )
                {
                    if( getPlayer()->estTourne )
                        pt->movingX = -6;
                    else 
                        pt->movingX =  6;
                    pt->lancer = false;
                }
                pt->rect->x += pt->movingX;
            }
            else 
            {
                pt->estMort = true;
                supprimeCible(getBullets(), true);
            }

        }
    }
}




extern void UpdateEnnemis()
{
     Node * pt = getEnnemis()->tete;
     
     for(; pt != NULL; pt = pt->suivant)
    {
    
        if ( !pt->estMort )
        {
            pt->rect->x = pt->baseX;
            pt->rect->y = pt->baseY;
            pt->rect->x = pt->baseX+ sinf( (pt->phase*2)+ getBaseGame()->time*0.04f)*75;
        }
        else 
        {
            supprimeCible(getEnnemis(), true);
        }

    }
}   



extern void collisionDetection()
{
    Node * pt;
    
    // Vérifie la collision avec les items
     for(pt = listCollider.tete; pt != NULL; pt = pt->suivant)
    {
        if(collide2d(getPlayerX(), getPlayerY(), pt->x,pt->y,50,50,25, 25 ) && pt->type == item )
        {

            if( !pt->estMort )
            {
               pt->estMort = true;
               
            }
            break;
        }
    }


    Node * pt_e = NULL;
    // Vérifie la collision avec les ennemies
     for(pt_e = listEnnemis.tete ; pt_e != NULL; pt_e = pt_e->suivant)
    {
        float mw = 50; float mh = 50;
        // homme position en x et y 
        float mx = getPlayerX(), my =getPlayerY();
   
        float bx = pt_e->rect->x, by = pt_e->rect->y, bw = pt_e->rect->w, bh = pt_e->rect->h;

        if(collide2d(getPlayerX(), getPlayerY(), pt_e->rect->x,pt_e->rect->y,50,50,50, 50 ) && pt_e->type == ennemi )
        {
				
            if( mx+mw > bx && mx < bx+bw  )
            {   
                
                if( my+mh > by && my < by && getPlayer()->vy > 0 )
                {
                    // correct y
                    getPlayer()->y = by-mh;
                    my = by-mh;

                    getPlayer()->nb_lancer = 0;
                    // landed on the ledge stop any velocity
                    //getPlayer()->vy = 0;
                    if( !pt_e->estMort )
                    {
                        pt_e->estMort = true;
                        
                    }
                     break;   
                }
                else
                {
                    actualiserJoueur(); 
                }
            } 

            
             break;
        }
    }

    //Check for falling
    if( getPlayer()->y > 600)
    {
        actualiserJoueur();
       
    }
    
    // checks for collision with any ledges(brick blocks)
    for(pt =  listCollider.tete; pt != NULL; pt = pt->suivant)
    {   


        
            // man taille en largeur et hauteur.
            float mw = 50; float mh = 50;
            // homme position en x et y 
            float mx = getPlayerX(), my =getPlayerY();
            // position en x et y des briques, et taille en largeur et hauteur.
            float bx = pt->rect->x, by = pt->rect->y, bw = pt->rect->w, bh = pt->rect->h;

            //  player.x+player.w/2 > collider.x && player.x+player.w/2 < collider.x+ collider.w
            if( mx+mw/2 > bx && mx+mw/2 < bx+bw  )
            {
                // are we bumping our head ?
                if( my < by+bh && my > by && getPlayer()->vy < 0 )
                {
                    
                    getPlayer()->y = by+bh;
                    my = by+bh;

                    
                    getPlayer()->vy = 0;
                    getPlayer()->estSurSol = true;

                }
            }

           
            if( mx+mw > bx && mx < bx+bw  )
            {   
                
                if( my+mh > by && my < by && getPlayer()->vy > 0 )
                {
                    
                    getPlayer()->y = by-mh;
                    my = by-mh;

                   
                    getPlayer()->vy = 0;
                    if(!getPlayer()->estSurSol)
                    {
                        getPlayer()->estSurSol = true;
                    }

                }
            }

            if(my+mh > by && my<by+bh)
            {
            
                if(mx < bx+bw && mx+mw > bx+bw && getPlayer()->vx < 0)
                {
    
                    getPlayer()->x = bx+bw;
                    mx = bx+bw;

                    getPlayer()->vx = 0;
                }
               
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
