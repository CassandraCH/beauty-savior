/**
 * \file entite.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le comportement des entités 
 * \brief Gestion des collisions entre le joueur et le décor (plateformes), le joueur et les ennemis, les ennemis et les projectiles ou si le joueur tombe dans le vide
 */
#include "baseGame.h"

/***
 * 
 */


extern void UpdateEnnemi()
{

    Node * pt = getEnnemis()->tete;
     for(; pt != NULL; pt = pt->suivant)
    {
        if ( !pt->estMort )
        {
            pt->rect->x += pt->vx;
            pt->rect->y += pt->vy;

            pt->vy += GRAVITY;
        }
    }
}

/**
 *  Mis à jour des Bullets() 
 */ 
extern bool UpdateBullets( typeEntite typeA, typeEntite typeB )
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

                    if ( typeA == joueur && pt->type == bull ) 
                    {
                         printf("Joueur\n");
                        // Si le joueur est tourné on inverse le sens du tir
                        if( getPlayer()->estTourne )
                            pt->movingX = -6;
                        else 
                            pt->movingX =  6;
                    }
                    else if ( typeB == ennemi && pt->type == feu )
                    {  

                        printf("Ennemi\n");
                        if( getPlayerX() + getPlayer()->w  <=pt->rect->x )
                            pt->movingX = -6;
                        else 
                            pt->movingX = 6;
                    }
                    pt->lancer = false;
                }
               
                pt->rect->x += pt->movingX;
            }
            else 
            {
                SetNombreTir_Ennemis();
                pt->estMort = true;   
            }

        }
    }
}


extern void SetNombreTir_Ennemis()
{
    
    Node * pt = getEnnemis()->tete;
     for(; pt != NULL; pt = pt->suivant)
    {
        if ( !pt->estMort )
        {
            if( pt->nb_lancer < 1  ) 
            {
                pt->nb_lancer = 1;
            }
            else 
            {
                pt->nb_lancer = 0;
            }
        }
    }
    
}


/**
 *  Fonction de création d'un tir 
 *  Prend en paramètre le type du tir, la largeur du sprite, sa hauteur. La position en X et Y du début du tir.
 */
extern void CreerTir( typeEntite type,int width, int height, int startX, int startY )  
{
    SDL_Rect *rect = malloc( sizeof(SDL_Rect) );
    rect->w = 41;
    rect->h = 47;
    rect->y = ( startY +  height  / 2 ) - rect->h / 2;
    rect->x = startX + 25;
    
    insertion( &bullet, rect, type );
}


/**
 *  
 * Fonction qui s'occupe de la gestion des attaques des ennemies.
 *  
 */ 
extern void attaqueEnnemis() 
{
    Node * pt = getEnnemis()->tete;
     for(; pt != NULL; pt = pt->suivant)
    {
    
        if ( !pt->estMort )
        {
            float distance = sqrt(pow(pt->rect->x - getPlayerX(), 2) +  pow(pt->rect->y - getPlayerY(), 2)); 
            if( distance < (pt->rect->w*3) + getPlayer()->w )
            {
                    if( pt->nb_lancer < 1) 
                    {
                        SetNombreTir_Ennemis();
                        CreerTir(feu, pt->rect->w, pt->rect->h, pt->rect->x, pt->rect->y );
                    }
            }
        }

    }

}


/*
    Mise à jour des ennemis
*/
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

    }
}   


/**
 *  
 * Fonction de detection du joueur avec le décor et les s
 */
extern void collisionDetection()
{
    
     /*##### JOUEUR ######*/
    // Largeur et Hauteur du joueur
    float joueur_w = getPlayer()->w ;
    float joueur_h = getPlayer()->h;
    
    // Position X & Y du joueur
    float joueur_x = getPlayerX();
    float joueur_y = getPlayerY();

    /*
        côté droit = x + largeur;
        coté gauche = x;
        coté bas = y + haut
        coté haut = y 
    */

    // Vérifie la collision avec les ennemies sur la gauche et la droite.
     for( Node * pt = listEnnemis.tete ; pt != NULL; pt = pt->suivant)
    {
            /*##### ENNEMI ######*/
        // Largeur et Hauteur de l'ennemi
        float ennemi_w = pt->rect->w;
        float ennemi_h = pt->rect->h;

        // Position X & Y de l'ennemi
        float ennemi_x = pt->rect->x;
        float ennemi_y = pt->rect->y;
         
        
        // Vérifie les collisions à gauche , droite, bas et en haut
        if(collide2d( joueur_x, joueur_y, ennemi_x, ennemi_y , joueur_w, joueur_h, ennemi_w, ennemi_h ) && pt->type == ennemi )
        {
            
            /*
                Gestion de la collision pour le saut 
                Vérifie que le joueur ce trouve bien au dessus de l'ennemi 
            */
            if( joueur_x+joueur_w > ennemi_x && joueur_x < ennemi_x+ennemi_w  )
            {   
                /* Vérifie si lorsque le joueur tombe, il touche le haut de l'ennemi  */
                if( joueur_y+joueur_h > ennemi_y && joueur_y < ennemi_y && getPlayer()->vy > 0 )
                {
                    // Si il n'est pas déjà mort alors il le devient.
                    if( !pt->estMort )
                    {
                        pt->estMort = true;  
                      
                    }
                     break;   
                }
                else
                {
                    // Sinon c'est que le joueur rentre en collision sur le côté. 
                    actualiserJoueur(); 
                }
            } 

            
             break;
        }
    }

    //Vérifie si le joueur tombe dans le vide et qu'il dépasse la hauteur de l'écran
    if( getPlayer()->y > 600)
    {
        actualiserJoueur();
    }
    
    /*##### COLLISION DECOR ####*/
    // Vérifie les collisions avec le décor
    collision_Decor(joueur,joueur_w, joueur_h, &getPlayer()->x , &getPlayer()->y , &getPlayer()->vy , &getPlayer()->estSurSol );

}


// extern void collision_Decor()
extern void collision_Decor( typeEntite type, float type_w, float type_h , float * type_x, float * type_y, float *vy, bool *estSurSol)
{   
    
     for(Node * pt = getCollider()->tete ; pt != NULL; pt = pt->suivant)
    {   
            /*##### BRIQUES ######*/
            // Largeur et Hauteur des blocs de collisions
            float collider_w = pt->rect->w;
            float collider_h = pt->rect->h;

            // Position X & Y des blocs de collisions
            float collider_x = pt->rect->x;
            float collider_y = pt->rect->y;
            
            /*
                Gestion des colisions avec le décor .
                Divers traitement 
                Cas du haut, bas, droit & gauche
            */
            if( (*type_x) + type_w / 2 > collider_x && (*type_x) + type_w / 2 < collider_x+collider_w  )
            {
                // Le haut du joueur rentre en collision avec le bas d'un bloc.
                if( (*type_y) < collider_y+collider_h && (*type_y) > collider_y && (*vy) < 0 )
                {
                    
                    (*type_y) = collider_y + collider_h;
                    (*type_y) = collider_y + collider_h;

                    // On arrête le saut 
                    (*vy) = 0;
                }
            }

           
            if( (*type_x)+type_w > collider_x && (*type_x) < collider_x+collider_w  )
            {   
                // Le bas du joueur est en collision avec le haut du bloc
                if((*type_y)+type_h > collider_y && (*type_y) < collider_y && (*vy) > 0 )
                {
                    (*type_y) = collider_y-type_h;
                    (*type_y) = collider_y-type_h;

                   if( type == joueur )
                   {
                        joueur_surSol();
                   }
                   
                }
            }

            if( (*type_y) + type_h > collider_y && (*type_y)<collider_y+collider_h)
            {
                 // Le côté droit du joueur est en collision avec le coté gauche du bloc
                if((*type_x)  < collider_x+collider_w && (*type_x)+type_w > collider_x+collider_w && (*vy) < 0)
                {
    
                    (*type_x) = collider_x+collider_w;
                    (*type_x) = collider_x+collider_w;

                    (*vy) = 0;
                }
                 // Le côté gauche du joueur est en collision avec le coté droit du bloc
                else if( (*type_x)+type_w > collider_x && (*type_x) < collider_x && (*type_x) > 0)
                {
                    //correct x
                    (*type_x)  = collider_x-type_w;
                    (*type_x) = collider_x-type_w;

                    (*vy) = 0;
                }
            }
        }
}

// extern void ennemi_surSol()
// {

//      for( Node * pt = listEnnemis.tete ; pt != NULL; pt = pt->suivant)
//     {
//         /*##### ENNEMI ######*/
//         // Largeur et Hauteur de l'ennemi
//         float ennemi_w = pt->rect->w;
//         float ennemi_h = pt->rect->h;

//         // Position X & Y de l'ennemi
//         float ennemi_x = pt->rect->x;
//         float ennemi_y = pt->rect->y;
        
//         pt->vy = 0;
//         // Le joueur est posé sur un bloc. 
//         if(!pt->estSurSol)
//         {
//             pt->estSurSol = true;
//         }

//     }

// }