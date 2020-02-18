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
extern void InitJoueur()
{
	player.niveau = 1;
	*player = (Player) { 0 };
	chargerImage(&player.tex, "assets/rect10.png");	
	player.h = player->tex.h;
	player.w = player->tex.w;
	player.x = 100;
    player.y = 100;
    player.posXDepart = 100;
    player.posYDepart = 100;
    player.actualiserVie = (void*)actualiserJoueur;
}


 extern void InputJoueur( const Uint8* keystates )
{
     if( keystates[SDL_SCANCODE_LEFT] && player.x-25 > 0  )
	{
		player->vx -= 0.5;
        
        if( player.vx < -6 )
        {
            player.vx = -6;
        }
       player.ralenti = 0;
		
	}
	else if (  keystates[SDL_SCANCODE_RIGHT] )
	{
		player.vx += 0.5;
        if(player.vx > 6 )
        {
           player.vx = 6;
        }     
        player.ralenti = false;
	}
    else if  ( keystates[SDL_SCANCODE_UP] )
    {
        player.vy  = -10;
    }
    else if ( keystates[SDL_SCANCODE_DOWN] )
    {
        player.y += 10;
    }
    else 
	{ 
        // friction   
        player.vx *= 0.8f;
        player.ralenti = true;

        if( fabsf( player.vx) < 0.1f)
        {
                player.vx = 0;
        }
    }

 }



extern void AfficherJoueur()
{
	SDL_Rect rec = { player.x - camera.x , player.y - camera.y , player.w, player.h};
    SDL_RenderFillRect(getRenderer(), &rec);

}

extern void UpdateJoueur(float dt)
{
	if( !player.estMort )
    {	

        Player *man = getPlayer();
        man->x += player.vx;
        man->y += player.vy;

        man->vy += GRAVITY;
    }
}

extern void actualiserJoueur(void)
{

    if( player.nombreVies > 0 )
    {
        player.nombreVies--;
    }else 
    {
        player.estMort = true;
        Init_MenuPrincipal();
        DestructionNiveau();
        getBaseGame()->state = MENU_PRINCIPAL;
        
    }
    setPlayerX(player.posXDepart);
    setPlayerY(player.posYDepart);
    player.vx = 0;

}
