#include "baseGame.h"

extern void deplacement_entiteNJ(Entite *entity)
{


    entity->vx -= 0.001f;

    //  if( fabsf( entity->vx) < 0.1f)
    // {
    //         entity->vx = 0;
    // }
    
    entity->x += entity->vx;
    entity->y += entity->vy;
    

	// 	man->vy += GRAVITY;
    entity->vy += GRAVITY;
}

extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{   
    return (! ( (x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))  )  );
}




extern void collisionEntite(Entite *entite_a, Entite *entite_b )
{
    // Taille A
    float largeur_A = entite_a->w; 
    float hauteur_A = entite_a->h;

    // Taille B
    float largeur_B = entite_b->w;
    float hauteur_B = entite_b->h;
    
    // Position A
    float posX_A = entite_a->x; 
    float posY_A = entite_a->y;
    
    // Position B
    float posX_B = entite_b->x;
    float posY_B = entite_b->y; 

    
    if(collide2d(posX_A, posX_B, posX_B,posY_B, largeur_A ,hauteur_A, largeur_B, hauteur_B) && entite_b->type == ennemi )
    {
				
        if( posX_A+largeur_A > posX_B && posX_A < posX_B+largeur_B  )
        {    
        
            if( posY_A+hauteur_A > posY_B && posY_A < posY_B && entite_a->vy > 0 )
            {
                // correct y
                entite_a->y = posY_B-hauteur_A;
                posY_A = posY_B-hauteur_A;

                if( !entite_b->estMort )
                {
                    entite_b->estMort = true;
                }

            }
            else
            {
                if( !entite_a->estMort )
                {
                    entite_a->actualiserVie;
                }
            }
        } 

    }
    

}


extern void collisionDecor(Entite *entity)
{

    //Vérifie si l'entité tombe
    if( entity->y > 600)
    {
        if( !entity->estMort  )
        {
          entity->estMort = true;
          if( entity->type == joueur)
          {
            Init_MenuPrincipal();
            DestructionNiveau();
            getBaseGame()->state = MENU_PRINCIPAL;

            entity->x = 100;
            entity->y = 100;
            entity->vx = 0;
          }
        }
    }

    Node * ec = NULL;
    // Vérifie les collisions avec les colliders
    for(ec =  listCollider.tete ; ec != NULL; ec = ec->suivant )
    {   
            // taille en largeur
            float largeur_entity = entity->w; 
            // taille en hauteur
            float hauteur_entity = entity->h;

            // position X
            float posX_entity = entity->x;
            
            // position Y
            float posY_entity = entity->y;

            // position en x des colliders
            float collider_x = ec->rect->x;
            // position en y
            float collider_y = ec->rect->y; 
            // taille en largeur
            float collider_w = ec->rect->w;
            // taille en hauteur
            float collider_h = ec->rect->h;


            if( ec->type == platform )
            {

                    //  player.x+player.w/2 > collider.x && player.x+player.w/2 < collider.x+ collider.w
                if( posX_entity+largeur_entity/2 > collider_x && posX_entity+largeur_entity/2 < collider_x+collider_w  )
                {
                    // are we bumping our head ?
                    if( posY_entity < collider_y+collider_h && posY_entity > collider_y && entity->vy < 0 )
                    {
            
                        // correct y
                        entity->y = collider_y+collider_h;
                        posY_entity = collider_y+collider_h;

                        // bumped our head, stop any velocity
                        entity->vy = 0;
                        // entity->onGround = true
                    }
                }

                // player.x+player.w > collider.x && player.x < collider.x+ collider.w
                if( posX_entity+largeur_entity > collider_x && posX_entity < collider_x+collider_w  )
                {   
                    // player.y+player.h > collider.y && player.y < collider.x+ collider.w
                    // are we landing on the ledge?
                    if( posY_entity+hauteur_entity > collider_y && posY_entity < collider_y && entity->vy > 0 )
                    {
                        // correct y
                        entity->y = collider_y-hauteur_entity;
                        posY_entity = collider_y-hauteur_entity;

                        // landed on the ledge stop any velocity
                        entity->vy = 0;
                        if(!entity->estSurSol )
                        {
                            // Mix_PlayChannel(-1, game->landSound, 0);
                            entity->estSurSol = true;
                        }

                    }
                }
 

            }
            if(posY_entity+hauteur_entity > collider_y && posY_entity<collider_y+collider_h)
            {
                //rubbing against right edge
                if(posX_entity < collider_x+collider_w && posX_entity+largeur_entity > collider_x+collider_w && entity->vx < 0)
                {
                    if( entity->type == ennemi  )
                    {
                         entity->vx = 0 - entity->vx;
                    }
                    else if (entity->type == joueur && !(ec->type == fleche ) )
                    {
                        //correct x
                        entity->x = collider_x+collider_w;
                        posX_entity = collider_x+collider_w;

                        entity->vx = 0;
                    }
                }
                //rubbing against left edge
                else if(posX_entity+largeur_entity > collider_x && posX_entity < collider_x && entity->x > 0)
                {
                    if( entity->type == ennemi)
                    {
                        entity->vx = 0 - entity->vx;
                    }
                    else if (entity->type == joueur && !(ec->type == fleche) )
                    {
                        //correct x
                        entity->x = collider_x-largeur_entity;
                        posX_entity = collider_x-largeur_entity;

                        entity->vx = 0;
                    }
                    
                }
            } // fin collision gauche/droite
        }
        
    
}

