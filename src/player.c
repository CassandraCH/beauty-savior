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


int level;
Player player;
Texture_Manager playerSprite;


//Renvoie l'adresse vers de l'objet Joueur (héros)
extern Player *getPlayer(void)
{
    
	return &player;
}

//Renvoie les coordonnées x du héros
extern int getPlayerX(void)
{
	return player.x;
}

//Renvoie les coordonnées y du héros
extern int getPlayerY(void)
{
	return player.y;
}

extern void setNombretir() 
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

//Change la valeur du niveau en cours
extern void SetValeurDuNiveau(int valeur)
{
	level = valeur;
}


// Initialisation du joueur
extern void InitJoueur()
{
	player.niveau = 1;
    player.nombreVies = 3;

	// player = (Player) { 0 };
	chargerImage(&player.tex, "graphics_assets/rect10.png");	
	player.h = player.tex.h;
	player.w = player.tex.w;
	player.x = 600;

	player.y = 100;
    player.frame = 0;

    player.nb_lancer = 0;
    player.nb_objet = 0;
    player.posXDepart = 100;
    player.posYDepart = 100;

}


 extern void InputJoueur( SDL_Event *event  )
{

    if( event->type == SDL_KEYDOWN )
    {
        switch(event->key.keysym.sym)
        {
            case SDLK_UP:
                if( player.estSurSol )
                {
                    player.vy  = -9;
                    player.estSurSol =false;
                }
            break;
    
          
        }
    }
 
     const Uint8 *states = SDL_GetKeyboardState(NULL);

 
    if( states[SDL_SCANCODE_LEFT]  && player.x-25 > 0  ){
        player.vx -= 0.5;
            
            if( player.vx < -6 )
            {
                player.vx = -6;
            }
        player.estTourne = true;
        player.ralenti = 0;


    } else if(   states[SDL_SCANCODE_RIGHT] && player.x < LARGEUR_NIVEAU - player.w ){

        player.vx += 0.5;
        if(player.vx > 6 )
        {
           player.vx = 6;
        }
           player.estTourne = false;
            player.ralenti = 0;
    }
    else { // friction
    
        player.frame = 0;
        player.vx *= 0.8f;
        player.ralenti = 1;

        if( fabsf( player.vx) < 0.1f)
        {
               player.vx = 0;
        }
    }
   
 }

extern void CollisionItems() 
{
    Node * pt;
    
    // Vérifie la collision avec les items
     for(pt = getItems()->tete ; pt != NULL; pt = pt->suivant)
    {
        if(collide2d(getPlayerX(), getPlayerY(), pt->rect->x,pt->rect->y, player.tex.w,player.tex.h,pt->rect->w , pt->rect->h  ) && pt->type == item )
        {

            if( !pt->estMort )
            {
               pt->estMort = true;
               supprimeCible(getItems(), true);
               SetScore("SCORES", ++player.nb_objet);
            }
            break;
        }
    }


}

extern void AfficherJoueur()
{
	SDL_Rect rec = { player.x - camera.x , player.y - camera.y , player.tex.w, player.tex.h};
    SDL_RenderCopy(getRenderer(), player.tex.texture , NULL, &rec );
    
}

extern void UpdateJoueur( float dt)
{   

	if( !player.estMort )
    {	
        
        player.x += player.vx;
        player.y += player.vy;

        if( player.vx != 0 && player.estSurSol && !player.ralenti) 
        {
            if( getBaseGame()->time % 8 == 0 )
            {
                player.frame = player.frame + 1;
                if( player.frame > 5 ) player.frame = 0; 
            }
        }



        player.vy += GRAVITY;
    }
}

extern void actualiserJoueur(void)
{
    if( !player.estMort )
    {
        //  if( player.nombreVies > 1 )
        // {
        //     player.nombreVies--;
        //     printf("Il reste %d points de vie\n", getPlayer()->nombreVies );
        // }else 
        // {
           

            // }
            PlayerScore("Scores: 0", 50, 50);
            player.nb_lancer = 0;
            player.x = player.posXDepart;
            player.y = player.posYDepart;
            player.vx = 0;
            player.nb_objet = 0;

            return;
    }

}


extern bool collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
    return (! ( (x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))  )  );
}

/**
 *  Fonction qui s'occupe de gérer les attaques lancer par le joueur
 */
extern void attaqueJoueur()
{
    if ( getPlayer()->nb_objet > 0 )
    {

      
        CreerTir(bull, getPlayer()->w , getPlayer()->h, getPlayerX(),  getPlayerY() );
        SetScore("SCORES",--player.nb_objet);

    }
    return;
}

extern void collision_tir()
{

     Node * tir = NULL;
    Node * enne = NULL;
    if( getBullets()->nodeCount > 0 )
    {
         //Vérifie la collision avec les armes 
        for(tir = getBullets()->tete; tir != NULL; tir = tir->suivant)
        {
            for(enne = getEnnemis()->tete; enne != NULL; enne = enne->suivant)
            {
                if(collide2d( tir->rect->x , tir->rect->y, enne->rect->x,enne->rect->y,tir->rect->w ,tir->rect->h,enne->rect->w, enne->rect->h ) && enne->type == ennemi && tir->type == bull ) 
                {

                        if( !enne->estMort )
                        {
                            enne->estMort = true;
                            tir->estMort = true;
                            tir->rect->x = 0;
                            enne->rect->x = 0;
                        }
                            
                        break;
                }
                else if(collide2d( tir->rect->x , tir->rect->y, getPlayerX(),getPlayerY(),tir->rect->w ,tir->rect->h,getPlayer()->w, getPlayer()->h ) && tir->type == feu ) 
                {
                    Init_GameOver();
                    break;
                }
            }
        }
    }

}

extern void joueur_surSol()
{
    player.vy = 0;
    // Le joueur est posé sur un bloc. 
    if(!player.estSurSol)
    {
        getPlayer()->estSurSol = true;
    }

}


