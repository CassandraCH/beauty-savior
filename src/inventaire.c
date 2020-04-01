#include "baseGame.h"

Menu_t inventaire;

extern Menu_t* getInventaire()
{
    return &inventaire;
}

extern void Init_Inventaire()
{  
     int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Inventaire");

    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */ 

    ChargerData_Menu(0,1,&inventaire , "ICON"
                ,"graphics_assets/inventaire/icon.png"
                ,"NULL"
                ,339
                ,491 );

    /* 
     * Deuxieme option : Retour sur le menu principal
     */
    ChargerData_Menu(1,0, &inventaire ,"OS"
                ,"graphics_assets/inventaire/os_on.png"
                ,"graphics_assets/icons_buttons/os_off.png"
                ,663
                ,337 );

    /* 
     * Deuxieme option : Retour sur le menu principal
     */
    ChargerData_Menu(2,1, &inventaire ,"ROCK"
                ,"graphics_assets/inventaire/rock_on.png"
                ,"graphics_assets/inventaire/rock_off.png"
                ,782
                ,337 );
    
    /* 
     * Deuxieme option : Retour sur le menu principal
     */
    ChargerData_Menu(3,1, &inventaire ,"TREE"
                ,"graphics_assets/inventaire/tree_on.png"
                ,"graphics_assets/inventaire/tree_off.png"
                ,830
                ,337 );


    //Option selectionnee = Reprendre partie
    inventaire.selectedOption = 1;

    //Chargement de la texture du menu de pause
    inventaire.bg = ChargerTexture("graphics_assets/inventaire/bg_inventaire.png");
}


extrn void Input_Inventaire(SDL_Event *event)
{

}

extern void Nettoyer_Inventaire()
{

}
