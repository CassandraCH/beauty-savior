/**
 * \file menu_win.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu de pause
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
 */

#include "baseGame.h"

GameObject menu_win; /**< Structure de type GameObject */

/**
 * \fn extern GameObject * getMenu_Win()
 * \brief Fonction qui permet retourner le menu concernant la fin d'une partie gagnée
 * \return une structure menu de type GameObject
*/
extern GameObject * getMenu_Win()
{
    return &menu_win;
}

/**
 * \fn extern void Init_MenuWin()
 * \brief Fonction qui initialise le menu du jeux gagné
 * \return pas de valeur de retour (void)
*/
extern void Init_MenuWin()
{
     int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu Win\n");


    //Initialisation du hud score
    SetHUD_IntToTexture( getNombreVie(), (SDL_Color){0,0,0,0}, "" , getPlayer()->nombreVies , 550 , 392) ;
    SetHUD_IntToTexture( getScores() ,(SDL_Color){0,0,0,0}, "",  getPlayer()->scores , 680 , 392 );
    
    menu_win.nom_gameObject = "Menu Victoire";

    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */ 

    ChargerData_Menu(0,0,&menu_win , "Reprendre partie"
                ,"graphics_assets/win_icons/quit_on.png"
                ,"graphics_assets/win_icons/quit_off.png"
                ,552
                ,473 );

    /* 
     * Deuxieme option : Retour sur le menu principal
     */
    ChargerData_Menu(1,1, &menu_win ,"Retour menu"
                ,"graphics_assets/win_icons/menu_on.png"
                ,"graphics_assets/win_icons/menu_off.png"
                ,657
                ,473 );

    

    //Option selectionnee = Reprendre partie
    menu_win.selectedOption = 0;

    //Chargement de la texture du menu de pause
    menu_win.bg = ChargerTexture("graphics_assets/game_win.png");

    printf("Fin Chargement Menu Win\n");

}

/**
 * \fn extern void Input_MenuWin(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu
 * \details Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Input_MenuWin(SDL_Event *event)
{   
    bool isKeyPressed = false; 
    // Lecture de tous les evenements
    while (SDL_PollEvent(event) != 0)
    {
        if (event->type == SDL_QUIT || event->key.keysym.sym == SDLK_ESCAPE)
        {
            //changer l'etat du jeu
            getBaseGame()->estActif = false;
            return;
        }

         //Si une touche est appuyee
        if (event->type == SDL_KEYUP)
        {
            switch (event->key.keysym.sym)
            {
                //Cas touche fleche de gauche
                case SDLK_LEFT:
                    Gauche(getMenu_Win(), 2);
                    break;

                //Cas touche fleche de droite
                case SDLK_RIGHT:
                    Droite(getMenu_Win() , 2);
                    break;

                //Cas de la touche entree
                case SDLK_RETURN:
                    switch (getTouchePresse(getMenu_Win()))
                    {
                        //Cas de la premiere option : Quitter le jeux
                        case 0:
                            getBaseGame()->estActif = false;                  
                            break;
                        //Cas de la deuxieme option : retour sur le menu principal
                        case 1:
                            actualiserJoueur();   
                            getBaseGame()->state = MENU_PRINCIPAL;       
                            return;
                            break;
                        default:
                            break;
                    }//fin du switch
                    break;
                default:
                    break;
                } //fin du switch
        }
        
    } // fin while (SDL_PollEvent)
}
