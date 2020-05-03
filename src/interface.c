/**
 * \file interface.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date avril 2020
 * \brief Programme qui gère l'interface de l'utilisateur 
 */
#include "baseGame.h"

Menu_t interface; /**< Structure de type menu_t */

/**
 * \fn extern Menu_t* getInterface()
 * \brief Fonction qui permet de retourner l'interface 
 * \return un pointeur sur l'interface
*/
extern Menu_t* getInterface()
{
    return &interface;
}

/**
 * \fn extern void Init_Interface()
 * \brief Fonction qui initialise l'interface
 * \return pas de valeur de retour (void)
 */
extern void Init_Interface()
{
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Initialisation Interface");

    //Initialisation du hud score
    Init_HUD(getScores(),"0", 565, 17);
    //Initialisation du hud time
    Init_HUD(getTime(),"1 : 10", 90, 15);

    


    ChargerData_Menu(0,0,&interface , "Timer"
                ,"graphics_assets/timer.png"
                ,"NULL"
                ,20
                ,10 );
                
    /* 
     * Deuxieme option : Charger la partie
     */

  ChargerData_Menu(0, 0, &interface, "Timer", "graphics_assets/timer.png", "NULL", 20, 10);

  /* 
  * Deuxieme option : Charger la partie
  */

  ChargerData_Menu(1, 0, &interface, "Scores", "graphics_assets/dead.png", "NULL", 500, 18);

  ChargerData_Menu(2, 0, &interface, "Items", "graphics_assets/items2.png", "NULL", 700, 18);

  ChargerData_Menu(3, 0, &interface, "Vie", "graphics_assets/vie_3.png", "NULL", 1091, 18);

  ChargerData_Menu(4, 0, &interface, "Help", "graphics_assets/help_info.png", "NULL", 18, 699);

  interface.selectedOption = 0;

  interface.bg = NULL;
}

/**
 * \fn extern void AfficherInterface()
 * \brief Fonction qui gère l'affichage de l'interface utilisateur
 * \return pas de valeur de retour (void)
*/
extern void AfficherInterface()
{
    
    Dessiner_Menu( &interface ,5, 0, 0, 0,0 );

    
    SetHUD_IntToTexture(getTime(),"0 : ", getBaseGame()->min ,90, 15 );
    
    
    AfficherHUD(getScores()); 
    AfficherHUD(getTime());
}