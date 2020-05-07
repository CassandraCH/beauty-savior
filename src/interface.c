/**
 * \file interface.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date avril 2020
 * \brief Programme qui gère l'interface de l'utilisateur 
 */
#include "baseGame.h"

GameObject interface; /**< Structure de type GameObject */

/**
 * \fn extern GameObject* getInterface()
 * \brief Fonction qui permet de retourner l'interface 
 * \return un pointeur sur l'interface
*/
extern GameObject* getInterface()
{
    return &interface;
}

/**
 * \fn extern void Interface_Init()
 * \brief Fonction qui initialise l'interface
 * \return pas de valeur de retour (void)
 */
extern void Interface_Init()
{
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Initialisation Interface");

    //Initialisation du hud score
    
    SetHUD_IntToTexture( getScores(),(SDL_Color){0xFF,0xFF,0xFF,0xFF}, "", getPlayer()->scores ,560, 21);
    //Initialisation du hud time
    Init_HUD(getTime(),(SDL_Color){0xFF,0xFF,0xFF,0xFF},"1 : 10", 90, 21);



  GameObject_LoadRessources(0, 0, &interface, "Scores", "graphics_assets/dead.png", "NULL", 500, 21);

  GameObject_LoadRessources(1, 0, &interface, "Items", "graphics_assets/items2.png", "NULL", 700, 21);

  GameObject_LoadRessources(2, 0, &interface, "Vie", "graphics_assets/vie_3.png", "NULL", 1091, 21);

    
  GameObject_LoadRessources(3, 0, &interface, "Help", "graphics_assets/help_info.png", "NULL", 18, 699);

  GameObject_LoadRessources(4,1, &interface, "Passeport", "graphics_assets/passport_on.png",
  "graphics_assets/passport_off.png", 900, 18);

    
 
  interface.componentSelected = 0;

  interface.bg = Texture_Load("graphics_assets/bg_interface.png");
}

/**
 * \fn extern void Interface_Render()
 * \brief Fonction qui gère l'affichage de l'interface utilisateur
 * \return pas de valeur de retour (void)
*/
extern void Interface_Render()
{
    

    GameObject_Render( &interface ,5, 20, 20, 1208,50 );


    
    SetHUD_IntToTexture(getTime(),(SDL_Color){0xFF,0xFF,0xFF,0xFF}, "0 : ", getBaseGame()->min ,90, 21 );
    
    
    AfficherHUD(getScores()); 
    AfficherHUD(getTime());
}