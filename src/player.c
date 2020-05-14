/**
 * \file player.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date janvier 2020
 * \brief Programme qui gère le joueur
 * \brief Initialisation, affichage (et actualisation en fonction des entrées clavier), positionnement et déplacement du joueur
 * \brief Gestion des tirs (attaques) et des collisions
 */
#include "baseGame.h"

int level; /**< numero du niveau */
Player player; /**< joueur */
Texture_Manager playerSprite; /**< texture du joueur */

/**
 * \fn extern Player *getPlayer(void)
 * \brief Fonction qui permet retourner l'adresse vers l'objet Joueur (héros)
 * \return une structure joueur de type Player
*/
extern Player *getPlayer(void)
{
	return &player;
}

/**
 * \fn extern int getPlayerX(void)
 * \brief Fonction qui permet retourner la position en x du héros
 * \return un int qui correspond a la position en x
*/
extern int getPlayerX(void)
{
	return player.x;
}

/**
 * \fn extern int getPlayerY(void)
 * \brief Fonction qui permet de retourner la position en y du héros
 * \return un int qui correspond a la position en y
*/
extern int getPlayerY(void)
{
	return player.y;
}

/**
 * \fn extern void Player_SetBullets() 
 * \brief Fonction qui permet de regler le nombre de lancer du joueur
 * \return pas de valeur de retour (void)
*/
extern void Player_SetBullets() 
{
    if( player.nb_lancer < 1  ) 
    {
        player.nb_lancer++;
    }
    else 
    {
       player.nb_lancer = 0;
    }           
}

/**
 * \fn extern void SetValeurDuNiveau(int valeur)
 * \brief Fonction qui permet de changer la valeur du niveau en cours
 * \param valeur numero du niveau en cours
 * \return pas de valeur de retour (void)
*/
extern void SetValeurDuNiveau(int valeur)
{
	level = valeur;
}

/**
 * \fn extern void Player_Init()
 * \brief Fonction qui permet d'initialiser le joueur
 * \brief Remplissage de tous les champs de la structure Player
 * \return pas de valeur de retour (void)
*/
extern void Player_Init()
{
    //niveau en cours et nombre de vies
	player.niveau = 1;
    player.nombreVies = 3;

    //Chargement de l'image
	Image_Load(&player.tex, "graphics_assets/player.png");	

    //position en x et en y, hauteur et largeur
	player.h = player.tex.h;
	player.w = player.tex.w;
    player.x = 100;
    player.y = 50;
    player.scores = 0;

   // le passport n'est pas collecté par défaut
    player.isPasspordCollected = false;

    //inventaire initialise a 0
    player.nb_lancer = 0;
    player.nb_objet = 0;

    player.osActif = true;
    player.treeActif = false;
    player.rockActif = false;

    //position de depart en x et en y
    player.posXDepart = player.x;
    player.posYDepart = player.y;
}

/**
 * \fn extern void Player_Input( SDL_Event *event  )
 * \brief Fonction qui gere les entrees clavier de l'utilisateur 
 * \param event evenement de l'utilisateur
 * \return pas de valeur de retour (void)
*/
extern void Player_Input(SDL_Event *event)
{
    //Si une touche a ete relachee
    if( event->type == SDL_KEYDOWN )
    {
        switch(event->key.keysym.sym)
        {   
            //Cas de la touche fleche du haut
            case SDLK_UP:
                if( player.estSurSol )
                {
                    //Gestion de la gravite
                    player.vy  = -9;
                    player.estSurSol =false;
                }
                
                break;
        }
    }
 
    //Variable qui permet de savoir si une touche enfoncee
    const Uint8 *states = SDL_GetKeyboardState(NULL);

    //Si la touche fleche LEFT_Key est appuyee et que le joueur peut se deplacer vers la LEFT_Key
    if( states[SDL_SCANCODE_LEFT]  && player.x - 25 > 0  )
    {
        //Modification de la velocite du joueur
        player.vx -= 0.5;

        //Deplacement du joueur vers la LEFT_Key    
        if( player.vx < -8)
        {
            player.vx = -8;
        }

        player.estTourne = true;
    }

    //Si la touche fleche RIGHT_Key est appuyee et que le joueur peut se deplacer vers la RIGHT_Key
    else if(states[SDL_SCANCODE_RIGHT] && player.x < LARGEUR_NIVEAU - player.w )
    {
        //Modification de la velocite du joueur
        player.vx += 0.5;

        //Deplacement du joueur vers la RIGHT_Key
        if(player.vx > 8)
        {
           player.vx = 8;
        }

        player.estTourne = false;
    }

    //Sinon => friction
    else
    { 
      
        //Modification de la velocite
        player.vx *= 0.8f;

        //Arreter le deplacement du joueur
        if( fabsf( player.vx) < 0.1f)
        {
            player.vx = 0;
        }
    } 
}

/**
 * \fn extern void CollisionItems() 
 * \brief Fonction qui gere les collisions avec les items
 * \return pas de valeur de retour (void)
*/
extern void CollisionItems() 
{
    Node * pt; //pointeur sur l'item actuel
    
    //Parcours de la liste des items
    for(pt = getItems()->head ; pt != NULL; pt = pt->next)
    {
        //Si le joueur est en collision avec l'item actuel
        if(collide2d(getPlayerX(), getPlayerY(), pt->_rect.x,pt->_rect.y, player.tex.w,player.tex.h,pt->_rect.w , pt->_rect.h) )
        {
            //Si l'item est toujours existant
            if(!pt->estMort)
            {
                //Changement de l'etat de l'item => mort
                pt->estMort = true;
                //Suppression de l'item dans la liste
                Delete_Target(getItems(), true);
                
                if( pt->type == os )
                {
                    increaseOs();
                    printf("Nombre Os: %d\n", getOs());
                }
                else if ( pt->type == rock )
                {
                    increaseRock();
                    printf("Nombre Rock: %d\n", getRock());
                }
                else if ( pt->type == tree )
                {
                    increaseBranche(); 
                    printf("Nombre branche: %d\n", getBranche());
                }
                else if ( pt->type == passport )
                {
                    player.isPasspordCollected = true;
                    UpdateComponent( &getInterface()->components[4], 0);
                }    
                
                        
            }
            break;
        }
    }
}

/**
 * \fn extern void Player_Render()
 * \brief Fonction qui gere l'affichage du joueur a l'ecran
 * \return pas de valeur de retour (void)
*/
extern void Player_Render()
{
    //rectangle tampon
	SDL_Rect rec = { player.x - camera.x , player.y - camera.y , player.tex.w, player.tex.h};

    //Gestion du rendu
    SDL_RenderCopy(getRenderer(), player.tex.texture , NULL, &rec );
}


/**
 * \fn extern void Player_Update()
 * \brief Fonction qui met a jour le joueur en fonction du delta-time
 * \brief Gestion du deplacement du joueur
 * \return pas de valeur de retour (void)
*/
extern void Player_Update()
{   

	if( !player.estMort )
    {	
        
        player.x += player.vx;
        player.y += player.vy;

        
        player.vy += GRAVITY;
    }
}

/**
 * \fn extern void Player_Reset(void)
 * \brief Fonction qui reinitialise le joueur
 * \brief Repositionnement du joueur a sa position initiale et remise a 0 de ses compteurs du nombre de lancer et du nombre d'objets
 * \return pas de valeur de retour (void)
*/
extern void Player_Reset(void)
{

    if( !player.estMort || getBaseGame()->state == LOADING )
    {
          
            player.nb_lancer = 0;
            player.y = player.posYDepart;
            player.x = player.posXDepart;
            if( getBaseGame()->state != LOADING )
            {
                player.vx = 0;
                player.nb_objet = 0;
                player.niveau = 1;
            }
            
        return;
    }

}

/**
 * \fn extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
 * \brief Fonction qui verifie la collision entre 2 elements
 * \param x1 position en x du premier element
 * \param y1 position en y du premier element
 * \param x2 position en x du deuxieme element
 * \param y2 position en y du deuxieme element
 * \param wt1 largeur du premier element
 * \param ht1 hauteur du premier element
 * \param wt2 largeur du deuxieme element
 * \param ht2 hauteur du deuxieme element
 * \return un booleen : VRAI s'il y a collison, FAUX sinon
*/
extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
    return (! ( (x1 > (x2+wt2)) || (x2 > (x1+wt1)) || ( y1 > (y2+ht2) ) || ( y2 > (y1+ht1) )  )  );
}

/**
 *  Fonction qui s'occupe de gérer les attaques lancer par le joueur
 */
extern void Player_Attack()
{
  
         
        if (  getRock() > 0 && player.rockActif  )
        {
            decreaseRock();
            CreateBullet(rock, getPlayer()->w , getPlayer()->h, getPlayerX(),  getPlayerY() );
        }
        else if( getBranche() > 0 && player.treeActif )
        {
            decreaseBranche();
            CreateBullet(tree, getPlayer()->w , getPlayer()->h, getPlayerX(),  getPlayerY() );
        }
  

    return;
}


/**
 * \fn extern void Shoot_Collision()
 * \brief Fonction qui gere les collisions entre un bullet et un ennemi
 * \return pas de valeur de retour (void)
*/
extern void Shoot_Collision()
{

    bool collide = false;
     Node * tir = NULL;
    Node * enne = NULL;
    if( getBullets()->nodeCount > 0 )
    {
         //Vérifie la collision avec les armes 
        for(tir = getBullets()->head; tir != NULL; tir = tir->next)
        {
            for(enne = getEnnemis()->head; enne != NULL; enne = enne->next)
            {
                if(collide = ( collide2d( tir->_rect.x , tir->_rect.y, enne->_rect.x,enne->_rect.y,tir->_rect.w ,tir->_rect.h,enne->_rect.w, enne->_rect.h ) ) && 
                ( tir->type == tree || tir->type == rock) ) 
                {

                        //Incrementation du score
                         if( collide ) SetHUD_IntToTexture(getScores(),(SDL_Color){0xFF,0xFF,0xFF,0xFF}, "", ++getPlayer()->scores, 565, 21 );
                        if( !enne->estMort )
                        {
                            enne->estMort = true;
                            tir->estMort = true;
                            tir->_rect.x = 0;
                            enne->_rect.x = 0;
                        }
                        
                            
                        break;
                }
                else if(collide2d( tir->_rect.x , tir->_rect.y, getPlayerX(),getPlayerY(),tir->_rect.w ,tir->_rect.h,getPlayer()->w, getPlayer()->h ) && tir->type == feu ) 
                {
                     if( !getPlayer()->estMort && getPlayer()->nombreVies > 1 )
                    {
                        getPlayer()->nombreVies--;
                        switch( getPlayer()->nombreVies )
                        {
                            case 1: UpdateImage_Component( &getInterface()->components[2], "graphics_assets/vie_1.png" ); break;
                            case 2: UpdateImage_Component( &getInterface()->components[2], "graphics_assets/vie_2.png" ); break;
                        }
                        Enemy_SetBullets();
                        tir->estMort = true;
                        printf("Il reste %d points de vie\n", getPlayer()->nombreVies );
                    }
                    else 
                    {
                        GameOver_Load();
                    }
                    break;
                }
            }
        }
    }

}



