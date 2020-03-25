/**
 * \file entite.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le comportement des entités 
 * \details Gestion des collisions entre le joueur et le décor (plateformes), le joueur et les ennemis, les ennemis et les projectiles ou si le joueur tombe dans le vide
 */
#include "baseGame.h"

/**
 * \fn extern bool UpdateBullets( typeEntite typeA, typeEntite typeB )
 * \brief Fonction qui permet mettre a jour les bullets
 * \details Parcours de la listes des bullets 
 * \details En fonction de si il s'agit d'un ennemi ou du joueur, le comportement des bullets est différent
 * \param typeA type de la premiere entite : item, joueur, ennemi, platform , bull, feu
 * \param typeB type de la deuxieme entite : item, joueur, ennemi, platform , bull, feu
 * \return Une valeur de type booleen
*/
extern bool UpdateBullets( typeEntite typeA, typeEntite typeB )
{
    Node *pt; //Pointeur sur le bullet actuel

    //sI il y a au moins un bullet dans la liste
    if( getBullets()->nodeCount > 0 )
    {   
        //Parcours de liste des bullets
        for( pt = getBullets()->tete; pt!= NULL; pt= pt->suivant )
        {
            //Si le joueur est suffisamment proche de l'ennemi
            if(  pt->rect->x > 0-15  && pt->rect->x < camera.x+camera.w )
            {   
                //Si le bullet actuel peut etre lancer
                if ( pt->lancer )
                {
                    //Si l'entite est le joueur et que le bullet actuel est de type bull => le bullet est tire a gauche ou a droite en fonction de la position du joueur
                    if ( typeA == joueur && pt->type == bull ) 
                    {
                        printf("Joueur\n");

                        //Si le joueur est tourné on inverse le sens du tir
                        if( getPlayer()->estTourne )
                            pt->movingX = -6;

                        //Sinon le sens de tir n'est pas inverse
                        else 
                            pt->movingX =  6;
                    }

                    //Si l'entite est un ennemi et que le bullet actuel est de type feu => le bullet est tire a gauche ou a droite en fonction de a position du joueur par rapport a l'ennemi
                    else if ( typeB == ennemi && pt->type == feu )
                    {  
                        printf("Ennemi\n");

                        if( getPlayerX() + getPlayer()->w  <= pt->rect->x )
                            pt->movingX = -6;
                            
                        else 
                            pt->movingX = 6;
                    }
                    //Mise a jour de l'etat du lancer du bullet => ne peut plus etre lancer
                    pt->lancer = false;
                }
               
                pt->rect->x += pt->movingX;
            }
            //Sinon
            else 
            {
                SetNombreTir_Ennemis();
                //Mise a jour de l'etat du bullet
                pt->estMort = true;   
            }

        }
    }
}

/**
 * \fn extern void SetNombreTir_Ennemis()
 * \brief Fonction qui configurer le nombre de tir des ennemis
 * \details 
 * \return pas de valeur de retour (void)
*/
extern void SetNombreTir_Ennemis()
{
    Node * pt = getEnnemis()->tete; //Pointeur sur l'ennemi actuel

    //Parcours de la liste des ennemis 
    for(; pt != NULL; pt = pt->suivant)
    {
        //Si l'ennemi n'a pas ete tue
        if ( !pt->estMort )
        {
            //Si son compteur de lancer est inferieur a 1 => le remettre a 1
            if( pt->nb_lancer < 1  ) 
            {
                pt->nb_lancer = 1;
            }
            //Sinon, le mettre a 0

            else 
            {
                pt->nb_lancer = 0;
            }
        }
    }
}

/**
 * \fn extern void CreerTir(typeEntite type, int width, int height, int startX, int startY)
 * \brief Fonction qui creer un tir
 * \details 
 * \param type type du tir
 * \param width largeur du sprite
 * \param height hauteur du sprite
 * \param startX position en x du sprite
 * \param startY position en y du sprite
 * \return pas de valeur de retour (void)
*/
extern void CreerTir(typeEntite type, int width, int height, int startX, int startY)
{
    SDL_Rect *rect = malloc(sizeof(SDL_Rect)); //Creation d'une structure de type rectangle en SDL

    /* Ajout des valeurs dans les champs de la structure */
    rect->w = 41;
    rect->h = 47;
    rect->y = (startY + height / 2) - rect->h / 2;
    rect->x = startX + 25;

    //Gestion de l'affichage
    insertion(&bullet, rect, type, false);
}

/**
 * \fn extern void attaqueEnnemis() 
 * \brief Fonction qui gère les attaques des ennemis
 * \details Parcours des ennemis, verification qu'il n'est pas mort et de son compteur de lancer
 * \return pas de valeur de retour (void)
*/
extern void attaqueEnnemis() 
{
    Node * pt = getEnnemis()->tete; // pointeur sur l'ennemi actuel

    //Parcours de la liste des ennemis
    for(; pt != NULL; pt = pt->suivant)
    {
        //Si l'ennemi n'est pas mort
        if ( !pt->estMort )
        {
            float distance = sqrt(pow(pt->rect->x - getPlayerX(), 2) +  pow(pt->rect->y - getPlayerY(), 2)); 
            if( distance < (pt->rect->w*3) + getPlayer()->w )
            {
                //Si le compteur de lancer disponible est inferieur a 1 => on reconfigure ce compteur et on cree un tir
                if( pt->nb_lancer < 1) 
                {
                    SetNombreTir_Ennemis();
                    CreerTir(feu, pt->rect->w, pt->rect->h, pt->rect->x, pt->rect->y );
                }
            }
        }
    }
}

/**
 * \fn extern void UpdateEnnemis()
 * \brief Fonction qui met a jour les ennemis
 * \details 
 * \return pas de valeur de retour (void)
*/
extern void UpdateEnnemis()
{
    Node *pt = getEnnemis()->tete; //pointeur sur l'ennemi actuel 

    //Parcours de la liste des ennemis
    for(; pt != NULL; pt = pt->suivant)
    {
        //Verifie que l'ennemi n'est pas mort et qu'il est actif
        if ( !pt->estMort && pt->actif )
        {
            //Affectation des positions en x et en y initiales
            pt->rect->x = pt->baseX;
            pt->rect->y = pt->baseY;

            //Gestion de l'amplitude du deplacement 
            pt->rect->x = pt->baseX + sinf( (pt->phase*2)+ getBaseGame()->time * 0.04f ) * 55;
       }
    }
}   

/**
 * \fn extern void collisionDetection()
 * \brief Fonction qui gere les collision entre le joueur et le decor, le joueur et les ennemis; et si le joueur tombe dans le vide
 * \details 
 * \return pas de valeur de retour (void)
*/
extern void collisionDetection()
{
    
    /*##### JOUEUR ######*/
    // Largeur et Hauteur du joueur
    float joueur_w = getPlayer()->tex.w ; // variable qui stocke la largeur du joueur 
    float joueur_h = getPlayer()->tex.h;  // variable qui stocke la hauteur du joueur 

    // Position X & Y du joueur
    float joueur_x = getPlayerX(); // variable qui stocke la position en x du joueur 
    float joueur_y = getPlayerY(); // variable qui stocke la position en y du joueur 

    /*
        côté droit = x + largeur;
        coté gauche = x;
        coté bas = y + haut
        coté haut = y 
    */


    /* 
        Verifie la collision avec les ennemis sur la gauche et la droite
        *pt = pointeur sur l'ennemi actuel
    */
    //Parcours de la liste des ennemis
    for( Node * pt = listEnnemis.tete ; pt != NULL; pt = pt->suivant)
    {
        /*##### ENNEMI ######*/
        // Largeur et Hauteur de l'ennemi
        float ennemi_w = pt->rect->w; // variable qui stocke la largeur de l'ennemi 
        float ennemi_h = pt->rect->h; // variable qui stocke la hauteur du joueur 

        // Position X & Y de l'ennemi
        float ennemi_x = pt->rect->x; // variable qui stocke la position en x du joueur 
        float ennemi_y = pt->rect->y; // variable qui stocke la position en y du joueur 


        // Vérifie les collisions à gauche , droite, bas et en haut
        if (collide2d(joueur_x, joueur_y, ennemi_x, ennemi_y, joueur_w, joueur_h, ennemi_w, ennemi_h) && pt->type == ennemi)
        {
            /*
                Gestion de la collision pour le saut 
                Vérifie que le joueur ce trouve bien au dessus de l'ennemi 
            */
            if (joueur_x + joueur_w > ennemi_x && joueur_x < ennemi_x + ennemi_w)
            {
                // Vérifie si lorsque le joueur tombe, il touche le haut de l'ennemi 
                if (joueur_y + joueur_h > ennemi_y && joueur_y < ennemi_y && getPlayer()->vy > 0)
                {
                    // Si l'ennemi n'est pas deja mort alors il le devient
                    if (!pt->estMort)
                    {
                        pt->estMort = true;

                    }
                    break;
                }

                // Sinon c'est que le joueur rentre en collision sur le cote => la partie est perdu
                else
                {

                    Init_GameOver();

                }
            }
            break;
        }
    }//Fin du parcours de la liste des ennemis

    //Verifie si le joueur tombe dans le vide et qu'il dépasse la hauteur de l'écran = > la partie est perdu
    if( getPlayer()->y > 720 ) 
    {
        Init_GameOver();
    }

    // Vérifie les collisions avec le décor
    collision_Decor( );

}

/**
 * \fn extern void collision_Decor()
 * \brief Fonction qui gere les collisions avec le decor
 * \details 
 * \return pas de valeur de retour (void)
*/
extern void collision_Decor()
{
    
    /*##### JOUEUR ######*/
    // Largeur et Hauteur du joueur
    float joueur_w = getPlayer()->tex.w ;
    float joueur_h = getPlayer()->tex.h;
    
    // Position X & Y du joueur
    float joueur_x = getPlayerX();
    float joueur_y = getPlayerY();

    
    for(Node * pt = getCollider()->tete ; pt != NULL; pt = pt->suivant)
    {   
        /*##### BRIQUES ######*/
        // Largeur et Hauteur des blocs de collisions
        float collider_w = pt->rect->w; // variable qui stocke la largeur du collider 
        float collider_h = pt->rect->h; // variable qui stocke la hauteur du collider 

        // Position X & Y des blocs de collisions
        float collider_x = pt->rect->x; // variable qui stocke la position en x du collider 
        float collider_y = pt->rect->y; // variable qui stocke la position en y du collider 


        typeEntite typeCollider = pt->type;
        
        /*
            Gestion des colisions avec le décor
            Divers traitement 
            Cas du haut, bas, droit & gauche
        */

        
        //  player.x+player.w/2 > collider.x && player.x+player.w/2 < collider.x+ collider.w
        if( joueur_x+joueur_w/2 > collider_x && joueur_x+joueur_w/2 < collider_x+collider_w  )
        {
            // Le haut du joueur rentre en collision avec le bas d'un bloc..
            if( joueur_y < collider_y+collider_h && joueur_y > collider_y && getPlayer()->vy < 0 )
            {         
                // correct y
                getPlayer()->y = collider_y+collider_h;
                joueur_y = collider_y+collider_h;

                // On arrête le saut 
                getPlayer()->vy = 0;
            }
        }

        if( joueur_x+joueur_w > collider_x && joueur_x < collider_x+collider_w  )
        {   
            // Le bas du joueur est en collision avec le haut du bloc
            if( joueur_y+joueur_h > collider_y && joueur_y < collider_y && getPlayer()->vy > 0 )
            {
                if( typeCollider == checkpoint )
                {
                    // Init_GameOver();
                    Init_Continue();

                }
                else 
                {
                    // correct y
                    getPlayer()->y = collider_y-joueur_h;
                    joueur_y = collider_y-joueur_h;

                    // On arrête le saut 
                    getPlayer()->vy = 0;
                    if(!getPlayer()->estSurSol)
                    {
                        getPlayer()->estSurSol = true;
                    }
                }
            }
        }

        if(joueur_y+joueur_h > collider_y && joueur_y<collider_y+collider_h)
        {
            //Le côté droit du joueur est en collision avec le coté gauche du bloc
            if(joueur_x < collider_x+collider_w && joueur_x+joueur_w > collider_x+collider_w && getPlayer()->vx < 0)
            {
                if( typeCollider == checkpoint )
                {
                    //Init_GameOver();
                    Init_Continue();    
                }       
                else 
                {
                    //correct x
                    getPlayer()->x = collider_x+collider_w;
                    joueur_x = collider_x+collider_w;

                    getPlayer()->vx = 0;
                }
            }

            // Le côté droit du joueur est en collision avec le coté gauche du bloc
            else if(joueur_x+joueur_w > collider_x && joueur_x < collider_x && getPlayer()->x > 0)
            {
                if( typeCollider == checkpoint )
                {
                        // Init_GameOver();
                        Init_Continue();

                }
                else 

                {
                    //correct x
                    getPlayer()->x = collider_x-joueur_w;
                    joueur_x = collider_x-joueur_w;

                    // On arrete le saut
                    getPlayer()->vx = 0;
                }
            }
        }//fin if
    }//fin for

}

