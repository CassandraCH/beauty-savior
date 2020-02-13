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


//Change la valeur des coordonnées x du héros
extern void setPlayerX(int valeur)
{
	player.x = valeur;
}


//Change la valeur des coordonnées y du héros
extern void setPlayerY(int valeur)
{
	player.y = valeur;
}

//Change la valeur du niveau en cours
extern void SetValeurDuNiveau(int valeur)
{
	level = valeur;
}

// Initialisation du joueur
extern void InitJoueur(Player *player)
{
	player->niveau = 1;
	*player = (Player) { 0 };
	chargerImage(&player->tex, "assets/rect10.png");	
	player->h = player->tex.h;
	player->w = player->tex.w;
	player->x = 100;
	player->y = 100;
}


 extern void InputJoueur( const Uint8* keystates )
{
     if( keystates[SDL_SCANCODE_LEFT] && getPlayer()->x-25 > 0  )
	{
		getPlayer()->vx -= 0.5;
        
        if( getPlayer()->vx < -6 )
        {
            getPlayer()->vx = -6;
        }
       
       getPlayer()->ralenti = 0;
		
	}
	else if (  keystates[SDL_SCANCODE_RIGHT])
	{
	
		getPlayer()->vx += 0.5;
        if(getPlayer()->vx > 6 )
        {
           getPlayer()->vx = 6;
        }
          
        getPlayer()->ralenti = false;

	}
    else if  ( keystates[SDL_SCANCODE_UP] )
    {
        getPlayer()->vy  = -10;
    }
    else if ( keystates[SDL_SCANCODE_DOWN] )
    {
        getPlayer()->y += 10;
    }
    else if ( keystates[SDL_SCANCODE_TAB ])
    {
        
        return;
    }else 
	{ // friction
       
        getPlayer()->vx *= 0.8f;
        getPlayer()->ralenti = true;

        if( fabsf( getPlayer()->vx) < 0.1f)
        {
               getPlayer()->vx = 0;
        }
    }

 }

extern void AfficherJoueur()
{
	SDL_Rect rec = { getPlayer()->x - camera.x , getPlayer()->y - camera.y , getPlayer()->w, getPlayer()->h};
    SDL_RenderFillRect(getRenderer(), &rec);
    
}

extern void UpdateJoueur(float dt)
{
	if( !getPlayer()->estMort )
    {	

        Player *man = getPlayer();
        man->x += getPlayer()->vx;
        man->y += getPlayer()->vy;


        man->vy += GRAVITY;

    }
	

}