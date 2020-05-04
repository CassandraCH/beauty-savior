/**
 * \file menu_pause.c
 * \author CALVADOS Cindy, CHAUMULON Cassandra, CHELLI Célia, OUSMANOVA Karina
 * \version 1.0
 * \date mars 2020
 * \brief Programme qui gère le menu de pause
 * \brief Initialisation, affichage du menu, navigation dans le menu, gestion des entrees clavier et destruction du menu
 */

#include "baseGame.h"

GameObject menu_pause; /**< Structure de type GameObject */

/**
 * \fn extern GameObject * getMenuPause()
 * \brief Fonction qui permet retourner le menu de pause
 * \return une structure menu de type GameObject
*/
extern GameObject * getMenuPause()
{
    return &menu_pause;
}

/**
 * \fn extern void Pause_Init()
 * \brief Fonction qui initialise le menu de pause
 * \return pas de valeur de retour (void)
*/
extern void Pause_Init()
{
     int width = LARGEUR_FENETRE, height = HAUTEUR_FENETRE;
    printf("Chargement Menu Pause");
    
    /* 
     * Premiere option : Reprendre la partie
     * Actif par défaut
     */ 

    menu_pause.nom_gameObject = "Menu Pause";

    GameObject_LoadRessources(0,0,&menu_pause , "Reprendre partie"
                ,"graphics_assets/icons_buttons/back_on_xs.png"
                ,"graphics_assets/icons_buttons/back_off_xs.png"
                ,339
                ,491 );

    /* 
     * Deuxieme option : Retour sur le menu principal
     */
    GameObject_LoadRessources(1,1, &menu_pause ,"Retour menu"
                ,"graphics_assets/icons_buttons/menu_on_xs.png"
                ,"graphics_assets/icons_buttons/menu_off_xs.png"
                ,620
                ,491 );

    

    //Option selectionnee = Reprendre partie
    menu_pause.componentSelected = 0;

    //Chargement de la texture du menu de pause
    menu_pause.bg = Texture_Load("graphics_assets/pause.png");
}

/**
 * \fn extern void Pause_Input(SDL_Event *event)
 * \brief Fonction qui gere les evenements du menu
 * \details Gestion des entrees clavier de l'utilisateur
 * \param event evenement
 * \return pas de valeur de retour (void)
*/
extern void Pause_Input(SDL_Event *event)
{
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
                //Cas touche fleche de LEFT_Key
                case SDLK_LEFT:
                    LEFT_Key(getMenuPause(), 2);
                    break;

                //Cas touche fleche de RIGHT_Key
                case SDLK_RIGHT:
                    RIGHT_Key(getMenuPause() , 2);
                    break;

                //Cas de la touche entree
                case SDLK_RETURN:
                    switch (GetKeypressed(getMenuPause()))
                    {
                        //Cas de la premiere option : reprendre la partie
                        case 0:
                            getBaseGame()->state = IN_GAME;                    
                            break;
                        //Cas de la deuxieme option : retour sur le menu principal
                        case 1:
                            Player_Reset();   
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
