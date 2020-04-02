#include "baseGame.h"



extern void Init_Interface()
{
    int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Initialisation Interface");


    //Initialisation du hud score
    Init_HUD(getScores(),"0", 10, 0);
    //Initialisation du hud time
    Init_HUD(getTime(),"1 : 10", 500, 0);


     /* 
     * Premiere option : Retour au menu principal
     * Actif par défaut
     */ 

    // ChargerData_Menu(0,0,&menu_load , "Retour"
    //             ,"graphics_assets/icons_buttons/return_on_xs.png"
    //             ,"graphics_assets/icons_buttons/return_off_xs.png"
    //             ,339
    //             ,570 );


    // /* 
    //  * Deuxieme option : Charger la partie
    //  */

    // ChargerData_Menu(1,1, &menu_load ,"Charger Partie"
    //             ,"graphics_assets/icons_buttons/load_on_xs.png"
    //             ,"graphics_assets/icons_buttons/load_off_xs.png"
    //             ,620
    //             ,570 );

    
}


extern void AfficherInterface()
{
    
    AfficherHUD(getScores()); 
    AfficherHUD(getTime());
    

}