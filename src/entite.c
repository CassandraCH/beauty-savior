/**
 * \file entite.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le comportement des entités 
 * \brief Gestion des collisions entre le joueur et le décor (plateformes), le joueur et les ennemis, les ennemis et les projectiles ou si le joueur tombe dans le vide
 */
#include "baseGame.h"

/**
 * \fn extern bool Bullets_Update( typeEntite typeA, typeEntite typeB )
 * \brief Fonction qui permet de mettre a jour les bullets
 * \details Parcours de la listes des bullets 
 * \details En fonction de s'il s'agit d'un ennemi ou du joueur, le comportement des bullets est différent
 * \param typeA type de la premiere entite : item, joueur, ennemi, platform , bull, feu
 * \param typeB type de la deuxieme entite : item, joueur, ennemi, platform , bull, feu
 * \return Une valeur de type booleen
*/
extern bool Bullets_Update( typeEntite typeA, typeEntite typeB )
{
    Node *pt; //Pointeur sur le bullet actuel

    //S'il y a au moins un bullet dans la liste
    if( getBullets()->nodeCount > 0 )
    {   
        //Parcours de liste des bullets
        for( pt = getBullets()->head; pt!= NULL; pt= pt->next )
        {
            //Si le joueur est suffisamment proche de l'ennemi
            if(    pt->rect->x > 0-15  && pt->rect->x < camera.x + camera.w )
            {   
                //Si le bullet actuel peut etre lancer
                if ( pt->lancer )
                {
                    //Si l'entité A est le joueur et que le bullet actuel est de type bull => le bullet est tiré a Left ou a Right en fonction de la position du joueur
                    if ( typeA == joueur &&  ( pt->type == tree || pt->type == rock)  ) 
                    {
                        printf("Joueur\n");

                        //Si le joueur est tourné, on inverse le sens du tir
                        if( getPlayer()->estTourne )
                            pt->movingX = -20;

                        //Sinon le sens de tir n'est pas inversé
                        else 
                            pt->movingX =  20;
                    }

                    //Si l'entité A est un ennemi et que le bullet actuel est de type feu => le bullet est tiré a Left ou a Right en fonction de la position du joueur par rapport a l'ennemi
                    else if ( typeB == ennemi && pt->type == feu )
                    {  
                        printf("Ennemi\n");

                        //Si le joueur est à Left de l'ennemi, on inverse le sens du tir
                        if( getPlayerX() + getPlayer()->w  <= pt->rect->x )
                            pt->movingX = -18;

                        //Sinon le sens de tir n'est pas inversé
                        else 
                            pt->movingX = 18;
                    }
                    //Mise a jour de l'état du lancer du bullet => ne peut plus être lancer
                    pt->lancer = false;
                }
               
                pt->rect->x += pt->movingX;
            }
            //Sinon
            else 
            {
                Enemy_SetBullets();
                //Mise a jour de l'état du bullet
                pt->estMort = true;   
            }

        }
    }
}

/**
 * \fn extern void Enemy_SetBullets()
 * \brief Fonction qui configurer le nombre de tir des ennemis
 * \return pas de valeur de retour (void)
*/
extern void Enemy_SetBullets()
{
    Node * pt = getEnnemis()->head; //Pointeur sur l'ennemi actuel

    //Parcours de la liste des ennemis 
    for(; pt != NULL; pt = pt->next)
    {
        //Si l'ennemi n'a pas été tué
        if ( !pt->estMort )
        {
            //Si son compteur de lancer est inférieur à 1 => le remettre à 1
            if( pt->nb_lancer < 1  ) 
            {
                pt->nb_lancer = 1;
            }

            //Sinon, le mettre à 0
            else 
            {
                pt->nb_lancer = 0;
            }
        }
    }
}

/**
 * \fn extern void CreateBullet(typeEntite type, int width, int height, int startX, int startY)
 * \brief Fonction qui creer un tir
 * \param type type du tir
 * \param width largeur du sprite
 * \param height hauteur du sprite
 * \param startX position en x du sprite
 * \param startY position en y du sprite
 * \return pas de valeur de retour (void)
*/
extern void CreateBullet(typeEntite type, int width, int height, int startX, int startY)
{
    SDL_Rect *rect = malloc(sizeof(SDL_Rect)); //Creation d'une structure de type rectangle en SDL

    /* Ajout des valeurs dans les champs de la structure */
    rect->w = width;
    rect->h = height;
    rect->y = ( startY + height / 2 ) - rect->h / 2;
    rect->x = startX + 25;

    //Gestion de l'affichage
    Insert_Element(&bullet, rect, type, false);
}

/**
 * \fn extern void Enemy_Attack() 
 * \brief Fonction qui gère les attaques des ennemis
 * \details Parcours des ennemis, verification qu'il n'est pas mort et de son compteur de lancer
 * \return pas de valeur de retour (void)
*/
extern void Enemy_Attack() 
{
    Node * pt = getEnnemis()->head; // pointeur sur l'ennemi actuel

    //Parcours de la liste des ennemis
    for(; pt != NULL; pt = pt->next)
    {
        //Si l'ennemi n'est pas mort
        if ( !pt->estMort )
        {
            //distance pour que le joueur soit détectable par l'ennemi
            float distance = sqrt(pow(pt->rect->x - getPlayerX(), 2) +  pow(pt->rect->y - getPlayerY(), 2)); 

            if( distance < (pt->rect->w*7) + getPlayer()->w )
            {
                //Si le compteur de lancer disponible est inférieur à 1 => on reconfigure ce compteur et on créé un tir
                if( pt->nb_lancer < 1) 
                {
                    Enemy_SetBullets();
                    CreateBullet(feu, pt->rect->w, pt->rect->h, pt->rect->x, pt->rect->y );
                }
            }
        }
    }
}

/**
 * \fn extern void Enemy_Update()
 * \brief Fonction qui met à jour les ennemis
 * \return pas de valeur de retour (void)
*/
extern void Enemy_Update()
{
    Node *pt = getEnnemis()->head; //pointeur sur l'ennemi actuel 

    //Parcours de la liste des ennemis
    for(; pt != NULL; pt = pt->next)
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
 * \fn extern void Collision_Detection()
 * \brief Fonction qui gère les collision entre le joueur et le decor, le joueur et les ennemis; et si le joueur tombe dans le vide
 * \return pas de valeur de retour (void)
*/
extern void Collision_Detection()
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
        coté Left = x;
        coté bas = y + haut
        coté haut = y 
    */

    /* 
        Verifie la collision avec les ennemis sur la Left et la Right
        *pt = pointeur sur l'ennemi actuel
    */
    //Parcours de la liste des ennemis
    for( Node * pt = listEnnemis.head ; pt != NULL; pt = pt->next)
    {
        /*##### ENNEMI ######*/
        // Largeur et Hauteur de l'ennemi
        float ennemi_w = pt->rect->w; // variable qui stocke la largeur de l'ennemi 
        float ennemi_h = pt->rect->h; // variable qui stocke la hauteur du joueur 

        // Position X & Y de l'ennemi
        float ennemi_x = pt->rect->x; // variable qui stocke la position en x du joueur 
        float ennemi_y = pt->rect->y; // variable qui stocke la position en y du joueur 


        // Vérifie les collisions à Left , Right, bas et en haut
        if (collide2d(joueur_x, joueur_y, ennemi_x, ennemi_y, joueur_w, joueur_h, ennemi_w, ennemi_h) && pt->type == ennemi)
        {
            /*
                Gestion de la collision pour le saut 
                Vérifie que le joueur se Find bien au-dessus de l'ennemi 
            */
            if (joueur_x + joueur_w > ennemi_x && joueur_x < ennemi_x + ennemi_w)
            {
                // Vérifie si lorsque le joueur tombe, il touche le haut de l'ennemi 
                if (joueur_y + joueur_h > ennemi_y && joueur_y < ennemi_y && getPlayer()->vy > 0)
                {
                    //Incrémentation du score
                     SetHUD_IntToTexture(getScores(),(SDL_Color){0xFF,0xFF,0xFF,0xFF} , "", ++getPlayer()->scores, 560, 21 );

                    // Si l'ennemi n'est pas deja mort alors il le devient
                    if (!pt->estMort)
                    {
                        pt->estMort = true;
                    }
                    break;
                }

                // Sinon c'est que le joueur rentre en collision sur le côté => la partie est perdu
                else
                {
                    //Si le joueur possède encore des vies
                    if( getPlayer()->nombreVies > 0 )
                    {
                        //On décrémente le nombre de vie
                        getPlayer()->nombreVies--;
                        printf("Il reste %d points de vie\n", getPlayer()->nombreVies );
                    }
                    //Sinon le joueur a perdu
                    else 
                    {
                        GameOver_Load();
                    }

                }
            }
            break;
        }
    }//Fin du parcours de la liste des ennemis

    //Verifie si le joueur tombe dans le vide et qu'il dépasse la hauteur de l'écran => la partie est perdu
    if( getPlayer()->y > 720 ) 
    {
        GameOver_Load();
    }

    // Vérifie les collisions avec le décor
    Level_Collision( );
}

/**
 * \fn extern void Level_Collision()
 * \brief Fonction qui gère les collisions avec le décor
 * \return pas de valeur de retour (void)
*/
extern void Level_Collision()
{
    
    /*##### JOUEUR ######*/
    // Largeur et Hauteur du joueur
    float joueur_w = getPlayer()->tex.w ;
    float joueur_h = getPlayer()->tex.h;
    
    // Position X & Y du joueur
    float joueur_x = getPlayerX();
    float joueur_y = getPlayerY();

    
    for(Node * pt = getCollider()->head ; pt != NULL; pt = pt->next)
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
            Cas du haut, bas, droit & Left
        */

        //Si le joueur est situé dans l'alignement du collider
        if( joueur_x+joueur_w/2 > collider_x && joueur_x+joueur_w/2 < collider_x+collider_w  )
        {
            // Le haut du joueur rentre en collision avec le bas du collider
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
                //Si c'est la fin d'un niveau
                if( typeCollider == checkpoint && getPlayer()->isPasspordCollected )
                {
                    Init_Continue();
                }

                //Si c'est la fin du jeu = dernier niveau
                else if ( typeCollider == gamewin  && getPlayer()->isPasspordCollected  )
                {  
                    Init_MenuWin();
                    getBaseGame()->state = GAMEWIN;
                }

                //Sinon
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
            //Le côté droit du joueur est en collision avec le coté Left du bloc
            if(joueur_x < collider_x+collider_w && joueur_x+joueur_w > collider_x+collider_w && getPlayer()->vx < 0)
            {
                //Si c'est la fin d'un niveau
                if( typeCollider == checkpoint  && getPlayer()->isPasspordCollected )
                {                    
                    Init_Continue();    
                }
                //Si c'est la fin du jeu = dernier niveau
                else if ( typeCollider == gamewin  && getPlayer()->isPasspordCollected )
                {
                    
                        Init_MenuWin();
                        getBaseGame()->state = GAMEWIN;
                }
                //Sinon
                else 
                {
                    //correct x
                    getPlayer()->x = collider_x+collider_w;
                    joueur_x = collider_x+collider_w;

                    getPlayer()->vx = 0;
                }
            }

            // Le côté droit du joueur est en collision avec le coté droit du bloc
            else if( joueur_x + joueur_w > collider_x && joueur_x < collider_x && getPlayer()->x > 0)
            {
                //Si c'est la fin d'un niveau
                if( typeCollider == checkpoint && getPlayer()->isPasspordCollected )
                { 
                    Init_Continue();
                }
                //Si c'est la fin du jeu = dernier niveau
                else if ( typeCollider == gamewin && getPlayer()->isPasspordCollected )
                {
                    Init_MenuWin();
                    getBaseGame()->state = GAMEWIN;
                }

                //Sinon
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

