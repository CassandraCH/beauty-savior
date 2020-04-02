#include "baseGame.h"


Menu_t interface;

extern Menu_t* getInterface()
{
    return &interface;
}


extern void Init_Interface()
{
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Initialisation Interface");


    //Initialisation du hud score
    Init_HUD(getScores(),"0", 565, 17);
    //Initialisation du hud time
    Init_HUD(getTime(),"1 : 10", 90, 15);

    

     /* 
     * Premiere option : Retour au menu principal
     * Actif par défaut
     */ 

    ChargerData_Menu(0,0,&interface , "Timer"
                ,"graphics_assets/timer.png"
                ,"NULL"
                ,20
                ,10 );


    /* 
     * Deuxieme option : Charger la partie
     */

    ChargerData_Menu(1,0, &interface ,"Scores"
                ,"graphics_assets/score.png"
                ,"NULL"
                ,500
                ,18 );


    ChargerData_Menu(2,0, &interface ,"Items"
                ,"graphics_assets/items.png"
                ,"NULL"
                ,700
                ,18 );

    

    interface.selectedOption = 0;

    
    interface.bg = NULL;
    
}


extern void AfficherInterface()
{
    
    Dessiner_Menu( &interface ,3, 0, 0, 0,0 );

    if( getBaseGame()->time_s > 100 )
    {
      SetHUD_IntToTexture(getTime(),"1 : ",getBaseGame()->sec ,90, 15 );
    }
    else 
    {
      SetHUD_IntToTexture(getTime(),"0 : ", getBaseGame()->min ,90, 15 );
    }

    AfficherHUD(getScores()); 
    AfficherHUD(getTime());
    

}